import unittest

from tools import verify_matching_units as v


class CardDirectoryLocalsProfileTest(unittest.TestCase):
    def _source(self):
        body = ["addu\t$16,$0,$zero", "addu\t$21,$0,$zero"]
        body += ["addu\t$2,$2,$16"] * 3
        body += ["addu\t$2,$2,$18"] * 3
        body += ["addu\t$2,$2,$17"] * 7
        body += ["addu\t$2,$2,$21"] * 2
        body += ["addu\t$17,$0,$zero"]
        return (
            "func_80095DB4:\n"
            "sw\t$7,156($sp)\n"
            + "\n".join(body)
            + "\n$L7:\n"
            "lw\t$2,156($sp)\n"
            "#nop\n"
            "beq\t$2,$0,$L25\n"
            "sw\t$21,0($2)\n"
            "$L25:\n"
            "addu\t$2,$0,$zero\n"
        )

    def test_rewrites_exact_shape(self):
        out = v._card_directory_locals(self._source())
        self.assertIn("sw\t$7,92($sp)", out)
        self.assertIn("lw\t$8,92($sp)", out)
        self.assertIn("beq\t$8,$0,$L25\naddu\t$2,$0,$zero", out)
        self.assertIn("sw\t$21,0($8)", out)
        self.assertNotIn("156($sp)", out)

    def test_rejects_changed_register_count(self):
        with self.assertRaises(ValueError):
            v._card_directory_locals(self._source().replace("$16", "$18", 1))

    def test_rejects_wrong_function(self):
        with self.assertRaises(ValueError):
            v._card_directory_locals(
                self._source().replace("func_80095DB4", "func_80096138")
            )

    def test_rejects_changed_tail(self):
        with self.assertRaises(ValueError):
            v._card_directory_locals(
                self._source().replace("lw\t$2,156($sp)", "lw\t$3,156($sp)")
            )


if __name__ == "__main__":
    unittest.main()
