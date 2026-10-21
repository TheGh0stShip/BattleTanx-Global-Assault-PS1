"""Little-endian fixed-width readers with bounds and alignment checks."""
import struct


class FormatError(ValueError):
    """Raised when bytes do not satisfy a proven format contract."""


class Reader:
    def __init__(self, data, name="<bytes>"):
        if not isinstance(data, (bytes, bytearray, memoryview)):
            raise TypeError("data must be bytes-like")
        self.data = bytes(data)
        self.name = name

    def __len__(self):
        return len(self.data)

    def need(self, off, size, what="field"):
        if off < 0 or size < 0 or off + size > len(self.data):
            raise FormatError("%s: %s at 0x%X+0x%X exceeds size 0x%X" % (self.name, what, off, size, len(self.data)))

    def aligned(self, off, align, what="field"):
        if off % align:
            raise FormatError("%s: %s at 0x%X is not %d-byte aligned" % (self.name, what, off, align))

    def u8(self, off, what="u8"):
        self.need(off, 1, what)
        return self.data[off]

    def u16(self, off, what="u16"):
        self.need(off, 2, what)
        return struct.unpack_from("<H", self.data, off)[0]

    def s16(self, off, what="s16"):
        self.need(off, 2, what)
        return struct.unpack_from("<h", self.data, off)[0]

    def u32(self, off, what="u32"):
        self.need(off, 4, what)
        return struct.unpack_from("<I", self.data, off)[0]

    def s32(self, off, what="s32"):
        self.need(off, 4, what)
        return struct.unpack_from("<i", self.data, off)[0]

    def bytes(self, off, size, what="bytes"):
        self.need(off, size, what)
        return self.data[off:off + size]

    def magic(self, off, expect):
        got = self.bytes(off, len(expect), "magic")
        if got != expect:
            raise FormatError("%s: magic %r != %r" % (self.name, got, expect))


def bgr555_to_rgba(v):
    """PS1 15-bit colour: bits 0-4 R, 5-9 G, 10-14 B, bit 15 STP.

    Returns (r, g, b, a).  Raw value 0x0000 is the hardware transparent texel
    for textured primitives, so alpha is 0 for exactly that value and 255 otherwise;
    the raw 16-bit value is always preserved separately by callers.
    """
    r = (v & 0x1F) << 3
    g = ((v >> 5) & 0x1F) << 3
    b = ((v >> 10) & 0x1F) << 3
    return (r | (r >> 5), g | (g >> 5), b | (b >> 5), 0 if v == 0 else 255)
