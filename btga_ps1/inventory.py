"""Corpus inventory: classify, decode and fingerprint every file of the extracted disc.

usage: python -m btga_ps1.inventory EXTRACTED_DIR OUT_DIR [--previews] [--obj] [--wav]

Writes OUT_DIR/manifest.json (deterministic: sorted keys, no timestamps, no host paths),
and with --previews / --obj / --wav, PNG sheets, OBJ models, and WAV effects under OUT_DIR. Nothing is
ever written inside EXTRACTED_DIR.
"""
import hashlib
import json
import os
import sys

from . import audio, level, metadata, models, textures
from .binio import FormatError
from .png import encode_rgba


def sha(b):
    return hashlib.sha256(b).hexdigest()


def _read_bytes(path):
    with open(path, "rb") as fh:
        return fh.read()


def rel(root, path):
    return os.path.relpath(path, root).replace(os.sep, "/")


def _tex_summary(dec, data):
    out = []
    for e in dec["entries"]:
        end = (e["clut_offset"] + 2 * len(e["_cluts"]) * len(e["_cluts"][0])) if e["_cluts"] else e["pixel_offset"] + e["pixel_bytes"]
        out.append({k: v for k, v in e.items() if not k.startswith("_")} | {
            "byte_range": [e["header_offset"], end], "sha256": sha(data[e["header_offset"]:end])})
    return out


def _sheet(images):
    """Pack (w, h, rgba) tiles left-to-right into rows no wider than 1024 px."""
    rows, row, rw, rh, W = [], [], 0, 0, 0
    for w, h, px in images:
        if row and rw + w + 2 > 1024:
            rows.append((row, rh)); W = max(W, rw); row, rw, rh = [], 0, 0
        row.append((rw, w, h, px)); rw += w + 2; rh = max(rh, h)
    if row:
        rows.append((row, rh)); W = max(W, rw)
    H = sum(h + 2 for _, h in rows)
    canvas = [(0, 0, 0, 0)] * (W * H)
    y0 = 0
    for row, rh in rows:
        for x0, w, h, px in row:
            for y in range(h):
                canvas[(y0 + y) * W + x0:(y0 + y) * W + x0 + w] = px[y * w:(y + 1) * w]
        y0 += rh + 2
    return W, H, canvas


