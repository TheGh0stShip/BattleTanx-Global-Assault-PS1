import os
import struct
import tempfile
import unittest

from btga_ps1 import audio, level, media, metadata, models, textures
from btga_ps1.binio import FormatError, Reader, bgr555_to_rgba
from btga_ps1.png import encode_rgba
from tests import fixtures as fx


class BinIO(unittest.TestCase):
    def test_little_endian(self):
        r = Reader(b"\x01\x02\x03\x04\xff\xff")
        self.assertEqual(r.u32(0), 0x04030201)
        self.assertEqual(r.u16(0), 0x0201)
        self.assertEqual(r.s16(4), -1)

    def test_bounds(self):
        r = Reader(b"\x00" * 4)
        self.assertRaises(FormatError, r.u32, 1)
        self.assertRaises(FormatError, r.u16, 3)
        self.assertRaises(FormatError, r.bytes, 0, 5)
        self.assertRaises(FormatError, r.need, -1, 1)

    def test_alignment(self):
        self.assertRaises(FormatError, Reader(bytes(8)).aligned, 2, 4)

    def test_bgr555(self):
        self.assertEqual(bgr555_to_rgba(0x001F), (255, 0, 0, 255))
        self.assertEqual(bgr555_to_rgba(0x03E0), (0, 255, 0, 255))
        self.assertEqual(bgr555_to_rgba(0x7C00), (0, 0, 255, 255))
        self.assertEqual(bgr555_to_rgba(0x0000), (0, 0, 0, 0))
        self.assertEqual(bgr555_to_rgba(0x8000), (0, 0, 0, 255))


class Tex(unittest.TestCase):
    def test_4bpp_nibble_order_and_clut(self):
        d = textures.decode_tex(fx.tex_4bpp())
        e = d["entries"][0]
        self.assertEqual((e["width"], e["height"], e["bpp"], e["pixel_bytes"]), (4, 2, 4, 4))
        px = textures.render_rgba(e, e["_cluts"][0])
        idx = [0, 1, 2, 3, 4, 5, 6, 7]                       # low nibble first
        self.assertEqual(px, [bgr555_to_rgba((k * 0x0421) & 0x7FFF) for k in idx])
        self.assertEqual(e["clut_offset"], 8 + 12 + 4)

    def test_8bpp_engine_cursor_quirk(self):
        d = textures.decode_tex(fx.tex_8bpp(3, 2))            # 6 pixel bytes, not a multiple of 4
        e = d["entries"][0]
        self.assertTrue(e["engine_layout_mismatch"])
        self.assertEqual(e["engine_clut_offset"], e["clut_offset"] - 2)

    def test_16bpp(self):
        e = textures.decode_tex(fx.tex_16bpp())["entries"][0]
        self.assertIsNone(e["clut_offset"])
        self.assertEqual(textures.render_rgba(e)[0], (255, 0, 0, 255))

    def test_3pal_explicit_clut_count(self):
        d = textures.decode_tex(fx.tex_4bpp(magic=b"3PAL", pal_count=2))
        self.assertEqual(d["entries"][0]["clut_count"], 2)

    def test_rejects(self):
        good = fx.tex_4bpp()
        self.assertRaises(FormatError, textures.decode_tex, good[:-1])              # truncated
        self.assertRaises(FormatError, textures.decode_tex, good + b"\0")           # trailing
        self.assertRaises(FormatError, textures.decode_tex, b"XTEX" + good[4:])     # magic
        bad_mode = good[:16] + struct.pack("<I", 7) + good[20:]
        self.assertRaises(FormatError, textures.decode_tex, bad_mode)
        huge = good[:8] + struct.pack("<II", 4096, 4096) + good[16:]
        self.assertRaises(FormatError, textures.decode_tex, huge)
        self.assertRaises(FormatError, textures.decode_tex, b"3TEX" + fx.u32(0))   # zero count
        self.assertRaises(FormatError, textures.decode_tex, fx.tex_4bpp(w=3, h=2))  # odd 4bpp width


