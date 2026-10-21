import unittest

from tools import verify_matching_units as v


class CdControlRetryProfileTest(unittest.TestCase):
    def test_moves_ret_init(self):
        out = v._cd_control_retry_psyq("func:\n" + v._CDCR_EXPECTED + "li\t$23,-1\n")
        self.assertIn(v._CDCR_RETAIL, out)
        self.assertEqual(out.count("addu\t$22,$0,$zero"), 1)

    def test_fails_closed_when_missing(self):
        with self.assertRaises(ValueError):
            v._cd_control_retry_psyq("func:\nnop\n")

    def test_fails_closed_when_duplicated(self):
        with self.assertRaises(ValueError):
            v._cd_control_retry_psyq(v._CDCR_EXPECTED + v._CDCR_EXPECTED)


if __name__ == "__main__":
    unittest.main()
