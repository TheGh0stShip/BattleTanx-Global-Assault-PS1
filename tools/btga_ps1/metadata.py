"""Disc text, boot configuration, executable container, and licence sectors."""
from .binio import FormatError, Reader


def decode_ascii_text(data, name="<text>"):
    if not data:
        raise FormatError("%s: empty text file" % name)
    try:
        text = data.decode("ascii")
    except UnicodeDecodeError as e:
        raise FormatError("%s: non-ASCII byte at 0x%X" % (name, e.start))
    for offset, value in enumerate(data):
        if value < 0x20 and value not in (0x09, 0x0A, 0x0D):
            raise FormatError("%s: control byte 0x%02X at 0x%X" % (name, value, offset))
        if value == 0x7F:
            raise FormatError("%s: DEL byte at 0x%X" % (name, offset))
    crlf = data.count(b"\r\n")
    bare_cr = data.count(b"\r") - crlf
    bare_lf = data.count(b"\n") - crlf
    return {
        "encoding": "ASCII",
        "text": text,
        "lines": text.splitlines(),
        "line_endings": {"crlf": crlf, "cr": bare_cr, "lf": bare_lf},
        "trailing_newline": text.endswith(("\r", "\n")),
    }


def decode_system_cnf(data, name="<system.cnf>"):
    decoded = decode_ascii_text(data, name)
    entries = []
    values = {}
    for index, line in enumerate(decoded["lines"]):
        if not line or "=" not in line:
            raise FormatError("%s: line %d is not KEY=VALUE" % (name, index + 1))
        key, value = line.split("=", 1)
        key, value = key.strip(), value.strip()
        if not key or not value:
            raise FormatError("%s: line %d has an empty key or value" % (name, index + 1))
        if key in values:
            raise FormatError("%s: duplicate key %s" % (name, key))
        values[key] = value
        entries.append({"key": key, "value": value})
    if "BOOT" not in values:
        raise FormatError("%s: missing BOOT entry" % name)
    boot = values["BOOT"]
    if not boot.lower().startswith("cdrom:\\") or ";" not in boot:
        raise FormatError("%s: malformed BOOT entry" % name)
    path, version = boot[6:].rsplit(";", 1)
    path = path.lstrip("\\/")
    if not path or not version.isdigit():
        raise FormatError("%s: malformed BOOT path or version" % name)
    return decoded | {
        "entries": entries,
        "boot_path": path,
        "boot_version": int(version),
    }


def decode_psx_exe(data, name="<psx-exe>"):
    r = Reader(data, name)
    if len(r) < 0x800:
        raise FormatError("%s: shorter than the 0x800-byte header" % name)
    r.magic(0, b"PS-X EXE")
    fields = {
        "entry": r.u32(0x10),
        "initial_gp": r.u32(0x14),
        "load_address": r.u32(0x18),
        "text_bytes": r.u32(0x1C),
        "data_address": r.u32(0x20),
        "data_bytes": r.u32(0x24),
        "bss_address": r.u32(0x28),
        "bss_bytes": r.u32(0x2C),
        "stack_address": r.u32(0x30),
        "stack_bytes": r.u32(0x34),
    }
    if fields["text_bytes"] == 0 or fields["text_bytes"] % 0x800:
        raise FormatError("%s: text size is not a positive sector multiple" % name)
    if len(r) != 0x800 + fields["text_bytes"]:
        raise FormatError("%s: size does not equal header plus text size" % name)
    marker_raw = r.bytes(0x4C, 0x800 - 0x4C).split(b"\0", 1)[0]
    try:
        marker = marker_raw.decode("ascii")
    except UnicodeDecodeError:
        raise FormatError("%s: non-ASCII header marker" % name)
    return fields | {
        "header_bytes": 0x800,
        "text_offset": 0x800,
        "header_marker": marker,
    }


def decode_licence_sectors(data, name="<licence>"):
    """Decode 2336-byte Mode 2 sectors as duplicated subheaders plus payloads."""
    r = Reader(data, name)
    if len(r) == 0 or len(r) % 2336:
        raise FormatError("%s: size is not a positive multiple of 2336" % name)
    sectors = []
    for index in range(len(r) // 2336):
        offset = 2336 * index
        subheader = r.bytes(offset, 8)
        if subheader[:4] != subheader[4:]:
            raise FormatError("%s: sector %d subheader copies differ" % (name, index))
        sectors.append({
            "index": index,
            "offset": offset,
            "file": subheader[0],
            "channel": subheader[1],
            "submode": subheader[2],
            "coding": subheader[3],
            "payload_offset": offset + 8,
            "payload_bytes": 2328,
        })
    return {"sector_bytes": 2336, "sectors": sectors}
