# Requested large-function recovery

This work set covers four previously raw instruction wrappers totaling 27,276
bytes.  The candidate files preserve the complete recovered control flow while
compiler matching continues:

| Function | Target bytes | Recovery status |
| --- | ---: | --- |
| `func_80044C38` | 7,052 | Complete C control flow; recompiles to 7,024 bytes with `--expand-div` |
| `func_80065920` | 11,168 | Full lifted control-flow draft and both recovered jump tables; GTE placeholders remain |
| `func_8007AE20` | 4,788 | Complete compiling crash-screen disassembler draft and both jump tables |
| `func_8008BF7C` | 4,268 | Full lifted renderer draft; GTE operations still require typed intrinsics |

`func_80044C38` corresponds to the N64 tank input/update routine
`func_80091768`.  The PS1 implementation replaces its floating-point steering,
normalization, and suspension calculations with 20.12 fixed-point operations,
including GTE `LZCS`/`LZCR` normalization.  Its candidate intentionally uses
small inline helpers for those two compiler-lowered arithmetic idioms.

`func_8007AE20` is the exception display and MIPS instruction formatter, not
gameplay code.  Its nested opcode/funct dispatch tables are recovered as
`jtbl_800C490C` and `jtbl_800C49FC`.

These candidates are research inputs and are not listed as matching units until
they reproduce their target byte ranges exactly.  The raw wrappers remain the
authoritative build fallback meanwhile.
