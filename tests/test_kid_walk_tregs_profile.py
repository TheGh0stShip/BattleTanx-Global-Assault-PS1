import unittest

from tools import verify_matching_units as v


class KidWalkTregsTest(unittest.TestCase):
    def _sample(self):
        lines = ["func_800684C0:"]
        for reg, n in v.KID_WALK_TREGS_COUNTS.items():
            lines += ["addu\t$2,$2,$%s" % reg] * n
        return "\n".join(lines) + "\n"

    def test_permutes(self):
        out = v._kid_walk_tregs(self._sample())
        for reg, n in v.KID_WALK_TREGS_COUNTS.items():
            self.assertEqual(out.count("$2,$%s\n" % v.KID_WALK_TREGS_MAP[reg]), n)

    def test_no_touch_other_regs(self):
        out = v._kid_walk_tregs(self._sample() + "lw\t$80x,0($12)\n".replace("$80x", "$18"))
        self.assertIn("$18", out)
        self.assertIn("$12", out)

    def test_wrong_counts(self):
        with self.assertRaises(ValueError):
            v._kid_walk_tregs(self._sample() + "move\t$8,$9\n")

    def test_wrong_function(self):
        with self.assertRaises(ValueError):
            v._kid_walk_tregs(self._sample().replace("func_800684C0", "func_80065710"))


if __name__ == "__main__":
    unittest.main()
