"""Minimal deterministic RGBA PNG writer (stdlib only, no timestamps)."""
import struct
import zlib


def _chunk(tag, data):
    return struct.pack(">I", len(data)) + tag + data + struct.pack(">I", zlib.crc32(tag + data) & 0xFFFFFFFF)


def encode_rgba(width, height, pixels):
    """pixels: sequence of (r,g,b,a) tuples, row-major, len == width*height."""
    if width <= 0 or height <= 0 or len(pixels) != width * height:
        raise ValueError("bad PNG geometry")
    raw = bytearray()
    for y in range(height):
        raw.append(0)
        for p in pixels[y * width:(y + 1) * width]:
            raw.extend(p)
    ihdr = struct.pack(">IIBBBBB", width, height, 8, 6, 0, 0, 0)
    return (b"\x89PNG\r\n\x1a\n" + _chunk(b"IHDR", ihdr)
            + _chunk(b"IDAT", zlib.compress(bytes(raw), 9)) + _chunk(b"IEND", b""))