class ImgPlt(unittest.TestCase):
    def test_pairing_and_multi_clut_records(self):
        img, plt = fx.img_plt()
        i, p = textures.decode_img(img), textures.decode_plt(plt)
        pairs = textures.pair_img_plt(i, p)
        self.assertEqual([q["clut_count"] for _, q in pairs], [1, 9])
        self.assertEqual(p["records"][1]["offset"], 8 + 40)
        px = textures.render_rgba(pairs[1][0], pairs[1][1]["_cluts"][0])
        self.assertEqual(px[0], bgr555_to_rgba(1 + 1))       # byte 0x11 -> index 1 of CLUT (i + k)

    def test_rejects(self):
        img, plt = fx.img_plt()
        self.assertRaises(FormatError, textures.decode_img, img[:-1])
        self.assertRaises(FormatError, textures.decode_plt, plt[:-2])
        bad = plt[:12] + fx.u32(0) + plt[16:]                 # zero CLUT count
        self.assertRaises(FormatError, textures.decode_plt, bad)
        img1, plt1 = fx.img_plt(n=1)
        self.assertRaises(FormatError, textures.pair_img_plt, textures.decode_img(img),
                          textures.decode_plt(plt1))


class Ful(unittest.TestCase):
    def test_frames(self):
        f = textures.decode_ful(fx.ful(frames=3))
        self.assertEqual((f["width"], f["height"], f["frames"]), (320, 256, 3))
        self.assertEqual(f["geometry_evidence"], "executable_stride_0x28004")

    def test_small_frames(self):
        f = textures.decode_ful(fx.ful(160, 120, 2))
        self.assertEqual((f["width"], f["height"]), (160, 120))
        self.assertEqual(f["geometry_evidence"], "corpus_tiling_and_rows")

    def test_rejects(self):
        d = bytearray(fx.ful(frames=2))
        d[4 + 320 * 256 * 2] = 9                               # frame number not sequential
        self.assertRaises(FormatError, textures.decode_ful, bytes(d))
        self.assertRaises(FormatError, textures.decode_ful, fx.ful()[:-2])


