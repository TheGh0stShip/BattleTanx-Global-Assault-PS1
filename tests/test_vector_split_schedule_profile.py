import unittest

from tools.verify_matching_units import _vector_split_schedule


ENTRY = (
    "sw\t$4,12($sp)\n"
    "sw\t$2,16($sp)\n"
    "sw\t$3,20($sp)\n"
    "addu\t$3,$4,$zero\n"
    "bgez\t$3,$L7\n"
    "subu\t$3,$0,$3\n"
)
TAIL = "addu\t$2,$2,$4\nsw\t$2,4($7)\naddu\t$3,$3,$5\n"


class VectorSplitScheduleProfile(unittest.TestCase):
    def source(self):
        return "func_80065710:\n" + ENTRY + "middle\n" + TAIL

    def test_reorders_only_the_two_expected_sites(self):
        expected = (
            "func_80065710:\n"
            "sw\t$4,12($sp)\n"
            "sw\t$3,20($sp)\n"
            "addu\t$3,$4,$zero\n"
            "bgez\t$3,$L7\n"
            "sw\t$2,16($sp)\n"
            "subu\t$3,$0,$3\n"
            "middle\n"
            "addu\t$2,$2,$4\n"
            "addu\t$3,$3,$5\n"
            "sw\t$2,4($7)\n"
        )
        self.assertEqual(_vector_split_schedule(self.source()), expected)

    def test_rejects_changed_entry(self):
        with self.assertRaises(ValueError):
            _vector_split_schedule(self.source().replace("12($sp)", "8($sp)"))

    def test_rejects_changed_tail(self):
        with self.assertRaises(ValueError):
            _vector_split_schedule(self.source().replace("4($7)", "8($7)"))

    def test_rejects_another_function(self):
        with self.assertRaises(ValueError):
            _vector_split_schedule(self.source() + "func_80065714:\n")


if __name__ == "__main__":
    unittest.main()
