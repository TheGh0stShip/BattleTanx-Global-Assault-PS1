"""MMM / TTT / 3MDL model decoders and the 3MDL command-stream interpreter.

Evidence (SLUS_010.44):
  * MMM loader 0x8003BF88: "MM01", u32 count, count x 12-byte entries, then a data blob;
    entry[0] == -1 means empty; otherwise entry[2] = blob+off (CM01) and entry[0] =
    blob+off+0x24 (3MDL).
  * TTT parse in the level loader (0x8003D9F8..0x8003DA74 for ENUMS, 0x8003DB70.. for the
    level): "TT01", u32 count, per model {"LBTX", u32 n, n x u32 texture index}; each
    index is rebased into the IMG/PLT texture-record array of the same set.
  * Model job queue 0x80069D68: scratch = 3MDL[+8] * 8 bytes; CM01+0x22 is the s16 cull radius.
  * Vertex transform 0x8007E570: RTPT over 8-byte {s16 x, s16 y, s16 z, s16 pad} records.
  * Command interpreter 0x8007D708..0x8007D790 with handler table 0x8007DC30 (64 slots,
    two instructions each) and primitive emitter table 0x8007DD78 (16 pointers).
"""
from math import isqrt

from .binio import FormatError, Reader

MAX_MODELS = 4096
MAX_VERTS = 4096          # vertex indices are 12-bit fields in the paired-index commands


def decode_ttt(data, name="<ttt>"):
    r = Reader(data, name)
    r.magic(0, b"TT01")
    count = r.u32(4, "count")
    if count > MAX_MODELS:
        raise FormatError("%s: model count %d out of range" % (name, count))
    off, lists = 8, []
    for i in range(count):
        r.magic(off, b"LBTX")
        n = r.u32(off + 4, "texture count")
        if n > 4096:
            raise FormatError("%s[%d]: texture count %d out of range" % (name, i, n))
        lists.append({"index": i, "offset": off, "textures": [r.u32(off + 8 + 4 * k) for k in range(n)]})
        off += 8 + 4 * n
    if off != len(r):
        raise FormatError("%s: %d trailing/missing bytes" % (name, len(r) - off))
    return {"count": count, "models": lists}


def _sext8(v):
    return v - 256 if v & 0x80 else v


def _normal(word):
    """Packed normal exactly as handlers 0x8007E0B8.. unpack it into GTE V0 (1.0 == 4096)."""
    x = (word >> 19) & 0x1FFF
    if x & 0x1000:
        x -= 0x2000
    y = _sext8((word >> 16) & 0xFF) << 5
    z = _sext8((word >> 8) & 0xFF) << 5
    return (x, y, z)


# word & 0xFC -> semantic, from the handler table at 0x8007DC30
TAG_COLOR = (0x00, 0x04, 0x08, 0x0C)
TAG_NORMAL = (0x10, 0x14, 0x18, 0x1C)
TAG_NORMAL_ALT = (0x90, 0x94, 0x98, 0x9C)   # same handlers as 0x10..0x1C
TAG_UV = (0x20, 0x24, 0x28, 0x2C)
TAG_UV_AUX = (0x80, 0x84, 0x88, 0x8C)       # UV plus bits 22..31 stored to scratch+0x40
TAG_VERT = (0x30, 0x34, 0x38, 0x3C)
TAG_VERT_PAIR = {0x40: (0, 1), 0x44: (1, 2), 0x48: (2, 3), 0x4C: (0, 2), 0x50: (0, 3), 0x54: (1, 3)}
TAG_TEXTURE, TAG_PRIMTYPE, TAG_NOP = 0x58, 0x5C, 0x60
TAG_SKIP1, TAG_END, TAG_SKIP_PARAM, TAG_SKIP2 = 0x64, 0x68, 0x6C, 0x70
TAG_NOP2 = (0x74, 0x78, 0x7C)
TAG_SEMITRANS = 0xA0
# Stream corner -> GPU vertex slot for 4-corner primitives (emitters 0x8007DF00/0x8007E008).
QUAD_GPU_SLOT_ORDER = (0, 1, 3, 2)
GP0_CODE = {0: 0x20, 1: 0x28, 4: 0x30, 5: 0x38, 8: 0x24, 9: 0x2C, 12: 0x34, 13: 0x3C}


