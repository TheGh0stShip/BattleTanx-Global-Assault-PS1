"""Host-only C interface checks; target byte verification remains separate."""

import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path


HARNESS = r'''
#include <assert.h>
#include "src/game/800237D0.c"

typedef char Count_is_32_bit[(sizeof(unsigned int) == 4) ? 1 : -1];
struct Node { int marker; };
unsigned int D_800A4388;
static struct Node node;
static struct Node *allocation;
static int calls;
static int expected_kind;

struct Node *func_80022B64(int kind) {
    assert(kind == expected_kind);
    calls++;
    return allocation;
}

int main(void) {
    allocation = &node;
    expected_kind = 49;
    D_800A4388 = 0;
    assert(func_800237D0(49, 32) == 0);
    D_800A4388 = 63;
    assert(func_800237D0(49, 32) == 0);
    assert(calls == 0);

    D_800A4388 = 64;
    assert(func_800237D0(49, 1024) == &node);
    assert(calls == 1);

    expected_kind = -1;
    D_800A4388 = 65;
    assert(func_800237D0(-1, 0) == &node);
    assert(calls == 2);

    expected_kind = 0x12345;
    D_800A4388 = ~0U;
    assert(func_800237D0(0x12345, 32) == &node);
    assert(calls == 3);

    allocation = 0;
    assert(func_800237D0(0x12345, 32) == 0);
    assert(calls == 4);
    return 0;
}
'''


@unittest.skipUnless(shutil.which("cc"), "native C compiler not available")
class NodeAllocationContract(unittest.TestCase):
    def test_kind_forwarding_threshold_and_pointer_return(self):
        root = Path(__file__).resolve().parents[1]
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "contract.c"
            binary = Path(directory) / "contract"
            source.write_text(HARNESS)
            compiled = subprocess.run(
                [shutil.which("cc"), "-std=c89", "-Werror",
                 "-Wstrict-prototypes", "-I", str(root), str(source),
                 "-o", str(binary)],
                capture_output=True, text=True,
            )
            self.assertEqual(compiled.returncode, 0, compiled.stderr)
            executed = subprocess.run(
                [str(binary)], capture_output=True, text=True,
            )
            self.assertEqual(executed.returncode, 0, executed.stderr)


if __name__ == "__main__":
    unittest.main()