class Models(unittest.TestCase):
    def build(self, words=None, verts=None, tex=(0,)):
        v, w = fx.quad_model()
        m = fx.model(verts or v, words or w)
        mmm, ttt = fx.mmm_ttt([None, m], [[], list(tex)])
        t = models.decode_ttt(ttt)
        return models.decode_mmm(mmm, "syn", t), t

    def test_quad(self):
        mm, _ = self.build()
        self.assertTrue(mm["models"][0]["empty"])
        m = mm["models"][1]
        self.assertTrue(m["primitive_count_matches"])
        self.assertTrue(m["cm01"]["bbox_matches_vertices"])
        self.assertEqual(m["cm01"]["bbox_diagonal_div4_0x1A"], 22)
        self.assertEqual(m["mdl"]["vertex_group_count"], 1)
        self.assertEqual(m["mdl"]["format_flags_0x10"], 0x47F)
        self.assertEqual(m["mdl"]["vertex_group_end_indices"], [3])
        self.assertEqual(m["mdl"]["empty_vertex_groups"], 0)
        (p,) = m["primitives"]
        self.assertEqual(p["vertices"], [0, 1, 2, 3])
        self.assertEqual(p["uvs"], [(0, 0), (63, 0), (63, 63), (0, 63)])
        self.assertEqual((p["corners"], p["textured"], p["gouraud"], p["gp0_code"]), (4, True, True, 0x3C))
        self.assertEqual(p["cull"], "front_if_nclip_negative")
        self.assertEqual(p["colors"][0], 0x008080)

    def test_obj_order_and_axes(self):
        mm, _ = self.build()
        obj = models.model_to_obj(mm["models"][1], "syn", [(64, 64)])
        self.assertIn("v 64 64 0", obj)
        self.assertIn("v 0 64 0", obj)
        face = [l for l in obj.splitlines() if l.startswith("f ")][0]
        self.assertEqual([int(x.split("/")[0]) for x in face.split()[1:]], [4, 3, 2, 1])   # mode 1 reversed

    def test_normal_unpack(self):
        self.assertEqual(models._normal(0x7F000010), (127 << 5, 0, 0))
        self.assertEqual(models._normal(0x0080FF10), (16, -128 << 5, -1 << 5))   # x keeps bits 19-23 like the engine

    def test_guard_block(self):
        v, w = fx.quad_model()
        w = w[:-1]
        guarded = [0x00002064, 0x00000002] + w[-6:]          # 0x20-byte block: guard + mask + 6 words
        words = w[:-6] + guarded + [0x68]
        mm, _ = self.build(words=words)
        p = mm["models"][1]["primitives"][0]
        self.assertEqual(p["guards"][0]["masks"], [2])

    def test_named_visibility_block(self):
        v, w = fx.quad_model()
        params = b"Mesh07" + bytes(10)
        guarded = [0x00003470, 4, 0] + list(struct.unpack("<4I", params)) + w[-7:-1]
        mm, _ = self.build(words=w[:-7] + guarded + [0x68], verts=v)
        guard = mm["models"][1]["primitives"][0]["guards"][0]
        self.assertEqual(guard["submesh_name"], "Mesh07")
        self.assertEqual(guard["visibility_channel_masks"], [4, 0])

    def test_rejects(self):
        v, w = fx.quad_model()
        bad_idx = list(w)
        bad_idx[6] = (0x000 << 20) | (0x009 << 8) | 0x40     # vertex 9 of 4
        self.assertRaises(FormatError, self.build, bad_idx)
        unknown = list(w)
        unknown.insert(2, 0x000000B0)
        self.assertRaises(FormatError, self.build, unknown)
        no_end = list(w[:-1]) + [0x60]
        self.assertRaises(FormatError, self.build, no_end)
        self.assertRaises(FormatError, self.build, None, None, ())        # texture slot 0 of 0
        m = fx.model(v, w)
        mmm, ttt = fx.mmm_ttt([m], [[0]])
        self.assertRaises(FormatError, models.decode_mmm, mmm[:-4], "t", models.decode_ttt(ttt))
        bad_groups = bytearray(mmm)
        struct.pack_into("<I", bad_groups, 8 + 12 + 0x24 + 4, 3)
        self.assertRaises(FormatError, models.decode_mmm, bytes(bad_groups), "t", models.decode_ttt(ttt))
        bad_vertex_flag = bytearray(mmm)
        struct.pack_into("<H", bad_vertex_flag, 8 + 12 + 0x24 + 24 + 6, 1)
        self.assertRaises(FormatError, models.decode_mmm, bytes(bad_vertex_flag), "t", models.decode_ttt(ttt))
        bad_flags = bytearray(mmm)
        struct.pack_into("<I", bad_flags, 8 + 12 + 0x24 + 16, 0)
        self.assertRaises(FormatError, models.decode_mmm, bytes(bad_flags), "t", models.decode_ttt(ttt))
        bad_center = bytearray(mmm)
        struct.pack_into("<h", bad_center, 8 + 12 + 0x1C, 1)
        self.assertRaises(FormatError, models.decode_mmm, bytes(bad_center), "t", models.decode_ttt(ttt))
        mmm2, ttt2 = fx.mmm_ttt([m, m], [[0], [0]])
        self.assertRaises(FormatError, models.decode_mmm, mmm, "t", models.decode_ttt(ttt2))   # count mismatch
        self.assertRaises(FormatError, models.decode_ttt, ttt.replace(b"LBTX", b"XBTX"))


