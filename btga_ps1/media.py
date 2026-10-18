"""Helpers for the disc's headerless 2,336-byte Mode-2 STR/PCK sectors."""

from .binio import FormatError


SECTOR_DATA_BYTES = 2336
RAW_SECTOR_BYTES = 2352
SYNC = b"\x00" + b"\xFF" * 10 + b"\x00"


def _bcd(value):
    return ((value // 10) << 4) | (value % 10)


def wrap_mode2_sectors(data, name="<mode2>", start_lba=0):
    """Restore sync, BCD MSF address, and mode byte to headerless Mode-2 sectors."""
    if len(data) % SECTOR_DATA_BYTES:
        raise FormatError("%s: size is not a multiple of 2336" % name)
    out = bytearray()
    for i in range(len(data) // SECTOR_DATA_BYTES):
        absolute = start_lba + i + 150
        minute, rem = divmod(absolute, 75 * 60)
        second, frame = divmod(rem, 75)
        if minute > 99:
            raise FormatError("%s: synthesized MSF address exceeds 99 minutes" % name)
        out += SYNC + bytes((_bcd(minute), _bcd(second), _bcd(frame), 2))
        at = i * SECTOR_DATA_BYTES
        out += data[at:at + SECTOR_DATA_BYTES]
    return bytes(out)
