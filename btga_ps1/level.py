"""FLB terrain grids, level BIN containers, font BIN glyph tables, VAGS.SFX, XA/STR sectors.

Evidence (SLUS_010.44):
  * FLB: loaded by 0x8003C8C8 into the buffer at 0x800DDDF0; sampled by the ground
    renderer 0x8003AF64 (u16 width selects 64/128/256 addressing; row stride width*4).
    Cell bits 0-14: BGR555 vertex colour (converted at 0x8003B374); bit 15: corner/UV
    order flag (0x8003B26C); bits 16-17: UV rotation (0x8003B2C4); bits 18-23: index
    into the 64-entry tile table at 0x800DDFF8 ((v >> 15) & 0x1F8 at 0x8003B238).
  * Level BIN: raw load 0x8003DE58; parse 0x8002429C: header words 0-4 are byte offsets
    rebased to pointers; (off3-off2)/12 placements (0xAAAAAAAB multiply); placement
    {s16 x, s16 y, s16 z, u16 yaw, u32 offset into section 4} consumed at 0x800245B4.
  * Font BIN: "assets\\bt14ln.bin" etc.; 6-byte glyph rectangles (layout proven by
    contiguity of x+width across every record).
  * VAGS.SFX: loader 0x80054B10: words [1]=data offset, [2]=data bytes (SPU upload),
    [3]=table bytes, [4]=entries; table copied from +20; entry word 0 rebased to SPU.
"""
from .binio import FormatError, Reader

FLB_WIDTHS = (64, 128, 256)   # the only widths the sampler at 0x8003AF64 addresses


def decode_flb(data, name="<flb>", tile_count=None):
    r = Reader(data, name)
    w, h = r.u16(0, "width"), r.u16(2, "height")
    if w not in FLB_WIDTHS:
        raise FormatError("%s: width %d not addressable by the engine (64/128/256)" % (name, w))
    if not 1 <= h <= 1024:
        raise FormatError("%s: height %d out of range" % (name, h))
    if len(r) != 4 + 4 * w * h:
        raise FormatError("%s: size %d != 4 + 4*%d*%d" % (name, len(r), w, h))
    cells = [r.u32(4 + 4 * k) for k in range(w * h)]
    tiles = {}
    over = 0
    for v in cells:
        t = (v >> 18) & 0x3F
        tiles[t] = tiles.get(t, 0) + 1
        if tile_count is not None and t >= tile_count:
            over += 1
    return {"width": w, "height": h, "cells": cells, "tile_histogram": dict(sorted(tiles.items())),
            "cells_with_tile_beyond_tex": over,
            "high_byte_histogram": _hist(v >> 24 for v in cells)}


def flb_cell(v):
    return {"color_bgr555": v & 0x7FFF, "flag_bit15": (v >> 15) & 1, "uv_rotation": (v >> 16) & 3,
            "tile": (v >> 18) & 0x3F, "opaque_bits_24_31": v >> 24}


def _hist(it):
    h = {}
    for x in it:
        h[x] = h.get(x, 0) + 1
    return dict(sorted(h.items()))


def decode_level_bin(data, name="<bin>"):
    r = Reader(data, name)
    hdr = [r.u32(4 * k) for k in range(8)]
    if hdr[0] != 0x20:
        raise FormatError("%s: first section offset 0x%X != 0x20 (not a level BIN)" % (name, hdr[0]))
    offs = hdr[:5]
    if offs != sorted(offs) or offs[4] > len(r):
        raise FormatError("%s: section offsets %s not monotonic within file" % (name, offs))
    if hdr[5:] != [0, 0, 0]:
        raise FormatError("%s: header words 5-7 are %s, expected zero" % (name, hdr[5:]))
    if (offs[3] - offs[2]) % 12:
        raise FormatError("%s: placement section length not a multiple of 12" % name)
    n = (offs[3] - offs[2]) // 12
    cnt, first = r.u16(offs[1]), r.u16(offs[1] + 2)
    if first + cnt > n:
        raise FormatError("%s: active range %d+%d exceeds %d placements" % (name, first, cnt, n))
    sec4 = len(r) - offs[4]
    pl = []
    for i in range(n):
        o = offs[2] + 12 * i
        rec = {"x": r.s16(o), "y": r.s16(o + 2), "z": r.s16(o + 4), "yaw_u16": r.u16(o + 6),
               "data_offset": r.u32(o + 8)}
        if rec["data_offset"] >= sec4:
            raise FormatError("%s: placement %d data offset 0x%X beyond section 4 (0x%X)" % (name, i, rec["data_offset"], sec4))
        pl.append(rec)
    sec1 = r.bytes(offs[1], offs[2] - offs[1])
    bounds = None
    if len(sec1) >= 32:
        bounds = {"s16_0x14": r.s16(offs[1] + 20), "s16_0x18": r.s16(offs[1] + 24),
                  "s16_0x1A": r.s16(offs[1] + 26), "s16_0x1E": r.s16(offs[1] + 30)}
    return {"section_offsets": offs, "section_sizes": [b - a for a, b in zip(offs, offs[1:] + [len(r)])],
            "placements": pl, "active_first": first, "active_count": cnt, "section1_bounds": bounds,
            "section0_hex": r.bytes(offs[0], offs[1] - offs[0]).hex()}


