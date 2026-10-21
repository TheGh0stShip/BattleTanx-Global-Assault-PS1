# Requested large-function recovery

This work set covers four previously raw instruction wrappers totaling 27,276
bytes.  The candidate files preserve the complete recovered control flow while
compiler matching continues:

| Function | Target bytes | Recovery status |
| --- | ---: | --- |
| `func_80044C38` | 7,052 | Complete C control flow; recompiles to 7,024 bytes with `--expand-div` |
| `func_80065920` | 11,168 | Compiler-valid 9,184-byte draft with both jump tables and 298 recovered hardware operations |
| `func_8007AE20` | 4,788 | Complete compiling crash-screen disassembler draft and both jump tables |
| `func_8008BF7C` | 4,268 | Compiler-valid 4,208-byte renderer with recovered scratchpad state, matrix loads, and complete COP2 stream |

`func_80044C38` corresponds to the N64 tank input/update routine
`func_80091768`.  The PS1 implementation replaces its floating-point steering,
normalization, and suspension calculations with 20.12 fixed-point operations,
including GTE `LZCS`/`LZCR` normalization.  Its candidate intentionally uses
small inline helpers for those two compiler-lowered arithmetic idioms.

`func_8007AE20` is the exception display and MIPS instruction formatter, not
gameplay code.  Its nested opcode/funct dispatch tables are recovered as
`jtbl_800C490C` and `jtbl_800C49FC`.

`func_8008BF7C` begins by loading one 32-byte matrix into GTE control
registers 0 through 7.  Keeping the loads and `ctc2` operations in one inline
helper preserves their dependency and prevents a superficially plausible but
incorrect reconstruction that writes stale `$t1`/`$t2` values.  This recovery
accounts for the complete 16-instruction matrix setup at `0x8008BFB0`.

These candidates are research inputs and are not listed as matching units until
they reproduce their target byte ranges exactly.  The raw wrappers remain the
authoritative build fallback meanwhile.

The adjacent polling candidate `func_800940C4` now emits the complete 148-byte
instruction body.  Its volatile stack reload restores the retail load-delay
sequence and raises the byte agreement from 103 to 138 of 148 bytes; only two
compiler register/scheduling choices remain before promotion.
