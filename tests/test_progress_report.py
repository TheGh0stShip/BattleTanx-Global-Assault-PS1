import json
import tempfile
import unittest
from pathlib import Path

from tools import progress_report


class ProgressReport(unittest.TestCase):
    def test_manifest_totals_and_units(self):
        root = Path(__file__).resolve().parents[1]
        report = progress_report.generate(root / "config/us/matching_units.json")
        self.assertEqual(report["version"], 2)
        self.assertEqual(len(report["units"]), 1875)
        self.assertEqual(report["measures"]["total_code"], 589836)
        self.assertEqual(report["measures"]["matched_code"], 417792)
        self.assertEqual(report["measures"]["total_data"], 157684)
        self.assertEqual(report["measures"]["matched_data"], 157684)
        self.assertEqual(report["measures"]["total_functions"], 1771)
        self.assertEqual(report["measures"]["matched_functions"], 1568)
        self.assertEqual(report["measures"]["complete_units"], 1672)
        self.assertEqual(
            report["measures"]["total_code"] + report["measures"]["total_data"],
            747520,
        )

    def test_cli_output_is_deterministic(self):
        root = Path(__file__).resolve().parents[1]
        config = root / "config/us/matching_units.json"
        with tempfile.TemporaryDirectory() as directory:
            first = Path(directory) / "first.json"
            second = Path(directory) / "second.json"
            progress_report.main(["--config", str(config), "--output", str(first)])
            progress_report.main(["--config", str(config), "--output", str(second)])
            self.assertEqual(first.read_bytes(), second.read_bytes())
            self.assertEqual(json.loads(first.read_text())["version"], 2)


if __name__ == "__main__":
    unittest.main()
