import unittest

from tools import verify_matching_units as v


class CardCreateCseProfileTest(unittest.TestCase):
    def _source(self):
        return (
            "func_80096138:\n"
            "addu\t$2,$5,$zero\n"
            "$L15:\n"
            "la\t$16,D_800EF094\n"
            "li\t$18,2\t\t\t# 0x00000002\n"
            "bne\t$3,$18,$L18\n"
            "addu\t$17,$17,1\n"
            ".set\tmacro\n"
            ".set\treorder\n"
            "\n"
            "slt\t$2,$17,16\n"
        )

    def test_rewrites_exact_shape(self):
        out = v._card_create_cse(self._source())
        self.assertIn("li\t$2,1", out)
        self.assertIn("addu\t$16,$18,$zero", out)
        self.assertIn("bne\t$3,$18,$L18\nnop", out)
        self.assertIn("\naddu\t$17,$17,1\nslt\t$2,$17,16", out)

    def test_rejects_changed_constant_copy(self):
        with self.assertRaises(ValueError):
            v._card_create_cse(
                self._source().replace("addu\t$2,$5,$zero", "addu\t$2,$4,$zero")
            )

    def test_rejects_changed_retry_branch(self):
        with self.assertRaises(ValueError):
            v._card_create_cse(
                self._source().replace("bne\t$3,$18,$L18", "bne\t$2,$18,$L18")
            )

    def test_rejects_wrong_function(self):
        with self.assertRaises(ValueError):
            v._card_create_cse(
                self._source().replace("func_80096138", "func_80056914")
            )


if __name__ == "__main__":
    unittest.main()