def interpret_3mdl(r, base, nverts, size, ntex, where):
    """Walk a 3MDL command stream; return primitives and stream facts.

    Conditional blocks (0x64/0x6C/0x70) are entered (all variants visible) and every
    primitive records the stack of (tag, masks) guards that enclose it."""
    p = base + 24 + 8 * nverts
    end = base + size
    state = {"color": [None] * 4, "normal": [None] * 4, "uv": [None] * 4, "uv_aux": [None] * 4,
             "vert": [None] * 4, "texture": None, "ptype": None, "semitrans": 0}
    prims, guards, words = [], [], 0
    terminated = False
    while p < end:
        while guards and p >= guards[-1]["end"]:
            guards.pop()
        w = r.u32(p, where + " command")
        at = p
        p += 4
        words += 1
        tag, pl = w & 0xFC, w >> 8
        if tag in TAG_COLOR:
            state["color"][TAG_COLOR.index(tag)] = pl & 0xFFFFFF
        elif tag in TAG_NORMAL or tag in TAG_NORMAL_ALT:
            k = (tag & 0x7F) // 4 - 4
            state["normal"][k] = _normal(w)
        elif tag in TAG_UV or tag in TAG_UV_AUX:
            k = (tag & 0x7F) // 4 - 8
            state["uv"][k] = (pl & 0xFF, (pl >> 8) & 0xFF)
            state["uv_aux"][k] = (w >> 22) if tag in TAG_UV_AUX else None
        elif tag in TAG_VERT:
            if pl >= nverts:
                raise FormatError("%s: vertex %d >= %d at 0x%X" % (where, pl, nverts, at))
            state["vert"][TAG_VERT.index(tag)] = pl
        elif tag in TAG_VERT_PAIR:
            a, b = TAG_VERT_PAIR[tag]
            lo, hi = pl & 0xFFF, pl >> 12
            if lo >= nverts or hi >= nverts:
                raise FormatError("%s: vertex pair (%d,%d) >= %d at 0x%X" % (where, hi, lo, nverts, at))
            state["vert"][a], state["vert"][b] = hi, lo
        elif tag == TAG_TEXTURE:
            state["texture"] = w >> 24
        elif tag == TAG_PRIMTYPE:
            state["ptype"] = w >> 28
        elif tag == TAG_SEMITRANS:
            state["semitrans"] = (w >> 16) & 3
        elif tag == TAG_END:
            terminated = True
            break
        elif tag in (TAG_SKIP1, TAG_SKIP_PARAM, TAG_SKIP2):
            nmask, extra = {TAG_SKIP1: (1, 0), TAG_SKIP_PARAM: (1, 16), TAG_SKIP2: (2, 16)}[tag]
            masks = [r.u32(p + 4 * k, where + " guard mask") for k in range(nmask)]
            params = r.bytes(p + 4 * nmask, extra, where + " guard params")
            block_end = at + pl          # skip target: guard word + payload bytes
            if block_end > end or block_end < p + 4 * nmask + extra:
                raise FormatError("%s: guard block 0x%X..0x%X outside stream" % (where, at, block_end))
            guard = {"tag": tag, "masks": masks, "params": params.hex(),
                     "start": at - base, "end": block_end}
            if tag == TAG_SKIP2:
                label_bytes = params.split(b"\0", 1)[0]
                if not label_bytes or params[len(label_bytes):].strip(b"\0"):
                    raise FormatError("%s: named visibility block at 0x%X has invalid label padding" %
                                      (where, at))
                try:
                    guard["submesh_name"] = label_bytes.decode("ascii")
                except UnicodeDecodeError:
                    raise FormatError("%s: named visibility block at 0x%X has a non-ASCII label" %
                                      (where, at))
                guard["visibility_channel_masks"] = masks
            guards.append(guard)
            p += 4 * nmask + extra
        elif tag == TAG_NOP or tag in TAG_NOP2:
            pass
        else:
            raise FormatError("%s: unknown command 0x%08X at 0x%X" % (where, w, at))
        emit = w & 3
        if emit:
            pt = state["ptype"]
            if pt is None:
                raise FormatError("%s: primitive emitted before a type was set (0x%X)" % (where, at))
            n = 4 if pt & 1 else 3
            if any(v is None for v in state["vert"][:n]):
                raise FormatError("%s: primitive uses an unset corner (0x%X)" % (where, at))
            textured = bool(pt & 8)
            if textured and (state["texture"] is None or state["texture"] >= ntex):
                raise FormatError("%s: textured primitive selects texture %r of %d" % (where, state["texture"], ntex))
            prims.append({
                "stream_offset": at - base, "type": pt & 0xD, "type_raw": pt,
                "gp0_code": GP0_CODE.get(pt & 0xD), "corners": n,
                "textured": textured, "gouraud": bool(pt & 4),
                "cull": {1: "front_if_nclip_negative", 2: "front_if_nclip_non_negative", 3: "double_sided"}[emit],
                "vertices": list(state["vert"][:n]),
                "colors": list(state["color"][:n]) if pt & 4 else [state["color"][0]],
                "normals": list(state["normal"][:n]),
                "uvs": list(state["uv"][:n]) if textured else None,
                "uv_aux": list(state["uv_aux"][:n]) if textured else None,
                "texture_slot": state["texture"] if textured else None,
                "semitrans": state["semitrans"],
                "guards": [{k: g[k] for k in ("tag", "masks", "params", "submesh_name",
                                               "visibility_channel_masks") if k in g} for g in guards],
            })
    if not terminated:
        raise FormatError("%s: stream not terminated by 0x68" % where)
    return {"primitives": prims, "end_offset": p - base, "command_words": words}


