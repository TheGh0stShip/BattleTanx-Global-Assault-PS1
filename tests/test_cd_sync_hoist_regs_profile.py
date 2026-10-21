import unittest

from tools import verify_matching_units as v


class CdSyncHoistRegsTest(unittest.TestCase):
    SAMPLE = (
        "func_8009FF30:\n"
        "sw\t$20,40($sp)\nsw\t$19,36($sp)\n"
        + v._CDSYNC_EXPECTED_BLOCK
        + "addu\t$2,$2,$19\naddu\t$4,$4,$19\nbeq\t$6,$20,$L30\nsb\t$20,0($18)\n"
        "lw\t$20,40($sp)\nlw\t$19,36($sp)\n"
    )

    def test_rewrites(self):
        out = v._cd_sync_hoist_regs(self.SAMPLE)
        self.assertIn(v._CDSYNC_RETAIL_BLOCK, out)
        self.assertIn("beq\t$6,$19,$L30\n", out)
        self.assertIn("addu\t$2,$2,$20\n", out)
        self.assertIn("sw\t$20,40($sp)\n", out)

    def test_fails_closed(self):
        with self.assertRaises(ValueError):
            v._cd_sync_hoist_regs(self.SAMPLE.replace("addu\t$18,$21,-1", "addu\t$18,$21,1"))
        with self.assertRaises(ValueError):
            v._cd_sync_hoist_regs(self.SAMPLE + v._CDSYNC_EXPECTED_BLOCK)
        with self.assertRaises(ValueError):
            v._cd_sync_hoist_regs(self.SAMPLE.replace("func_8009FF30", "func_X"))


if __name__ == "__main__":
    unittest.main()
