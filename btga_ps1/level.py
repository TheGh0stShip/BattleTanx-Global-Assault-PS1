"""FLB terrain grids, level BIN containers, font BIN glyph tables, VAGS.SFX, XA/STR sectors.

Evidence (SLUS_010.44):
  * FLB: loaded by 0x8003C8C8 into the buffer at 0x800DDDF0; sampled by the ground
    renderer 0x8003AF64 (u16 width selects 64/128/256 addressing; row stride width*4).
    Cell bits 0-14: BGR555 vertex colour (converted at 0x8003B374); bit 15: corner/UV
    order flag (0x8003B26C); bits 16-17: UV rotation (0x8003B2C4); bits 18-23: index
    into the 64-entry tile table at 0x800DDFF8 ((v >> 15) & 0x1F8 at 0x8003B238).
  * Level BIN: raw load 0x8003DE58; parse 0x8002429C: header words 0-4 are byte offsets
    rebased to pointers; (off3-off2)/12 placements (0xAAAAAAAB multiply); placement
    {s16 x, s16 y, s16 z, u16 yaw, u32 offset into section 3} consumed at 0x800245B4.
    The call at 0x800245F8 adds that offset to rebased header word 3. The first byte
    is dispatched through the 44-slot table at 0x800CD6A4. Record sizes below tile
    the object region of all 75 level BIN files exactly.
  * Font BIN: "assets\\bt14ln.bin" etc.; 6-byte glyph rectangles (layout proven by
    contiguity of x+width across every record).
  * VAGS.SFX: loader 0x80054B10: words [1]=data offset, [2]=data bytes (SPU upload),
    [3]=table bytes, [4]=entries; table copied from +20; entry word 0 rebased to SPU.
"""
from .binio import FormatError, Reader

FLB_WIDTHS = (64, 128, 256)   # the only widths the sampler at 0x8003AF64 addresses

OBJECT_RECORD_SIZES = {
    0: 4, 1: 8, 3: 20, 4: 16, 5: 8, 6: 4, 7: 4, 9: 4,
    10: 12, 11: 4, 12: 8, 13: 16, 14: 8, 15: 12, 17: 4,
    20: 4, 21: 24, 24: 12, 25: 12, 26: 40, 27: 4,
    30: 16, 31: 8, 32: 16, 35: 8, 37: 24, 38: 4,
    42: 4, 43: 8,
}