def decode_mmm(data, name="<mmm>", ttt=None):
    """Decode every model; `ttt` (decode_ttt result) bounds texture slots when given."""
    r = Reader(data, name)
    r.magic(0, b"MM01")
    count = r.u32(4, "count")
    if count > MAX_MODELS:
        raise FormatError("%s: model count %d out of range" % (name, count))
    if ttt is not None and ttt["count"] != count:
        raise FormatError("%s: MMM has %d models but TTT has %d" % (name, count, ttt["count"]))
    blob = 8 + 12 * count
    r.need(blob, 0, "model table")
    models, spans = [], []
    for i in range(count):
        where = "%s[%d]" % (name, i)
        off = r.s32(8 + 12 * i)
        f1, f2 = r.u32(12 + 12 * i), r.u32(16 + 12 * i)
        if off == -1:
            models.append({"index": i, "empty": True, "table_words": [off, f1, f2]})
            continue
        if off < 0:
            raise FormatError("%s: negative offset %d" % (where, off))
        o = blob + off
        r.aligned(o, 4, where)
        r.magic(o, b"CM01")
        hdr = [r.s16(o + 4 + 2 * k) for k in range(16)]
        m = o + 0x24
        r.magic(m, b"3MDL")
        unk4, nverts, nprims, flags, size = (r.u32(m + 4 + 4 * k) for k in range(5))
        if flags != 0x47F:
            raise FormatError("%s: 3MDL format flags 0x%X != 0x47F" % (where, flags))
        if not 1 <= nverts <= MAX_VERTS:
            raise FormatError("%s: vertex count %d out of range" % (where, nverts))
        r.need(m, size, where + " 3MDL chunk")
        if size < 24 + 8 * nverts + 4:
            raise FormatError("%s: chunk size %d too small" % (where, size))
        verts = [(r.s16(m + 24 + 8 * k), r.s16(m + 26 + 8 * k), r.s16(m + 28 + 8 * k), r.u16(m + 30 + 8 * k))
                 for k in range(nverts)]
        if any(v[3] & 0x7FFF for v in verts):
            raise FormatError("%s: vertex flag contains bits other than group-end bit 15" % where)
        vertex_group_ends = [k for k, v in enumerate(verts) if v[3] & 0x8000]
        empty_vertex_groups = unk4 - len(vertex_group_ends)
        if empty_vertex_groups not in (0, 1):
            raise FormatError("%s: %d vertex groups but %d group terminators" %
                              (where, unk4, len(vertex_group_ends)))
        ntex = len(ttt["models"][i]["textures"]) if ttt is not None else 256
        stream = interpret_3mdl(r, m, nverts, size, ntex, where)
        if stream["end_offset"] != size:
            raise FormatError("%s: stream ends at 0x%X, chunk size 0x%X" % (where, stream["end_offset"], size))
        mn = [min(v[a] for v in verts) for a in range(3)]
        mx = [max(v[a] for v in verts) for a in range(3)]
        bbox_ok = (hdr[0:3] == [int(x / 4) for x in mn] and hdr[4:7] == [int(x / 4) for x in mx]
                   and hdr[3] == 0 and hdr[7] == 0)
        if hdr[8:11] != hdr[12:15]:
            raise FormatError("%s: CM01 duplicated bounds centers disagree" % where)
        bbox_span = [hdr[4 + axis] - hdr[axis] for axis in range(3)]
        bbox_diagonal = isqrt(sum(x * x for x in bbox_span))
        if hdr[11] != bbox_diagonal:
            raise FormatError("%s: CM01 bounding-box diagonal %d != calculated %d" %
                              (where, hdr[11], bbox_diagonal))
        spans.append((o, m + size, i))
        models.append({
            "index": i, "empty": False, "table_words": [off, f1, f2], "offset": o, "length": 0x24 + size,
            "cm01": {"bbox_min_div4": hdr[0:3], "bbox_max_div4": hdr[4:7], "bbox_matches_vertices": bbox_ok,
                     "bounds_center": hdr[8:11], "bbox_diagonal_div4_0x1A": hdr[11],
                     "cull_radius_s16_0x22": hdr[15]},
            "mdl": {"vertex_group_count": unk4, "vertex_group_end_indices": vertex_group_ends,
                    "empty_vertex_groups": empty_vertex_groups, "vertex_count": nverts,
                    "primitive_count_field": nprims, "format_flags_0x10": flags, "chunk_size": size},
            "vertices": verts, **stream,
            "primitive_count_matches": nprims == len(stream["primitives"]),
        })
    spans.sort()
    for (a0, a1, i0), (b0, b1, i1) in zip(spans, spans[1:]):
        if b0 < a1:
            raise FormatError("%s: model %d overlaps model %d" % (name, i0, i1))
    if spans and spans[-1][1] > len(r):
        raise FormatError("%s: last model runs past EOF" % name)
    tail = len(r) - (spans[-1][1] if spans else blob)
    return {"count": count, "models": models, "blob_offset": blob, "trailing_bytes": tail}


