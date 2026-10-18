import json
import struct
import unittest
from pathlib import Path

from tools import build_matching_executable


class LinkedBuild(unittest.TestCase):
    def test_reconstructs_header_from_metadata(self):
        root = Path(__file__).resolve().parents[1]
        metadata = json.loads((root / "config/us/executable.json").read_text())
        header = build_matching_executable.build_header(metadata)
        self.assertEqual(len(header), 0x800)
        self.assertEqual(header[:8], b"PS-X EXE")
        self.assertEqual(struct.unpack_from("<I", header, 0x10)[0], 0x800860B0)
        self.assertEqual(struct.unpack_from("<I", header, 0x18)[0], 0x80010000)
        self.assertEqual(struct.unpack_from("<I", header, 0x1C)[0], 0xB6800)
        self.assertEqual(struct.unpack_from("<I", header, 0x30)[0], 0x801FFFF0)
        self.assertEqual(header[0x4C:0x80], b"Sony Computer Entertainment Inc. for North America a")
        self.assertFalse(any(header[0x84:]))


if __name__ == "__main__":
    unittest.main()
