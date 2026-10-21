import unittest

from tools import verify_matching_units as v


class StreamSetupDestSwapTest(unittest.TestCase):
    def sample(self):
        body = ("func_80089B70:\nsw\t$fp,48($sp)\naddu\t$fp,$5,$zero\nsw\t$22,40($sp)\n"
                + "lw\t$22,108($16)\n" * 4 + v._SSDS_SCHED_OLD + "sw\t$fp,112($4)\n"
                + "lw\t$fp,48($sp)\n#x $fp\n#y $fp\nlw\t$22,40($sp)\n#z $22\n#w $22\n#v $22\n")
        return body

    def test_applies(self):
        out = v._stream_setup_dest_swap(self.sample())
        self.assertIn("sw\t$22,40($sp)\naddu\t$22,$5,$zero\nsw\t$fp,48($sp)\n", out)
        self.assertIn(v._SSDS_SCHED_NEW, out)
        self.assertIn("sw\t$22,112($4)", out)
        self.assertIn("lw\t$fp,48($sp)\n#x $22\n#y $22\nlw\t$22,40($sp)\n", out)

    def test_fails_closed(self):
        with self.assertRaises(ValueError):
            v._stream_setup_dest_swap(self.sample().replace(v._SSDS_SCHED_OLD, ""))
        with self.assertRaises(ValueError):
            v._stream_setup_dest_swap(self.sample() + "lw\t$22,0($4)\n")


if __name__ == "__main__":
    unittest.main()
