import unittest

from tools import verify_matching_units


class MatchingUnits(unittest.TestCase):
    def test_oracle_slice(self):
        image = bytes(range(256)) * 0xC00
        address = verify_matching_units.LOAD_ADDRESS + 0x20
        self.assertEqual(
            verify_matching_units.oracle_slice(image, address, 4),
            image[verify_matching_units.HEADER_SIZE + 0x20:
                  verify_matching_units.HEADER_SIZE + 0x24],
        )

    def test_oracle_slice_rejects_header(self):
        with self.assertRaises(ValueError):
            verify_matching_units.oracle_slice(
                b"\0" * 0x1000,
                verify_matching_units.LOAD_ADDRESS - 4,
                4,
            )


if __name__ == "__main__":
    unittest.main()