class Level(unittest.TestCase):
    def test_flb(self):
        f = level.decode_flb(fx.flb(), tile_count=6)
        self.assertEqual((f["width"], f["height"]), (64, 256))
        self.assertEqual(f["tile_histogram"], {5: 64 * 256})
        self.assertEqual(f["rgb_block_count"], 32 * 128)
        self.assertEqual(level.flb_cell((7 << 18) | (3 << 16) | 0x8000 | 0x1234)["uv_rotation"], 3)
        self.assertEqual(level.decode_flb(fx.flb(), tile_count=5)["cells_with_tile_beyond_tex"], 64 * 256)
        sentinel = level.decode_flb(fx.flb(tile=63), tile_count=5)
        self.assertEqual(sentinel["sentinel_tile_cells"], 64 * 256)
        self.assertEqual(sentinel["cells_with_tile_beyond_tex"], 0)
        self.assertIsNone(level.flb_cell(63 << 18)["tile"])
        d = bytearray(fx.flb())
        for index, value in ((1, 0x12), (64, 0x34), (65, 0x56)):
            struct.pack_into("<I", d, 4 + 4 * index, struct.unpack_from("<I", d, 4 + 4 * index)[0] | value << 24)
        self.assertEqual(level.decode_flb(bytes(d))["_rgb_blocks"][0], 0x563412)

    def test_flb_rejects(self):
        self.assertRaises(FormatError, level.decode_flb, fx.flb()[:-1])
        self.assertRaises(FormatError, level.decode_flb, fx.flb() + b"\0\0\0\0")   # trailing cell
        self.assertRaises(FormatError, level.decode_flb, struct.pack("<HH", 100, 1) + bytes(400))
        d = bytearray(fx.flb())
        struct.pack_into("<I", d, 4, 1 << 24)
        self.assertRaises(FormatError, level.decode_flb, bytes(d))

    def test_level_bin(self):
        b = level.decode_level_bin(fx.level_bin())
        self.assertEqual(len(b["placements"]), 3)
        self.assertEqual(b["placements"][1]["yaw_u16"], 16384)
        self.assertEqual((b["active_first"], b["active_count"]), (1, 2))
        self.assertEqual(b["group_count"], 2)
        self.assertEqual(b["groups"][0]["z1"], 20)
        self.assertEqual([x["opcode"] for x in b["object_records"]], [7, 7, 7])
        self.assertEqual(b["placements"][2]["object_record"], 2)
        self.assertEqual(b["model_names"], [{"pointer": 0x7C, "section_offset": 8, "name": "fixture"}])

    def test_level_bin_rejects(self):
        d = fx.level_bin()
        self.assertRaises(FormatError, level.decode_level_bin, d[:20])
        bad = bytearray(d)
        struct.pack_into("<I", bad, 8, 0x21)                 # placement section no longer a multiple of 12
        self.assertRaises(FormatError, level.decode_level_bin, bytes(bad))
        bad = bytearray(d)
        struct.pack_into("<I", bad, 0x20, 3)                 # group count disagrees with section size
        self.assertRaises(FormatError, level.decode_level_bin, bytes(bad))
        bad = bytearray(d)
        struct.pack_into("<I", bad, 0x44 + 8, 2)             # not an object-record boundary
        self.assertRaises(FormatError, level.decode_level_bin, bytes(bad))

    def test_level_object_fields(self):
        bounds = struct.pack("<BBhhhhhhH", 30, 2, -1, -2, -3, 4, 5, 6, 0)
        palette = bytes([37]) + bytes(range(1, 22)) + bytes(2)
        records = [bytes([0, 0, 0, 0]), bounds, bytes([6, 2, 3, 0]), bytes([7, 20, 1, 0]),
                   bytes([27, 1, 0, 0]), palette, bytes([38, 10, 20, 30]),
                   struct.pack("<BBHi", 31, 2, 17, -4),
                   struct.pack("<BB3HBBH", 10, 0, 1, 2, 3, 4, 5, 0),
                   struct.pack("<BB3HBBH", 15, 0, 1, 2, 3, 4, 5, 6),
                   struct.pack("<BBH", 20, 0, 9),
                   struct.pack("<BB5HB3xiB3x", 21, 0, 1, 2, 3, 4, 5, 1, -1, 3),
                   struct.pack("<BB7H", 32, 2, 1, 2, 3, 4, 5, 6, 7),
                   struct.pack("<BB8HBB", 3, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1),
                   struct.pack("<BB5HB3x", 4, 0, 1, 2, 3, 4, 5, 1),
                   struct.pack("<BB3H", 5, 0, 1, 2, 3), bytes([9, 0, 0, 0]),
                   struct.pack("<4BHH", 12, 2, 3, 0, 0xFFFF, 0),
                   struct.pack("<4B2HiH2B", 13, 2, 3, 4, 5, 6, -7, 0xFFFF, 8, 0),
                   struct.pack("<BBH", 17, 2, 300),
                   struct.pack("<BB3HB3x", 24, 0, 1, 2, 3, 0xFF),
                   struct.pack("<BB5H", 25, 4, 1, 2, 3, 4, 5),
                   struct.pack("<BBHiiHH6i", 26, 1, 0, 4, 8, 12, 13, 1, 2, 3, 4, 5, -1)]
        b = level.decode_level_bin(fx.level_bin(object_records=records))
        self.assertEqual(b["object_records"][0]["fields"],
                         {"model_name_index": 0, "model_name": "fixture"})
        self.assertEqual(b["object_records"][1]["fields"],
                         {"mode": 2, "min_offset": [-1, -2, -3], "max_offset": [4, 5, 6],
                          "reserved_u16": 0})
        self.assertEqual(b["object_records"][2]["fields"], {"grid_row": 2, "grid_column": 3})
        self.assertEqual(b["object_records"][3]["fields"], {"turret_mode": 20, "spawn_parameter": 1})
        self.assertEqual(b["object_records"][4]["fields"], {"randomized_hazard_type": True})
        self.assertEqual(b["object_records"][5]["fields"]["environment_rgb"][0], [1, 2, 3])
        self.assertEqual(b["object_records"][5]["fields"]["environment_rgb"][-1], [19, 20, 21])
        self.assertEqual(b["object_records"][6]["fields"], {"player_rgb": [10, 20, 30]})
        self.assertEqual(b["object_records"][7]["fields"],
                         {"team_index": 2, "actor_id": 17, "actor_definition_offset": -4})
        self.assertEqual(b["object_records"][8]["fields"]["resource_indices"], [1, 2, 3])
        self.assertEqual(b["object_records"][9]["fields"]["building_kind"], 4)
        self.assertEqual(b["object_records"][10]["fields"], {"crate_resource_index": 9})
        self.assertEqual(b["object_records"][11]["fields"]["subrecord_offset"], -1)
        self.assertEqual(b["object_records"][12]["fields"]["resource_indices"], [1, 2, 3, 4, 5, 6, 7])
        self.assertEqual(b["object_records"][13]["fields"]["resource_indices"], list(range(1, 9)))
        self.assertTrue(b["object_records"][14]["fields"]["derive_selection"])
        self.assertEqual(b["object_records"][15]["fields"]["resource_indices"], [1, 2, 3])
        self.assertEqual(b["object_records"][16]["fields"], {"no_parameters": True})
        self.assertIsNone(b["object_records"][17]["fields"]["optional_resource_index"])
        self.assertEqual(b["object_records"][18]["fields"]["quantity"], -7)
        self.assertEqual(b["object_records"][19]["fields"], {"world_slot": 2, "value": 300})
        self.assertEqual(b["object_records"][20]["fields"]["selection"], 0xFF)
        self.assertTrue(b["object_records"][21]["fields"]["engine_noop"])
        self.assertEqual(b["object_records"][22]["fields"]["segment_offsets"], [1, 2, 3, 4, 5, -1])
        bad_ref = bytearray(fx.level_bin(object_records=[bytes([0, 0, 2, 0])]))
        self.assertRaises(FormatError, level.decode_level_bin, bytes(bad_ref))
        bad_reserved = bytearray(fx.level_bin(object_records=[bounds[:-2] + b"\1\0"]))
        self.assertRaises(FormatError, level.decode_level_bin, bytes(bad_reserved))
        self.assertRaises(FormatError, level.decode_level_bin,
                          fx.level_bin(object_records=[bytes([6, 0, 0, 1])]))

    def test_font(self):
        data = struct.pack("<6H", 0, 0, 5, 5, 0, 6) + bytes(79 * 6) + struct.pack("<3H", 8, 10, 4)
        g = level.decode_font_bin(data, sheet_size=(16, 8))
        self.assertEqual(g["absent"], 79)
        self.assertEqual(g["metrics"], {"glyph_height": 8, "fixed_advance": 10, "space_width": 4})
        bad = bytearray(data)
        struct.pack_into("<H", bad, 6, 12)
        self.assertRaises(FormatError, level.decode_font_bin, bytes(bad), sheet_size=(16, 8))
        bad = bytearray(data)
        struct.pack_into("<3H", bad, 12, 1, 0, 0)
        self.assertRaises(FormatError, level.decode_font_bin, bytes(bad))
        self.assertRaises(FormatError, level.decode_font_bin, b"\0" * 5)

    def test_sfx(self):
        s = level.decode_sfx(fx.sfx())
        self.assertEqual(s["count"], 2)
        self.assertEqual(s["entries"][0]["data_bytes"], 32)
        self.assertEqual(s["entries"][0]["pitch"], 0x400)
        self.assertEqual(s["entries"][0]["sentinel_s16"], -1)
        self.assertRaises(FormatError, level.decode_sfx, fx.sfx()[:-1])

    def test_xa(self):
        x = level.inventory_xa(fx.xa_sectors())
        self.assertEqual(x["sectors"], 2)
        self.assertEqual(x["sector_kinds"], {"audio:ch0": 1, "video:ch0": 1})
        self.assertRaises(FormatError, level.inventory_xa, bytes(100))


