import unittest

from tools import verify_matching_units as v


class PrntAspsxMacrosTest(unittest.TestCase):
    def test_rewrites_both_sequences(self):
        out = v._prnt_aspsx_macros("x\n" + v._PRNT_LOAD_OLD + "y\n" + v._PRNT_NOP_OLD)
        self.assertIn(v._PRNT_LOAD_NEW, out)
        self.assertIn(v._PRNT_NOP_NEW, out)
        self.assertNotIn("$at,%hi(D_800B6B31)", out)

    def test_fails_closed_when_missing(self):
        with self.assertRaises(ValueError):
            v._prnt_aspsx_macros(v._PRNT_LOAD_OLD)

    def test_fails_closed_when_duplicated(self):
        with self.assertRaises(ValueError):
            v._prnt_aspsx_macros(v._PRNT_LOAD_OLD + v._PRNT_LOAD_OLD + v._PRNT_NOP_OLD)


if __name__ == "__main__":
    unittest.main()