def run(root, out, previews=False, objs=False, wavs=False):
    root = os.path.abspath(root)
    out = os.path.abspath(out)
    if out == root or out.startswith(root + os.sep):
        raise SystemExit("refusing to write inside the extracted disc directory")
    os.makedirs(out, exist_ok=True)
    files = sorted(os.path.join(d, f) for d, _, fs in os.walk(root) for f in fs)
    by_rel = {rel(root, p): p for p in files}
    upper = {k.upper(): k for k in by_rel}
    manifest = {"tool": "btga_ps1.inventory", "files": {}, "summary": {}}
    texsets = {}

    def sib(r, ext):
        return upper.get(r.rsplit(".", 1)[0].upper() + "." + ext)

    for r in sorted(by_rel):
        data = _read_bytes(by_rel[r])
        ext = r.rsplit(".", 1)[-1].upper() if "." in r else ""
        ent = {"size": len(data), "sha256": sha(data), "family": ext, "status": "accepted"}
        try:
            if ext == "TEX":
                dec = textures.decode_tex(data, r)
                ent["decoded"] = {"magic": dec["magic"], "count": dec["count"], "entries": _tex_summary(dec, data)}
                if previews:
                    imgs = [(e["width"], e["height"], textures.render_rgba(e, e["_cluts"][0] if e["_cluts"] else None))
                            for e in dec["entries"]]
                    _write_png(out, r, imgs)
            elif ext == "IMG":
                plt_r = sib(r, "PLT")
                if plt_r is None:
                    raise FormatError("IMG without PLT")
                img = textures.decode_img(data, r)
                plt = textures.decode_plt(_read_bytes(by_rel[plt_r]), plt_r)
                pairs = textures.pair_img_plt(img, plt, r)
                texsets[r.rsplit(".", 1)[0].upper()] = [(e["width"], e["height"]) for e in img["entries"]]
                ent["decoded"] = {"count": img["count"], "paired_plt": plt_r, "entries": [
                    {k: v for k, v in e.items() if not k.startswith("_")} | {
                        "plt_record": p["index"], "plt_clut_count": p["clut_count"],
                        "byte_range": [e["header_offset"], e["pixel_offset"] + e["pixel_bytes"]],
                        "sha256": sha(data[e["header_offset"]:e["pixel_offset"] + e["pixel_bytes"]])}
                    for e, p in pairs]}
                if previews:
                    _write_png(out, r, [(e["width"], e["height"], textures.render_rgba(e, p["_cluts"][0])) for e, p in pairs])
            elif ext == "PLT":
                plt = textures.decode_plt(data, r)
                ent["decoded"] = {"count": plt["count"], "records": [
                    {"index": p["index"], "offset": p["offset"], "reserved": p["reserved"], "clut_count": p["clut_count"],
                     "sha256": sha(data[p["offset"]:p["offset"] + 8 + 32 * p["clut_count"]])} for p in plt["records"]]}
            elif ext == "FUL":
                ful = textures.decode_ful(data, r)
                ent["decoded"] = {"width": ful["width"], "height": ful["height"], "frames": ful["frames"],
                                  "frame_offsets": ful["frame_offsets"],
                                  "frame_sha256": [sha(data[o:o + 2 * ful["width"] * ful["height"]]) for o in ful["frame_offsets"]]}
                if previews:
                    _write_png(out, r, [(ful["width"], ful["height"], textures.ful_frame_rgba(ful, 0))], suffix="_frame1")
            elif ext == "TTT":
                t = models.decode_ttt(data, r)
                ent["decoded"] = {"count": t["count"], "texture_refs": sum(len(m["textures"]) for m in t["models"])}
            elif ext == "MMM":
                ttt_r = sib(r, "TTT")
                ttt = models.decode_ttt(_read_bytes(by_rel[ttt_r]), ttt_r) if ttt_r else None
                mm = models.decode_mmm(data, r, ttt)
                img_r = sib(r, "IMG")
                ent["decoded"] = {"count": mm["count"], "paired_ttt": ttt_r, "paired_img": img_r,
                                  "trailing_bytes": mm["trailing_bytes"], "models": [_model_summary(m, data, ttt) for m in mm["models"]]}
                if objs:
                    sizes = None
                    if img_r and ttt is not None:
                        img = textures.decode_img(_read_bytes(by_rel[img_r]), img_r)
                        dims = [(e["width"], e["height"]) for e in img["entries"]]
                    for m in mm["models"]:
                        if m["empty"]:
                            continue
                        if img_r and ttt is not None:
                            sizes = [dims[t] for t in ttt["models"][m["index"]]["textures"]]
                        _write_text(out, "obj/%s/%03d.obj" % (r.replace("/", "_"), m["index"]), models.model_to_obj(m, r, sizes))
            elif ext == "FLB":
                tex_r = sib(r, "TEX")
                nt = textures.decode_tex(_read_bytes(by_rel[tex_r]), tex_r)["count"] if tex_r else None
                f = level.decode_flb(data, r, nt)
                ent["decoded"] = {k: v for k, v in f.items() if k != "cells"} | {"paired_tex": tex_r, "tex_count": nt}
            elif ext == "BIN":
                head = int.from_bytes(data[0:4], "little") if len(data) >= 4 else None
                if head == 0x20:
                    b = level.decode_level_bin(data, r)
                    ent["family"] = "BIN-level"
                    ent["decoded"] = {"section_offsets": b["section_offsets"], "section_sizes": b["section_sizes"],
                                      "placements": len(b["placements"]), "active_first": b["active_first"],
                                      "active_count": b["active_count"], "groups": b["groups"],
                                      "object_records": len(b["object_records"]),
                                      "object_opcode_histogram": _top(x["opcode"] for x in b["object_records"]),
                                      "model_names": len(b["model_names"]),
                                      "yaw_histogram_top": _top(p["yaw_u16"] for p in b["placements"])}
                else:
                    stem = r.rsplit("/", 1)[-1].rsplit(".", 1)[0].upper()
                    if stem not in level.FONT_SHEETS:
                        raise FormatError("BIN is neither a level container nor a known font table")
                    sheet_r = upper.get((r.rsplit("/", 1)[0] + "/" if "/" in r else "").upper() + level.FONT_SHEETS[stem] + ".TEX")
                    sheet = textures.decode_tex(_read_bytes(by_rel[sheet_r]), sheet_r)["entries"][0] if sheet_r else None
                    g = level.decode_font_bin(data, r, (sheet["width"], sheet["height"]) if sheet else None)
                    ent["family"] = "BIN-font"
                    ent["decoded"] = {"glyphs": len(g["glyphs"]), "absent_glyphs": g["absent"], "paired_sheet": sheet_r,
                                      "glyph_rects": g["glyphs"]}
            elif ext == "SFX":
                s = level.decode_sfx(data, r)
                ent["decoded"] = {k: v for k, v in s.items() if k != "entries"} | {
                    "entry_spu_offsets": [e["spu_offset"] for e in s["entries"]],
                    "entry_data_bytes": [e["data_bytes"] for e in s["entries"]],
                    "pitch_histogram": _top(e["pitch"] for e in s["entries"])}
                if wavs:
                    for i, e in enumerate(s["entries"]):
                        start = s["data_offset"] + e["spu_offset"]
                        raw = data[start:start + e["data_bytes"]]
                        dec = audio.decode_spu_adpcm(raw, "%s entry %d" % (r, i))
                        rate = audio.pitch_sample_rate(e["pitch"])
                        _write_bytes(out, "wav/%s/%03d.wav" % (r.replace("/", "_"), i),
                                     audio.encode_wav_mono16(dec["samples"], rate))
            elif ext in ("STR", "PCK"):
                ent["decoded"] = level.inventory_xa(data, r)
            elif ext == "TXT":
                ent["family"] = "TXT-ASCII"
                ent["decoded"] = metadata.decode_ascii_text(data, r)
            elif ext == "CNF":
                ent["family"] = "CNF-system"
                ent["decoded"] = metadata.decode_system_cnf(data, r)
            elif ext == "44":
                ent["family"] = "PS-X-EXE"
                dec = metadata.decode_psx_exe(data, r)
                dec["header_sha256"] = sha(data[:dec["header_bytes"]])
                dec["text_sha256"] = sha(data[dec["text_offset"]:])
                ent["decoded"] = dec
            elif ext == "DAT":
                ent["family"] = "DAT-licence"
                dec = metadata.decode_licence_sectors(data, r)
                dec["sector_sha256"] = [sha(data[s["offset"]:s["offset"] + dec["sector_bytes"]])
                                          for s in dec["sectors"]]
                ent["decoded"] = dec
            else:
                ent["status"] = "rejected"
                ent["reason"] = "no decoder for this family"
        except FormatError as e:
            ent["status"] = "rejected"
            ent["reason"] = str(e)
        manifest["files"][r] = ent
    s = {}
    for r, e in manifest["files"].items():
        key = e["family"] + ":" + e["status"]
        s[key] = s.get(key, 0) + 1
    manifest["summary"] = dict(sorted(s.items()))
    manifest["file_count"] = len(manifest["files"])
    with open(os.path.join(out, "manifest.json"), "w", newline="\n") as fh:
        json.dump(manifest, fh, sort_keys=True, indent=1)
        fh.write("\n")
    return manifest