FONT_SHEETS = {"BT14LN": "BT14PT", "LOUS16LN": "LOUS16", "SURP10LN": "SURP10", "VERDA8LN": "VERDA8PT"}


def decode_font_bin(data, name="<font>", sheet_size=None):
    """6-byte glyph rects {u16 x, u16 y, u16 width}; an all-zero record is an absent glyph.

    sheet_size: (w, h) of the paired font TEX; present glyphs must start inside it and
    end at or before its right edge."""
    r = Reader(data, name)
    if len(r) == 0 or len(r) % 6:
        raise FormatError("%s: size %d not a positive multiple of 6" % (name, len(r)))
    glyphs = [{"x": r.u16(6 * k), "y": r.u16(6 * k + 2), "width": r.u16(6 * k + 4)} for k in range(len(r) // 6)]
    absent = 0
    for k, g in enumerate(glyphs):
        if g["width"] == 0:
            if g["x"] or g["y"]:
                raise FormatError("%s: glyph %d has zero width at (%d,%d)" % (name, k, g["x"], g["y"]))
            absent += 1
            continue
        if sheet_size is not None:
            sw, sh = sheet_size
            if g["x"] + g["width"] > sw or g["y"] >= sh:
                raise FormatError("%s: glyph %d (%d,%d,w%d) outside %dx%d sheet" % (name, k, g["x"], g["y"], g["width"], sw, sh))
    return {"glyphs": glyphs, "absent": absent}


def decode_sfx(data, name="<sfx>"):
    r = Reader(data, name)
    r.magic(0, b"1SFX")
    data_off, data_len, table_len, count = (r.u32(4 + 4 * k) for k in range(4))
    if table_len != 20 * count or 20 + table_len != data_off or data_off + data_len != len(r):
        raise FormatError("%s: header fields inconsistent with file size" % name)
    ents = []
    for i in range(count):
        o = 20 + 20 * i
        ents.append({"spu_offset": r.u32(o), "words": [r.u32(o + 4 * k) for k in range(1, 5)]})
    starts = [e["spu_offset"] for e in ents]
    if any(s >= data_len for s in starts):
        raise FormatError("%s: entry offset beyond VAG data" % name)
    return {"data_offset": data_off, "data_bytes": data_len, "count": count, "entries": ents}


def inventory_xa(data, name="<xa>"):
    """STR/PCK are raw 2336-byte Mode 2 sectors: 8-byte subheader + 2328 payload."""
    r = Reader(data, name)
    if len(r) % 2336:
        raise FormatError("%s: size not a multiple of 2336" % name)
    n = len(r) // 2336
    kinds = {}
    for k in range(n):
        sub = r.bytes(2336 * k, 8)
        if sub[0:4] != sub[4:8]:
            raise FormatError("%s: sector %d subheader copies differ" % (name, k))
        sm = sub[2]
        kind = "audio" if sm & 0x04 else "video" if sm & 0x02 else "data" if sm & 0x08 else "other"
        key = "%s:ch%d" % (kind, sub[1])
        kinds[key] = kinds.get(key, 0) + 1
    return {"sectors": n, "sector_kinds": dict(sorted(kinds.items()))}
