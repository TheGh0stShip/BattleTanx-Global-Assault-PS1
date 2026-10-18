import unittest

from tools import psyq_signatures


class PsyqSignatures(unittest.TestCase):
    def test_parse_signature(self):
        pattern, mask = psyq_signatures.parse_signature("12 ?? aB 00")
        self.assertEqual(pattern, bytes((0x12, 0, 0xAB, 0)))
        self.assertEqual(mask, bytes((0xFF, 0, 0xFF, 0xFF)))

    def test_masked_match_and_alignment(self):
        payload = b"xxxx" + bytes.fromhex("11 22 33 44 55 66 77 88")
        pattern, mask = psyq_signatures.parse_signature(
            "11 22 33 44 ?? 66 77 88"
        )
        self.assertEqual(
            psyq_signatures.find_masked(payload, pattern, mask), [4]
        )

    def test_unanchorable_signature(self):
        pattern, mask = psyq_signatures.parse_signature("11 ?? 22 ??")
        self.assertIsNone(psyq_signatures.find_masked(b"\x00" * 16, pattern, mask))

    def test_rejects_bad_token(self):
        with self.assertRaises(ValueError):
            psyq_signatures.parse_signature("not-a-byte")


if __name__ == "__main__":
    unittest.main()
