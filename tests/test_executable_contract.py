import tempfile
import unittest
from pathlib import Path
from unittest import mock

from tools import verify_exe


class ExecutableContract(unittest.TestCase):
    def test_constants_tile_the_file(self):
        self.assertEqual(0x800 + 0xB6800, verify_exe.EXPECTED_SIZE)
        self.assertEqual(
            verify_exe.EXPECTED_FIELDS[0x18][1] + verify_exe.EXPECTED_FIELDS[0x1C][1],
            0x800C6800,
        )

    def test_rejects_arbitrary_input(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "input"
            path.write_bytes(b"not an executable")
            with self.assertRaises(SystemExit):
                verify_exe.verify(path)

    def test_hashes_use_complete_input(self):
        fake = bytearray(verify_exe.EXPECTED_SIZE)
        fake[:8] = b"PS-X EXE"
        for offset, (_, value) in verify_exe.EXPECTED_FIELDS.items():
            fake[offset:offset + 4] = value.to_bytes(4, "little")
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "input"
            path.write_bytes(fake)
            with mock.patch.object(verify_exe, "EXPECTED_SHA1", "0" * 40), \
                    mock.patch.object(verify_exe, "EXPECTED_SHA256", "0" * 64):
                with self.assertRaises(SystemExit) as raised:
                    verify_exe.verify(path)
                self.assertIn("SHA-1", str(raised.exception))
                self.assertIn("SHA-256", str(raised.exception))


if __name__ == "__main__":
    unittest.main()