class Metadata(unittest.TestCase):
    def test_ascii_text(self):
        decoded = metadata.decode_ascii_text(b"first\r\nsecond")
        self.assertEqual(decoded["lines"], ["first", "second"])
        self.assertEqual(decoded["line_endings"], {"crlf": 1, "cr": 0, "lf": 0})
        self.assertFalse(decoded["trailing_newline"])
        self.assertRaises(FormatError, metadata.decode_ascii_text, b"bad\0text")
        self.assertRaises(FormatError, metadata.decode_ascii_text, b"bad\xfftext")

    def test_system_cnf(self):
        decoded = metadata.decode_system_cnf(
            b"BOOT=cdrom:\\SLUS_010.44;1\r\nTCB=4\r\nSTACK=801fff00\r\n")
        self.assertEqual(decoded["boot_path"], "SLUS_010.44")
        self.assertEqual(decoded["boot_version"], 1)
        self.assertEqual(decoded["entries"][1], {"key": "TCB", "value": "4"})
        self.assertRaises(FormatError, metadata.decode_system_cnf, b"TCB=4\r\n")
        self.assertRaises(FormatError, metadata.decode_system_cnf,
                          b"BOOT=cdrom:\\X;1\r\nBOOT=cdrom:\\Y;1\r\n")

    def test_psx_exe(self):
        header = bytearray(0x800)
        header[:8] = b"PS-X EXE"
        struct.pack_into("<III", header, 0x10, 0x80010000, 0, 0x80010000)
        struct.pack_into("<I", header, 0x1C, 0x800)
        header[0x4C:0x50] = b"TEST"
        decoded = metadata.decode_psx_exe(bytes(header) + bytes(0x800))
        self.assertEqual(decoded["entry"], 0x80010000)
        self.assertEqual(decoded["header_marker"], "TEST")
        self.assertEqual(decoded["text_offset"], 0x800)
        self.assertRaises(FormatError, metadata.decode_psx_exe, bytes(header))
        self.assertRaises(FormatError, metadata.decode_psx_exe, b"bad")

    def test_licence_sectors(self):
        sector = b"\0\0\x08\0" * 2 + bytes(2328)
        decoded = metadata.decode_licence_sectors(sector * 2)
        self.assertEqual(decoded["sector_bytes"], 2336)
        self.assertEqual(len(decoded["sectors"]), 2)
        self.assertEqual(decoded["sectors"][1]["payload_offset"], 2336 + 8)
        bad = bytearray(sector)
        bad[4] = 1
        self.assertRaises(FormatError, metadata.decode_licence_sectors, bytes(bad))
        self.assertRaises(FormatError, metadata.decode_licence_sectors, bytes(100))


