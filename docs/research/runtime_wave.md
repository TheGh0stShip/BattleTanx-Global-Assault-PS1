# Recovered runtime and game routines

These routines compile under the manifest's default GCC 2.8.1 configuration
and match their complete retail extents.

| Entry | Bytes | Recovered behavior |
|---|---:|---|
| `0x800323C0` | 176 | Walk the signed-short-linked node list rooted at `0x800D329C`; resolve the node byte at `+0x16` into a `0x114`-byte subject record; invoke `func_800530E0(subject, 2500, 1)` unless its state at `+0x58` is two. |
| `0x80034544` | 240 | Request a type-49 effect with second argument 32, copy the input position, stamp the current tick, and produce four pairs of random offsets in `[-50, 49]` and `[-10, 9]`. Allocation failure exits without initializing an effect. |
| `0x800530E0` | 244 | Update local and referenced totals according to the global mode gate and flag; add ten times the change in the referenced total's signed quotient by 10000 to two referenced counters. |
| `0x8007FCE8` | 184 | Diagnose a rectangle, reject zero width or height, pack its coordinates, dimensions, and the low 16 bits of two caller values, and submit a 20-byte driver packet. |
| `0x80083854` | 176 | Select the runtime global pointer, add the channel rate to source field `+0x04`, conditionally advance the timer, update its hardware channel, and restore the saved global pointer. |

The palette loader at `0x8003D0CC` is documented separately. Together these
six entries account for 1,264 bytes of matching C.

The allocator wrapper at `0x800237D0` also now declares and forwards its `kind`
argument explicitly to `func_80022B64`. Its previous no-argument declarations
matched through incidental preservation of the incoming argument register by
the tail jump. The corrected C preserves the same bytes while expressing that
data flow. The wrapper ignores the requested-size argument: it checks the free
node count against 64 and otherwise allocates a 64-byte pool node. The effect
initializer's 32-byte size assertion describes its used prefix, not the pool's
allocation stride.

`tests/test_node_allocation_contract.py` compiles the actual wrapper with a
typed host stub for its callee. It checks the 63/64 free-count boundary,
unsigned high counts, full-width kind forwarding, the ignored size argument,
and pointer/null returns. Host counts are explicitly required to be 32-bit;
host pointers remain real pointers. This checks the C interface, not physical
PS1 behavior or the target node layout. The separate MIPS byte verifier covers
the actual routine and its target calling sequence.

## List and counter details

The list loop uses 64-byte nodes and stops on the signed index `-1`. The
subject lookup maps byte value 127 to zero, retaining retail's subsequent
state-field read rather than introducing a new guard.

`func_80022814` reads the global mode and takes no arguments. Its true case is
the interval 7 through 14. In `func_800530E0`, a false mode gate updates only
the local total at `+0x70`. With a true gate, a zero flag also updates that
local total, and every flag value updates the referenced total at `+0x18`.
Crossing a signed `/10000` boundary changes referenced fields `+0x0C` and
`+0x14` by ten times the quotient difference. This also covers decreases and
multi-boundary changes; the C source preserves signed division toward zero.

## Graphics and timer details

The rectangle union preserves both four signed 16-bit fields and the two
32-bit packed words read by retail. Its union alignment accounts for those
word loads. The command payload at `0x800B0D00` stores packed coordinates,
the caller values, and packed dimensions. Submission starts eight bytes before
that payload and passes length 20 and final argument zero. Negative dimensions
are not rejected by this routine's zero checks. The source preserves driver
pointer-load and packet-store ordering with a bounded address-load assembly
expression and empty constraints; it contains no instruction blobs.

The timer block has four 20-byte sources followed by four 12-byte channels.
Cross-checking `func_80083540` establishes source `+0x10` as a callback pointer,
not merely an integer enable flag. Timer advancement requires busy field zero,
a non-null callback, and a nonzero limit at `+0x0C`; channel maintenance and
global-pointer restoration happen on both paths. Layout assertions enforce the
target strides and pointer widths.
