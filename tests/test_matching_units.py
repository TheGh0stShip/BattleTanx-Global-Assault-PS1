import unittest

from tools import verify_matching_units


class MatchingUnits(unittest.TestCase):
    def unit(self, name="first", address="0x80010000", source="first.c", size="0x10"):
        return {"name": name, "address": address, "source": source, "size": size}

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

    def test_rejects_duplicate_names(self):
        units = [self.unit(), self.unit(address="0x80010010", source="second.c")]
        with self.assertRaises(ValueError):
            verify_matching_units.validate_units({"units": units})

    def test_rejects_duplicate_addresses(self):
        units = [self.unit(), self.unit(name="second", source="second.c")]
        with self.assertRaises(ValueError):
            verify_matching_units.validate_units({"units": units})

    def test_rejects_duplicate_sources(self):
        units = [self.unit(), self.unit(name="second", address="0x80010010")]
        with self.assertRaises(ValueError):
            verify_matching_units.validate_units({"units": units})

    def test_rejects_overlapping_ranges(self):
        units = [self.unit(size="0x20"), self.unit(
            name="second", address="0x80010010", source="second.c")]
        with self.assertRaises(ValueError):
            verify_matching_units.validate_units({"units": units})


if __name__ == "__main__":
    unittest.main()
