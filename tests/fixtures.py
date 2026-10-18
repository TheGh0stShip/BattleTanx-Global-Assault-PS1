"""Synthetic fixture builders.  No retail bytes are used anywhere in the unit tests."""
import struct


def u32(*v):
    return struct.pack("<%dI" % len(v), *v)


def tex_4bpp(w=4, h=2, magic=b"3TEX", pal_count=None):
    pix = bytes((2 * i) & 0xF | (((2 * i + 1) & 0xF) << 4) for i in range(w * h // 2))
    clut = struct.pack("<16H", *[(k * 0x0421) & 0x7FFF for k in range(16)])
    body = u32(w, h, 0) + pix
    if pal_count is not None:
        body += u32(pal_count) + clut * pal_count
    else:
        body += clut
    return magic + u32(1) + body


def tex_8bpp(w=3, h=2):
    pix = bytes(range(w * h))
    clut = struct.pack("<256H", *[k for k in range(256)])
    return b"3TEX" + u32(1) + u32(w, h, 1) + pix + clut


def tex_16bpp(w=2, h=2):
    return b"3TEX" + u32(1) + u32(w, h, 2) + struct.pack("<4H", 0x001F, 0x03E0, 0x7C00, 0x0000)


def img_plt(n=2, w=4, h=2, clut_counts=(1, 9)):
    img = b"3IMG" + u32(n)
    plt = b"3PLT" + u32(n)
    for i in range(n):
        img += u32(w, h, 0) + bytes([0x10 * i + 1] * (w * h // 2))
        c = clut_counts[i % len(clut_counts)]
        plt += u32(0, c) + struct.pack("<16H", *[(i + k) & 0x7FFF for k in range(16)]) * c
    return img, plt


def ful(w=320, h=256, frames=2):
    out = b""
    for k in range(frames):
        out += u32(k + 1) + struct.pack("<H", 0x7FFF) * (w * h)
    return out


def mdl_stream(words):
    return b"".join(struct.pack("<I", w) for w in words)


def model(verts, words, prims=None, unk4=1, flags=0x47F):
    vb = b"".join(struct.pack("<4h", *v) for v in verts)
    stream = mdl_stream(words)
    size = 24 + len(vb) + len(stream)
    nprims = sum(1 for w in words if w & 3) if prims is None else prims
    mdl = b"3MDL" + u32(unk4, len(verts), nprims, flags, size) + vb + stream
    xs = [v[0] for v in verts]; ys = [v[1] for v in verts]; zs = [v[2] for v in verts]
    q = lambda x: int(x / 4)
    cm = b"CM01" + struct.pack("<16h", q(min(xs)), q(min(ys)), q(min(zs)), 0, q(max(xs)), q(max(ys)), q(max(zs)), 0,
                               0, 0, 0, 0, 0, 0, 0, 64)
    return cm + mdl


def quad_model():
    verts = [(0, 0, 0, 0), (64, 0, 0, 0), (64, 64, 0, 0), (0, 64, 0, -32768)]
    words = [0x00000058, 0xD000005C, 0x00000020, 0x00003F24, 0x003F3F28, 0x003F002C,
             (0x000 << 20) | (0x001 << 8) | 0x40,      # c0 = v0, c1 = v1
             (0x002 << 20) | (0x003 << 8) | 0x48,      # c2 = v2, c3 = v3
             0x00808000, 0x00808004, 0x00808008, 0x0080800D,   # colours, last emits (mode 1)
             0x00000068]
    return verts, words


def mmm_ttt(models_bytes, tex_lists):
    n = len(models_bytes)
    table, blob = b"", b""
    for m in models_bytes:
        if m is None:
            table += struct.pack("<iII", -1, 0, 0)
        else:
            table += struct.pack("<iII", len(blob), 0, 0)
            blob += m
    mmm = b"MM01" + u32(n) + table + blob
    ttt = b"TT01" + u32(n) + b"".join(b"LBTX" + u32(len(t), *t) for t in tex_lists)
    return mmm, ttt


def flb(w=64, h=256, tile=5):
    cells = [(tile << 18) | (k & 0x7FFF) for k in range(w * h)]
    return struct.pack("<HH", w, h) + struct.pack("<%dI" % len(cells), *cells)


def level_bin(n=3, object_records=None):
    if object_records is None:
        object_records = [bytes([7, 0, 0, 0]) for _ in range(n)]
    n = len(object_records)
    sec0 = u32(2)
    sec1 = struct.pack("<HHhhhhhh", n - 1, 1, -10, -5, -20, 10, 5, 20) + bytes(16)
    object_offsets, sec3 = [], b""
    for record in object_records:
        object_offsets.append(len(sec3))
        sec3 += record
    sec2 = b"".join(struct.pack("<hhhHI", 10 * i, 0, -10 * i, 16384 * i & 0xFFFF, object_offsets[i])
                    for i in range(n))
    offs = [0x20]
    for s in (sec0, sec1, sec2, sec3):
        offs.append(offs[-1] + len(s))
    sec4 = u32(offs[4] + 8, 0) + b"fixture\0"
    return u32(*offs, 0, 0, 0) + sec0 + sec1 + sec2 + sec3 + sec4


def sfx(count=2, data_len=64):
    size = data_len // count
    table = b"".join(u32(size * i, size, 1, 0x3FFF, 0xFFFF0400) for i in range(count))
    return b"1SFX" + u32(20 + len(table), data_len, len(table), count) + table + bytes(data_len)


def xa_sectors(kinds=(0x64, 0x62)):
    out = b""
    for sm in kinds:
        sub = bytes([1, 0, sm, 0])
        out += sub + sub + bytes(2328)
    return out