# These opcodes read the u16 at +2 through the same model-name lookup in the
# PS1 dispatcher and the corresponding N64 entry-script dispatcher.
OBJECT_MODEL_REFERENCE_OPCODES = frozenset((0, 1, 11, 14, 35, 42, 43))


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
    if offs[1] - offs[0] != 4:
        raise FormatError("%s: group-count section is not four bytes" % name)
    group_count = r.u32(offs[0], "group count")
    if offs[2] - offs[1] != 16 * group_count:
        raise FormatError("%s: group section size %d != 16*%d" %
                          (name, offs[2] - offs[1], group_count))
    groups = []
    for i in range(group_count):
        o = offs[1] + 16 * i
        group = {"placement_count": r.u16(o), "first_placement": r.u16(o + 2),
                 "x0": r.s16(o + 4), "y0": r.s16(o + 6), "z0": r.s16(o + 8),
                 "x1": r.s16(o + 10), "y1": r.s16(o + 12), "z1": r.s16(o + 14)}
        if group["first_placement"] + group["placement_count"] > n:
            raise FormatError("%s: group %d placement range %d+%d exceeds %d" %
                              (name, i, group["first_placement"], group["placement_count"], n))
        groups.append(group)
    cnt = groups[0]["placement_count"]
    first = groups[0]["first_placement"]
    object_start, object_end = offs[3], offs[4]
    object_records = []
    object_by_offset = {}
    pos = object_start
    while pos < object_end:
        rel = pos - object_start
        opcode = r.u8(pos, "object opcode")
        size = OBJECT_RECORD_SIZES.get(opcode)
        if size is None:
            raise FormatError("%s: unknown object opcode %d at section-3 offset 0x%X" % (name, opcode, rel))
        if pos + size > object_end:
            raise FormatError("%s: object opcode %d at 0x%X overruns section 3" % (name, opcode, rel))
        raw = r.bytes(pos, size)
        rec = {"offset": rel, "opcode": opcode, "size": size, "raw_hex": raw.hex(),
               "u16": [r.u16(pos + 2 * k) for k in range(size // 2)],
               "u32": [r.u32(pos + 4 * k) for k in range(size // 4)]}
        if opcode == 30:
            rec["fields"] = {
                "mode": r.u8(pos + 1),
                "min_offset": [r.s16(pos + 2), r.s16(pos + 4), r.s16(pos + 6)],
                "max_offset": [r.s16(pos + 8), r.s16(pos + 10), r.s16(pos + 12)],
                "reserved_u16": r.u16(pos + 14),
            }
            if rec["fields"]["reserved_u16"] != 0:
                raise FormatError("%s: opcode 30 at 0x%X has nonzero reserved word" % (name, rel))
        object_by_offset[rel] = len(object_records)
        object_records.append(rec)
        pos += size
    name_ptrs = []
    pos = offs[4]
    while pos + 4 <= len(r):
        ptr = r.u32(pos, "model-name pointer")
        if ptr == 0:
            break
        if ptr < offs[4] or ptr >= len(r):
            raise FormatError("%s: model-name pointer 0x%X outside section 4" % (name, ptr))
        name_ptrs.append(ptr)
        pos += 4
    model_names = []
    if name_ptrs:
        string_start = min(name_ptrs)
        if any(r.bytes(pos, string_start - pos)):
            raise FormatError("%s: nonzero bytes between model-name table and strings" % name)
        for ptr in name_ptrs:
            end = data.find(b"\0", ptr)
            if end < 0:
                raise FormatError("%s: unterminated model name at 0x%X" % (name, ptr))
            raw_name = r.bytes(ptr, end - ptr)
            try:
                text = raw_name.decode("ascii")
            except UnicodeDecodeError:
                raise FormatError("%s: non-ASCII model name at 0x%X" % (name, ptr))
            model_names.append({"pointer": ptr, "section_offset": ptr - offs[4], "name": text})
    for rec in object_records:
        if rec["opcode"] in OBJECT_MODEL_REFERENCE_OPCODES:
            model_index = rec["u16"][1]
            if model_index != 0xFFFF and model_index >= len(model_names):
                raise FormatError("%s: opcode %d at 0x%X references model %d of %d" %
                                  (name, rec["opcode"], rec["offset"], model_index, len(model_names)))
            fields = rec.setdefault("fields", {})
            fields["model_name_index"] = None if model_index == 0xFFFF else model_index
            fields["model_name"] = None if model_index == 0xFFFF else model_names[model_index]["name"]
    pl = []
    for i in range(n):
        o = offs[2] + 12 * i
        rec = {"x": r.s16(o), "y": r.s16(o + 2), "z": r.s16(o + 4), "yaw_u16": r.u16(o + 6),
               "data_offset": r.u32(o + 8)}
        if rec["data_offset"] not in object_by_offset:
            raise FormatError("%s: placement %d data offset 0x%X is not a section-3 object boundary" %
                              (name, i, rec["data_offset"]))
        rec["object_record"] = object_by_offset[rec["data_offset"]]
        pl.append(rec)
    return {"section_offsets": offs, "section_sizes": [b - a for a, b in zip(offs, offs[1:] + [len(r)])],
            "group_count": group_count, "groups": groups,
            "placements": pl, "active_first": first, "active_count": cnt,
            "object_records": object_records,
            "model_names": model_names,
            "section4_hex": r.bytes(offs[4], len(r) - offs[4]).hex()}


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
        packed = r.u32(o + 16)
        ents.append({"spu_offset": r.u32(o), "data_bytes": r.u32(o + 4),
                     "flags": r.u32(o + 8), "volume": r.u32(o + 12),
                     "pitch": packed & 0xFFFF,
                     "sentinel_s16": packed >> 16 if packed < 0x80000000 else (packed >> 16) - 0x10000})
    starts = [e["spu_offset"] for e in ents]
    if any(s >= data_len for s in starts):
        raise FormatError("%s: entry offset beyond VAG data" % name)
    for i, e in enumerate(ents):
        expected_end = starts[i + 1] if i + 1 < count else data_len
        if e["spu_offset"] + e["data_bytes"] != expected_end:
            raise FormatError("%s: entry %d does not end at the next sample" % (name, i))
        if e["flags"] != 1 or e["volume"] != 0x3FFF or e["sentinel_s16"] != -1:
            raise FormatError("%s: entry %d has unexpected playback constants" % (name, i))
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
