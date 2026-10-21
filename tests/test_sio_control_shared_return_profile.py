import unittest

from tools import verify_matching_units as v


class SioControlSharedReturnTest(unittest.TestCase):
    SITE = "sh\t$2,10($3)\nj\t$31\naddu\t$2,$7,$zero\n\n"
    TAIL = ("$L2:\naddu\t$2,$7,$zero\nj\t$31\nnop  # DEBUG: branch/jump\n"
            ".end\tfunc_80099DEC\n")

    def test_rewrites_six_sites(self):
        out = v._sio_control_shared_return(self.SITE * 6 + self.TAIL)
        self.assertEqual(out.count("j\t$Lsio_ret\naddu\t$2,$7,$zero"), 6)
        self.assertEqual(out.count("j\t$31"), 1)
        self.assertIn("$Lsio_ret:\nj\t$31\nnop", out)

    def test_wrong_site_count_fails(self):
        with self.assertRaises(ValueError):
            v._sio_control_shared_return(self.SITE * 5 + self.TAIL)

    def test_missing_tail_fails(self):
        with self.assertRaises(ValueError):
            v._sio_control_shared_return(self.SITE * 6)

    def test_extra_return_fails(self):
        with self.assertRaises(ValueError):
            v._sio_control_shared_return(self.SITE * 6 + "j\t$31\nnop\n" + self.TAIL)


if __name__ == "__main__":
    unittest.main()