class Audio(unittest.TestCase):
    def test_spu_adpcm_and_wav(self):
        frame = bytes([0x0C, 1]) + bytes([0x11]) + bytes(13)
        dec = audio.decode_spu_adpcm(frame)
        self.assertEqual(dec["samples"][:2], [1, 1])
        self.assertEqual(dec["decoded_frames"], 1)
        wav = audio.encode_wav_mono16(dec["samples"], audio.pitch_sample_rate(0x400))
        self.assertEqual(wav[:12], b"RIFF" + struct.pack("<I", len(wav) - 8) + b"WAVE")
        self.assertEqual(struct.unpack_from("<I", wav, 24)[0], 11025)

    def test_spu_adpcm_rejects(self):
        self.assertRaises(FormatError, audio.decode_spu_adpcm, bytes(15))
        self.assertRaises(FormatError, audio.decode_spu_adpcm, bytes([0x5C, 1]) + bytes(14))
        self.assertRaises(FormatError, audio.decode_spu_adpcm, bytes([0x0C, 0]) + bytes(14))


class Media(unittest.TestCase):
    def test_mode2_rewrap(self):
        raw = media.wrap_mode2_sectors(bytes(2 * 2336))
        self.assertEqual(len(raw), 2 * 2352)
        self.assertEqual(raw[:12], b"\x00" + b"\xFF" * 10 + b"\x00")
        self.assertEqual(raw[12:16], bytes((0, 2, 0, 2)))
        self.assertEqual(raw[2352 + 12:2352 + 16], bytes((0, 2, 1, 2)))
        self.assertRaises(FormatError, media.wrap_mode2_sectors, bytes(1))


