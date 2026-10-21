import unittest

from tools.analyze_large_candidate import aligned_differences, classify_pair
from tools.search_large_candidate_variants import (
    materialize_variants,
    unique_source_variants,
)


class LargeCandidateAnalysis(unittest.TestCase):
    def test_branch_displacement_is_separate_from_content(self):
        self.assertEqual(classify_pair(0x10620011, 0x1062000E), "flow-target")
        self.assertEqual(classify_pair(0x10620011, 0x14620011), "opcode")

    def test_gte_words_are_not_masked(self):
        self.assertNotEqual(classify_pair(0x484C0000, 0x484D0000), "flow-target")

    def test_alignment_ignores_only_flow_targets(self):
        target = bytes.fromhex("0e00621000000000")
        candidate = bytes.fromhex("1100621000000000")
        self.assertEqual(
            [item["kind"] for item in aligned_differences(candidate, target)],
            ["flow-target"],
        )

    def test_variant_cross_product(self):
        specification = {
            "sites": [
                {
                    "old": "A",
                    "variants": [
                        {"name": "a0", "text": "A"},
                        {"name": "a1", "text": "X"},
                    ],
                },
                {
                    "old": "B",
                    "variants": [
                        {"name": "b0", "text": "B"},
                        {"name": "b1", "text": "Y"},
                    ],
                },
            ]
        }
        variants = list(materialize_variants("AB", specification, 4))
        self.assertEqual(
            variants,
            [("a0+b0", "AB"), ("a0+b1", "AY"),
             ("a1+b0", "XB"), ("a1+b1", "XY")],
        )

    def test_duplicate_generated_sources_are_compiled_once(self):
        variants = [
            ("first", "same source"),
            ("duplicate", "same source"),
            ("different", "other source"),
        ]
        self.assertEqual(
            unique_source_variants(variants),
            [("first", "same source"), ("different", "other source")],
        )


if __name__ == "__main__":
    unittest.main()