def _top(it, n=8):
    h = {}
    for x in it:
        h[x] = h.get(x, 0) + 1
    return [[k, v] for k, v in sorted(h.items(), key=lambda kv: (-kv[1], kv[0]))[:n]]


def _model_summary(m, data, ttt):
    if m["empty"]:
        return {"index": m["index"], "empty": True}
    prims = m["primitives"]
    kinds = {}
    for p in prims:
        k = "%s%s%d" % ("T" if p["textured"] else "", "G" if p["gouraud"] else "F", p["corners"])
        kinds[k] = kinds.get(k, 0) + 1
    return {"index": m["index"], "offset": m["offset"], "length": m["length"],
            "sha256": sha(data[m["offset"]:m["offset"] + m["length"]]),
            "vertices": len(m["vertices"]), "primitives": len(prims), "primitive_kinds": dict(sorted(kinds.items())),
            "primitive_count_matches_header": m["primitive_count_matches"],
            "guarded_primitives": sum(1 for p in prims if p["guards"]),
            "double_sided": sum(1 for p in prims if p["cull"] == "double_sided"),
            "texture_slots": ttt["models"][m["index"]]["textures"] if ttt is not None else None,
            "cm01": m["cm01"], "mdl": m["mdl"],
            "vertex_group_end_count": len(m["mdl"]["vertex_group_end_indices"])}


def _write_png(out, r, images, suffix=""):
    w, h, px = _sheet(images)
    _write_bytes(out, "png/" + r.replace("/", "_") + suffix + ".png", encode_rgba(w, h, px))


def _write_text(out, relpath, text):
    _write_bytes(out, relpath, text.encode("ascii"))


def _write_bytes(out, relpath, b):
    p = os.path.join(out, relpath)
    os.makedirs(os.path.dirname(p), exist_ok=True)
    with open(p, "wb") as fh:
        fh.write(b)


def main(argv=None):
    argv = list(sys.argv[1:] if argv is None else argv)
    previews = "--previews" in argv
    objs = "--obj" in argv
    wavs = "--wav" in argv
    args = [a for a in argv if not a.startswith("--")]
    if len(args) != 2:
        print(__doc__)
        return 2
    m = run(args[0], args[1], previews, objs, wavs)
    for k, v in m["summary"].items():
        print("%-28s %d" % (k, v))
    rej = [(r, e["reason"]) for r, e in m["files"].items() if e["status"] == "rejected"]
    print("files: %d, rejected: %d" % (m["file_count"], len(rej)))
    for r, why in rej:
        print("  REJECTED %s: %s" % (r, why))
    return 0


if __name__ == "__main__":
    sys.exit(main())