class Png(unittest.TestCase):
    def test_deterministic(self):
        a = encode_rgba(2, 1, [(1, 2, 3, 4), (5, 6, 7, 8)])
        self.assertEqual(a, encode_rgba(2, 1, [(1, 2, 3, 4), (5, 6, 7, 8)]))
        self.assertTrue(a.startswith(b"\x89PNG"))
        self.assertRaises(ValueError, encode_rgba, 2, 2, [(0, 0, 0, 0)])


class InventoryIsolation(unittest.TestCase):
    def test_refuses_output_inside_input(self):
        from btga_ps1 import inventory
        with tempfile.TemporaryDirectory() as d:
            self.assertRaises(SystemExit, inventory.run, d, os.path.join(d, "out"))

    def test_synthetic_corpus_deterministic(self):
        from btga_ps1 import inventory
        with tempfile.TemporaryDirectory() as root, tempfile.TemporaryDirectory() as o1, tempfile.TemporaryDirectory() as o2:
            a = os.path.join(root, "ASSETS")
            os.makedirs(a)
            img, plt = fx.img_plt()
            v, w = fx.quad_model()
            mmm, ttt = fx.mmm_ttt([fx.model(v, w)], [[0]])
            files = {"X.TEX": fx.tex_4bpp(), "X.IMG": img, "X.PLT": plt, "X.MMM": mmm, "X.TTT": ttt,
                     "X.FLB": fx.flb(), "X.BIN": fx.level_bin(), "V.SFX": fx.sfx(), "BAD.TEX": b"junk"}
            for k, b in files.items():
                with open(os.path.join(a, k), "wb") as fh:
                    fh.write(b)
            m1 = inventory.run(root, o1, previews=True, objs=True)
            inventory.run(root, o2, previews=True, objs=True)
            self.assertEqual(m1["files"]["ASSETS/BAD.TEX"]["status"], "rejected")
            self.assertEqual(sum(e["status"] == "accepted" for e in m1["files"].values()), 8)
            for dp, _, fs in os.walk(o1):
                for f in fs:
                    p1 = os.path.join(dp, f)
                    p2 = os.path.join(o2, os.path.relpath(p1, o1))
                    with open(p1, "rb") as left, open(p2, "rb") as right:
                        self.assertEqual(left.read(), right.read(), p1)


if __name__ == "__main__":
    unittest.main()
