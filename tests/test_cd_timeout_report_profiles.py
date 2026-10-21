import unittest

from tools import verify_matching_units as v


def block(t, c):
    return v._cd_report_block(t)[0].format(t=t, c=c)


class CdTimeoutReportProfileTest(unittest.TestCase):
    def test_cd_ready_report(self):
        src = ("sw\t$23,52($sp)\naddu\t$23,$4,$zero\nli\t$4,-1\t\t\t# 0xffffffff\n"
               "sw\t$19,36($sp)\naddu\t$19,$5,$zero\n" + block("$21", "$fp"))
        out = v._cd_ready_report(src)
        self.assertIn("lbu\t$4,0($18)\n", out)
        self.assertIn("lw\t$7,0($4)\n", out)
        self.assertIn("addu\t$19,$5,$zero\nli\t$4,-1", out)
        with self.assertRaises(ValueError):
            v._cd_ready_report(out)

    def test_cd_cw_report(self):
        src = ("sw\t$22,48($sp)\naddu\t$22,$6,$zero\nsw\t$16,24($sp)\naddu\t$16,$5,$zero\n"
               + block("$19", "$21"))
        out = v._cd_cw_report(src)
        self.assertTrue(out.startswith("sw\t$16,24($sp)\naddu\t$16,$5,$zero\nsw\t$22"))
        self.assertIn("addu\t$4,$4,$19\n", out)
        with self.assertRaises(ValueError):
            v._cd_cw_report(out)
        with self.assertRaises(ValueError):
            v._cd_cw_report(src + src)


if __name__ == "__main__":
    unittest.main()