def model_to_obj(model, name, texture_sizes=None):
    """Export one decoded model as Wavefront OBJ text (proven fields only).

    Model space is +Y up (4713/4761 models have bbox min y >= 0, i.e. they stand on
    y = 0) and, because the engine's view matrix flips Y into GTE screen space, it is
    left-handed; the OBJ negates Z only, giving right-handed +Y-up coordinates.  Stream corners c0..c3
    are perimeter order: the quad emitters (0x8007DF00, 0x8007E008) place them into GPU
    slots as c0, c1, c3, c2, so the OBJ polygon is c0, c1, c2, c3.  Faces whose cull mode
    selects negative NCLIP as front (cull mode 1) are reversed: with this conversion,
    signed-volume tests give outward CCW faces for 1563/1644 mode-1 and 817/856 mode-2
    closed shells (first 40 MMM files); double-sided faces keep stored order.
    texture_sizes: optional list of (w, h) per texture slot to normalise UVs."""
    out = ["# %s model %d (BattleTanx GA PS1), raw->OBJ: (x, y, -z)" % (name, model["index"])]
    for (x, y, z, _pad) in model["vertices"]:
        out.append("v %d %d %d" % (x, y, -z))
    vt = []
    faces = []
    for prim in model["primitives"]:
        order = [0, 1, 2, 3] if prim["corners"] == 4 else [0, 1, 2]
        if prim["cull"] == "front_if_nclip_negative":
            order = order[::-1]
        idx = [prim["vertices"][k] + 1 for k in order]
        if prim["textured"] and texture_sizes is not None:
            tw, th = texture_sizes[prim["texture_slot"]]
            base = len(vt)
            for k in order:
                u, v = prim["uvs"][k]
                vt.append("vt %.6f %.6f" % ((u + 0.5) / tw, 1.0 - (v + 0.5) / th))
            faces.append((prim["texture_slot"], "f " + " ".join("%d/%d" % (vi, base + j + 1) for j, vi in enumerate(idx))))
        else:
            faces.append((None, "f " + " ".join(str(vi) for vi in idx)))
    out.extend(vt)
    cur = object()
    for slot, f in faces:
        if slot != cur:
            out.append("usemtl tex%s" % ("none" if slot is None else slot))
            cur = slot
        out.append(f)
    return "\n".join(out) + "\n"
