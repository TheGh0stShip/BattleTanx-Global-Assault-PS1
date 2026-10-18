"""TEX, IMG/PLT and FUL decoders.

Evidence (SLUS_010.44, load address 0x80010000):
  * TEX entry reader 0x8003CB80, called from the TEX loader at 0x8003CCE8.
  * IMG descriptor loop in the level loader 0x8003D5B8 (0x8003D7C4..0x8003D850).
  * PLT records are walked with a 40-byte stride by 0x8003D0CC (8-byte header + 16 colours).
  * FUL frames: \\assets\\*.ful string references; frame size proven by file arithmetic only.
"""
from .binio import FormatError, Reader, bgr555_to_rgba

MODE_4BPP, MODE_8BPP, MODE_16BPP = 0, 1, 2
MAGIC_TEX = b"3TEX"
MAGIC_PAL = b"3PAL"     # 0x4C415033: loader reads an explicit CLUT count when the file magic is this
MAGIC_IMG = b"3IMG"
MAGIC_PLT = b"3PLT"
MAX_DIM = 1024          # PS1 VRAM is 1024x512 halfwords; larger is malformed
MAX_ENTRIES = 4096


def pixel_bytes(width, height, mode):
    """Exact pixel byte count using the engine's integer arithmetic.

    mode 0: (w/2)*h with C truncating division (0x8003CBE0), mode 1: w*h, mode 2: w*2*h.
    """
    if mode == MODE_4BPP:
        return (width // 2) * height
    if mode == MODE_8BPP:
        return width * height
    if mode == MODE_16BPP:
        return width * 2 * height
    raise FormatError("unknown texture mode %d" % mode)


def _check_dims(w, h, mode, where):
    if not (1 <= w <= MAX_DIM and 1 <= h <= MAX_DIM):
        raise FormatError("%s: dimensions %dx%d out of range" % (where, w, h))
    if mode == MODE_4BPP and w % 2:
        raise FormatError("%s: odd-width 4bpp texture is not representable" % where)


def _texels(pixels, w, h, mode):
    out = []
    if mode == MODE_4BPP:
        for i in range(w * h):
            b = pixels[i >> 1]
            out.append((b >> 4) if (i & 1) else (b & 0xF))     # low nibble is the left texel
    elif mode == MODE_8BPP:
        out = list(pixels[:w * h])
    else:
        r = Reader(pixels)
        out = [r.u16(2 * i) for i in range(w * h)]
    return out


def decode_tex(data, name="<tex>"):
    """Decode a 3TEX/3PAL texture container.

    Layout: char[4] magic, u32 count, then per entry
      u32 width, u32 height, u32 mode, pixels[pixel_bytes], [u32 clut_count if 3PAL],
      CLUT data (clut_count*16 or *256 BGR555 words; none for 16bpp).
    The engine advances its cursor by pixel_bytes rounded DOWN to 4; the file layout
    is exact.  Entries where the two disagree are reported, not silently reconciled.
    """
    r = Reader(data, name)
    magic = r.bytes(0, 4, "magic")
    if magic not in (MAGIC_TEX, MAGIC_PAL):
        raise FormatError("%s: magic %r is not 3TEX/3PAL" % (name, magic))
    count = r.u32(4, "count")
    if count == 0 or count > MAX_ENTRIES:
        raise FormatError("%s: entry count %d out of range" % (name, count))
    off = 8
    entries = []
    for i in range(count):
        where = "%s[%d]" % (name, i)
        r.aligned(off, 4, where)
        w, h, mode = r.u32(off), r.u32(off + 4), r.u32(off + 8)
        if mode not in (0, 1, 2):
            raise FormatError("%s: mode %d unknown" % (where, mode))
        _check_dims(w, h, mode, where)
        hdr = off
        pix_off = off + 12
        npix = pixel_bytes(w, h, mode)
        r.need(pix_off, npix, where + " pixels")
        cur = pix_off + npix
        engine_cur = pix_off + (npix & ~3)
        clut_count = 0
        if mode in (MODE_4BPP, MODE_8BPP):
            if magic == MAGIC_PAL:
                clut_count = r.u32(cur, where + " clut count")
                cur += 4
                engine_cur += 4
            else:
                clut_count = 1
            if not 1 <= clut_count <= 256:
                raise FormatError("%s: CLUT count %d out of range" % (where, clut_count))
        ncol = (16 if mode == MODE_4BPP else 256) * clut_count if mode != MODE_16BPP else 0
        clut_off = cur
        r.need(clut_off, ncol * 2, where + " CLUT")
        cluts = [[r.u16(clut_off + 2 * (k * (ncol // clut_count) + j))
                  for j in range(ncol // clut_count)] for k in range(clut_count)] if ncol else []
        entries.append({
            "index": i, "header_offset": hdr, "width": w, "height": h, "mode": mode,
            "bpp": (4, 8, 16)[mode], "pixel_offset": pix_off, "pixel_bytes": npix,
            "clut_offset": clut_off if ncol else None, "clut_count": clut_count,
            "engine_clut_offset": (engine_cur if ncol else None),
            "engine_layout_mismatch": bool(ncol) and engine_cur != clut_off,
            "_pixels": r.bytes(pix_off, npix), "_cluts": cluts,
        })
        off = clut_off + ncol * 2
    if off != len(r):
        raise FormatError("%s: %d trailing/missing bytes after last entry" % (name, len(r) - off))
    return {"magic": magic.decode("ascii"), "count": count, "entries": entries}


def decode_img(data, name="<img>"):
    """3IMG: char[4] magic, u32 count, entries {u32 w, u32 h, u32 mode, pixels}; no CLUTs.

    CLUTs live in the paired PLT (record i belongs to IMG entry i)."""
    r = Reader(data, name)
    r.magic(0, MAGIC_IMG)
    count = r.u32(4, "count")
    if count == 0 or count > MAX_ENTRIES:
        raise FormatError("%s: entry count %d out of range" % (name, count))
    off = 8
    entries = []
    for i in range(count):
        where = "%s[%d]" % (name, i)
        w, h, mode = r.u32(off), r.u32(off + 4), r.u32(off + 8)
        if mode not in (0, 1, 2):
            raise FormatError("%s: mode %d unknown" % (where, mode))
        _check_dims(w, h, mode, where)
        npix = pixel_bytes(w, h, mode)
        if npix % 4:
            raise FormatError("%s: pixel size %d breaks the engine's 4-byte cursor" % (where, npix))
        r.need(off + 12, npix, where + " pixels")
        entries.append({"index": i, "header_offset": off, "width": w, "height": h, "mode": mode,
                        "bpp": (4, 8, 16)[mode], "pixel_offset": off + 12, "pixel_bytes": npix,
                        "_pixels": r.bytes(off + 12, npix)})
        off += 12 + npix
    if off != len(r):
        raise FormatError("%s: %d trailing/missing bytes" % (name, len(r) - off))
    return {"count": count, "entries": entries}


def decode_plt(data, name="<plt>"):
    """3PLT: char[4] magic, u32 count, records {u32 reserved, u32 clut_count, clut_count*16 BGR555}."""
    r = Reader(data, name)
    r.magic(0, MAGIC_PLT)
    count = r.u32(4, "count")
    if count == 0 or count > MAX_ENTRIES:
        raise FormatError("%s: record count %d out of range" % (name, count))
    off = 8
    recs = []
    for i in range(count):
        where = "%s[%d]" % (name, i)
        reserved, n = r.u32(off), r.u32(off + 4)
        if not 1 <= n <= 256:
            raise FormatError("%s: CLUT count %d out of range" % (where, n))
        r.need(off + 8, 32 * n, where + " CLUTs")
        cluts = [[r.u16(off + 8 + 32 * k + 2 * j) for j in range(16)] for k in range(n)]
        recs.append({"index": i, "offset": off, "reserved": reserved, "clut_count": n, "_cluts": cluts})
        off += 8 + 32 * n
    if off != len(r):
        raise FormatError("%s: %d trailing/missing bytes" % (name, len(r) - off))
    return {"count": count, "records": recs}


def pair_img_plt(img, plt, name="<img/plt>"):
    if img["count"] != plt["count"]:
        raise FormatError("%s: IMG has %d entries but PLT has %d" % (name, img["count"], plt["count"]))
    for e, p in zip(img["entries"], plt["records"]):
        if e["mode"] == MODE_16BPP:
            continue
        need = 16 if e["mode"] == MODE_4BPP else 256
        if need > 16 * p["clut_count"]:
            raise FormatError("%s[%d]: %d-colour texture but PLT record holds %d colours"
                              % (name, e["index"], need, 16 * p["clut_count"]))
    return [(e, p) for e, p in zip(img["entries"], plt["records"])]


def render_rgba(entry, clut=None):
    """Return RGBA tuples for an entry using `clut` (list of BGR555) for indexed modes."""
    w, h, mode = entry["width"], entry["height"], entry["mode"]
    tex = _texels(entry["_pixels"], w, h, mode)
    if mode == MODE_16BPP:
        return [bgr555_to_rgba(v) for v in tex]
    if clut is None:
        raise FormatError("indexed texture needs a CLUT")
    lim = 16 if mode == MODE_4BPP else 256
    if len(clut) < lim:
        raise FormatError("CLUT has %d colours, need %d" % (len(clut), lim))
    pal = [bgr555_to_rgba(v) for v in clut[:lim]]
    return [pal[t] for t in tex]


FUL_FRAME_SIZES = {320 * 256 * 2: (320, 256), 160 * 120 * 2: (160, 120)}


def decode_ful(data, name="<ful>", width=None, height=None):
    """FUL: repeated {u32 frame_number (1-based, sequential), width*height BGR555}.

    The file stores no dimensions.  320x256 is proven by row autocorrelation and file
    arithmetic for six files; TK_BMP.FUL is 160x120 by the same evidence.  Callers may
    override; geometry that does not tile the file exactly is rejected."""
    r = Reader(data, name)
    candidates = [(width, height)] if width else [FUL_FRAME_SIZES[k] for k in sorted(FUL_FRAME_SIZES, reverse=True)]
    for (w, h) in candidates:
        fs = 4 + w * h * 2
        if len(r) == 0 or len(r) % fs:
            continue
        n = len(r) // fs
        if all(r.u32(k * fs) == k + 1 for k in range(n)):
            return {"width": w, "height": h, "frames": n,
                    "frame_offsets": [k * fs + 4 for k in range(n)], "_reader": r}
    raise FormatError("%s: no frame geometry tiles the file with sequential frame numbers" % name)


def ful_frame_rgba(ful, k):
    r, w, h = ful["_reader"], ful["width"], ful["height"]
    base = ful["frame_offsets"][k]
    # Full-screen frames are drawn as 16-bit direct colour; 0x0000 is opaque black here.
    return [bgr555_to_rgba(r.u16(base + 2 * i))[:3] + (255,) for i in range(w * h)]
