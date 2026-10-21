# Requested large-function recovery

This work set covers four previously raw instruction wrappers totaling 27,276
bytes.  The candidate files preserve the complete recovered control flow while
compiler matching continues:

| Function | Target bytes | Recovery status |
| --- | ---: | --- |
| `func_80044C38` | 7,052 | Complete C control flow; recompiles to 7,040 bytes with `--expand-div` |
| `func_80065920` | 11,168 | Compiler-valid 9,932-byte draft with the exact 320-byte retail frame, both jump tables, and 298 recovered hardware operations |
| `func_8007AE20` | 4,788 | Compiling crash-screen disassembler with recovered 248-byte retail frame and both jump tables |
| `func_8008BF7C` | 4,268 | Compiler-valid 4,208-byte renderer with recovered scratchpad state, matrix loads, and complete COP2 stream |

`func_80044C38` corresponds to the N64 tank input/update routine
`func_80091768`.  The PS1 implementation replaces its floating-point steering,
normalization, and suspension calculations with 20.12 fixed-point operations,
including GTE `LZCS`/`LZCR` normalization.  Its candidate intentionally uses
small inline helpers for those two compiler-lowered arithmetic idioms.
The frame-step scalar is now constrained to the retail `$s6` allocation,
removing repeated stack reloads throughout the 7 KB body and increasing direct
retail agreement from 1,570 to 2,052 bytes.  The first paired steering
normalizers now keep the fixed `0x58000` denominator and its leading-sign count
in the retail `$a2`/`$a1` registers.  That closes the candidate-size gap from
28 to 12 bytes and raises direct agreement to 2,287 bytes.

`func_80065920` now models its scratch area as one 260-byte structure rather
than unrelated scalar placeholders.  Together with the outgoing argument area
and saved registers, this reproduces the retail 320-byte frame and the exact
local addresses from `sp+0x10` through `sp+0x110`.  The persistent display-state
and matrix-pool pointers are also recovered in retail `$s2` and `$s4`, and the
function prologue now agrees through the first 0x80 bytes.

`func_8007AE20` is the exception display and MIPS instruction formatter, not
gameplay code.  Its nested opcode/funct dispatch tables are recovered as
`jtbl_800C490C` and `jtbl_800C49FC`.  Its two display records now occupy the
retail `sp+0x30` and `sp+0x90` ranges, restoring the exact 248-byte stack frame;
the accumulated register mask is constrained to retail `$s4`.  Those layout
fixes move the first differing instruction from byte zero to `+0xC`.
The exception-name table and both eight-byte GTE opcode/name catalogs are now
typed as 32-bit records.  Their reverse searches consequently use the retail
eight-byte stride, and an unsuccessful extended-opcode search resets its index
to zero instead of executing the earlier empty recovery branch.

`func_8008BF7C` begins by loading one 32-byte matrix into GTE control
registers 0 through 7.  Keeping the loads and `ctc2` operations in one inline
helper preserves their dependency and prevents a superficially plausible but
incorrect reconstruction that writes stale `$t1`/`$t2` values.  This recovery
accounts for the complete 16-instruction matrix setup at `0x8008BFB0`.
Its retail use of trapping `add`/`addi`, `$gp` as an ordinary working register,
two `$ra` saves, and a manually nested call frame identifies the renderer as
hand-written assembly rather than compiler-emitted C; its semantic C candidate
is therefore retained as documentation instead of being claimed as an exact C
match.

These candidates are research inputs and are not listed as matching units until
they reproduce their target byte ranges exactly.  The raw wrappers remain the
authoritative build fallback meanwhile.

The adjacent polling routine `func_800940C4` has been promoted to exact C.  Its
volatile stack reload and constrained hardware-pointer loads reproduce all 148
retail bytes.
