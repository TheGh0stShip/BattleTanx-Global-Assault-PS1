import unittest

from tools import verify_matching_units as v


class CardFinishConstArgTest(unittest.TestCase):
    SAMPLE = (
        "$L16:\n" + v._CFCA_OLD.format(label="$L14") + "#.set\tvolatile\n"
    )

    def test_rewrites_once(self):
        out = v._card_finish_const_arg(self.SAMPLE)
        self.assertIn("bne\t$3,$2,$L14\nli\t$4,4\n.set\tmacro\n", out)
        self.assertNotIn("addu\t$4,$2,$zero", out)

    def test_fails_closed_when_missing(self):
        with self.assertRaises(ValueError):
            v._card_finish_const_arg("bne\t$3,$2,$L14\naddu\t$4,$2,$zero\n")

    def test_fails_closed_when_duplicated(self):
        with self.assertRaises(ValueError):
            v._card_finish_const_arg(self.SAMPLE + self.SAMPLE)


if __name__ == "__main__":
    unittest.main()
