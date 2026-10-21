"""Bounds-checked decoders for BattleTanx: Global Assault (PS1, SLUS-01044) asset files.

All multi-byte reads are explicit little-endian with fixed widths.  File offsets are
kept as Python integers and are never treated as host pointers.  Every decoder raises
FormatError on truncated, oversized, or inconsistent input instead of guessing.
"""
__version__ = "0.1.0"
