import unittest

from tools import inventory_functions


class FunctionInventory(unittest.TestCase):
    def test_scans_ordered_candidates(self):
        text = "\n".join((
            "glabel func_80010000",
            "  nop",
            "glabel func_80010010",
        ))
        self.assertEqual(
            inventory_functions.scan(text),
            [0x80010000, 0x80010010],
        )

    def test_includes_named_entrypoint(self):
        self.assertEqual(
            inventory_functions.scan("glabel entrypoint\n"),
            [0x800860B0],
        )

    def test_rejects_duplicates(self):
        with self.assertRaises(ValueError):
            inventory_functions.scan(
                "glabel func_80010000\nglabel func_80010000\n"
            )

    def test_rejects_out_of_range(self):
        with self.assertRaises(ValueError):
            inventory_functions.scan("glabel func_800C6800\n")


if __name__ == "__main__":
    unittest.main()
