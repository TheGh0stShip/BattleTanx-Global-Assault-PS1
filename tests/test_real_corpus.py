"""Gated real-corpus test.  Set BTGA_PS1_EXTRACTED to the extracted disc directory;
skips cleanly when absent.  Never writes inside the corpus."""
import os
import tempfile
import unittest

CORPUS = os.environ.get("BTGA_PS1_EXTRACTED", "")


@unittest.skipUnless(CORPUS and os.path.isdir(CORPUS), "BTGA_PS1_EXTRACTED not set or missing")
class RealCorpus(unittest.TestCase):
    def test_every_file_accepted(self):
        from btga_ps1 import inventory
        with tempfile.TemporaryDirectory() as out:
            m = inventory.run(CORPUS, out)
        self.assertEqual(m["file_count"], 737)
        rejected = {k: e["reason"] for k, e in m["files"].items() if e["status"] == "rejected"}
        self.assertEqual(rejected, {})
        self.assertTrue(all(e["status"] == "accepted" for e in m["files"].values()))
        self.assertTrue(all("decoded" in e for e in m["files"].values()))
        fam = m["summary"]
        self.assertEqual(fam["TEX:accepted"], 256)
        self.assertEqual(fam["MMM:accepted"], 76)
        self.assertEqual(fam["BIN-level:accepted"], 75)
        self.assertEqual(fam["TXT-ASCII:accepted"], 2)
        self.assertEqual(fam["CNF-system:accepted"], 1)
        self.assertEqual(fam["PS-X-EXE:accepted"], 1)
        self.assertEqual(fam["DAT-licence:accepted"], 1)
        models = [x for k, e in m["files"].items() if k.endswith(".MMM") for x in e["decoded"]["models"] if not x.get("empty")]
        self.assertEqual(len(models), 4761)
        self.assertTrue(all(x["cm01"]["bbox_matches_vertices"] for x in models))
        self.assertEqual(sum(not x["primitive_count_matches_header"] for x in models), 1)
        self.assertEqual(sum(x["mdl"]["empty_vertex_groups"] for x in models), 66)
        self.assertTrue(all(x["mdl"]["empty_vertex_groups"] in (0, 1) for x in models))
        self.assertEqual(sum(x["vertex_group_end_count"] for x in models), 15829)
        levels = [e["decoded"] for e in m["files"].values() if e["family"] == "BIN-level"]
        self.assertEqual(sum(x["model_references"] for x in levels), 1756)
        self.assertEqual(sum(x["bounds_records"] for x in levels), 141)
        self.assertEqual(sum(x["semantic_object_records"] for x in levels), 4530)
        fonts = [e["decoded"] for e in m["files"].values() if e["family"] == "BIN-font"]
        self.assertEqual(sum(x["glyphs"] for x in fonts), 324)
        self.assertEqual(sorted((x["metrics"]["glyph_height"], x["metrics"]["fixed_advance"],
                                 x["metrics"]["space_width"]) for x in fonts),
                         [(10, 11, 4), (10, 12, 6), (15, 17, 8), (15, 17, 8)])
        terrains = [e["decoded"] for e in m["files"].values() if e["family"] == "FLB"]
        self.assertEqual(sum(x["rgb_block_count"] for x in terrains), 307200)
        self.assertEqual(sum(x["cells_with_tile_beyond_tex"] for x in terrains), 0)
        self.assertEqual(sum(x["sentinel_tile_cells"] for x in terrains), 36037)


if __name__ == "__main__":
    unittest.main()
