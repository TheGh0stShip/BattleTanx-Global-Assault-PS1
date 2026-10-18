import unittest

from tools import verify_matching_units as vmu


class UnitCompiler(unittest.TestCase):
    config = {"compiler": "gcc-2.8.1-psx", "units": []}

    def test_default_compiler(self):
        path = vmu.compiler_path({"name": "a"}, self.config)
        self.assertEqual(path, vmu.ROOT / ".toolchain/gcc-2.8.1-psx/cc1")

    def test_unit_override(self):
        path = vmu.compiler_path({"name": "a", "compiler": "gcc-2.7.2-psx"}, self.config)
        self.assertEqual(path, vmu.ROOT / ".toolchain/gcc-2.7.2-psx/cc1")

    def test_unknown_compiler_rejected(self):
        with self.assertRaises(ValueError):
            vmu.compiler_path({"name": "a", "compiler": "gcc-9"}, self.config)
        with self.assertRaises(ValueError):
            vmu.validate_units({"compiler": "gcc-2.8.1-psx", "units": [
                {"name": "a", "address": "0x0", "size": "0x4", "source": "a.c", "compiler": "x"}]})


if __name__ == "__main__":
    unittest.main()
