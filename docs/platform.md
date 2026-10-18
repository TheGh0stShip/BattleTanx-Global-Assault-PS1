# Target platform contract

The target is the original PlayStation, not PlayStation Vita:

- little-endian MIPS R3000A-compatible CPU
- 32-bit addresses and 32-bit general-purpose registers
- o32-style calling convention assumptions must be verified against the game
  and compiler before matching work begins
- the PS-X EXE loads at `0x80010000`; its text size is `0xB6800`, and its entry
  point is `0x800860B0`

Host tools must preserve the original fixed-width disk and command-stream
semantics. Use explicit integer widths and byte order at every binary boundary.
Never cast file offsets into host pointers or depend on native structure layout.
Linux x86-64 hosts are normally LP64, while Windows x64 is LLP64; neither host
layout describes the target.

Before adding target C compilation, identify the original compiler and verify
object-file architecture, endianness, ABI, alignment, calling convention, and
code-generation flags. Add compile-time layout assertions where reconstructed
structures cross binary boundaries. Emulator and host test results are useful
evidence, but do not establish behavior on physical hardware.
