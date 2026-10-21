import unittest

from tools.verify_matching_units import _font_advance_negative_layout


TAIL = (
    "$L66:\n"
    "addu\t$2,$3,-2048\n"
    "bgez\t$2,$L86\n"
    "sra\t$2,$2,12\n"
    "\n"
    "j\t$L123\n"
    "subu\t$2,$20,$3\n"
    "\n"
)


class FontAdvanceNegativeLayoutProfile(unittest.TestCase):
    def source(self):
        return (
            "func_80057420:\n"
            "$L53:\n"
            "normal\n"
            + TAIL
            + "$L51:\n"
            "done\n"
        )

    def test_moves_only_the_rounding_tail(self):
        expected = (
            "func_80057420:\n"
            + TAIL
            + "$L53:\n"
            "normal\n"
            "$L51:\n"
            "done\n"
        )
        self.assertEqual(_font_advance_negative_layout(self.source()), expected)

    def test_rejects_changed_tail(self):
        with self.assertRaises(ValueError):
            _font_advance_negative_layout(self.source().replace("-2048", "-2047"))

    def test_rejects_another_function(self):
        with self.assertRaises(ValueError):
            _font_advance_negative_layout(self.source() + "func_80057424:\n")

    def test_rejects_duplicate_anchor(self):
        with self.assertRaises(ValueError):
            _font_advance_negative_layout(self.source() + "$L53:\n")


if __name__ == "__main__":
    unittest.main()
