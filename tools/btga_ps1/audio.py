"""PlayStation SPU ADPCM decoding and deterministic PCM WAV output."""
import struct

from .binio import FormatError


FILTERS = ((0, 0), (60, 0), (115, -52), (98, -55), (122, -60))


def decode_spu_adpcm(data, name="<spu-adpcm>"):
    """Decode 16-byte SPU frames to signed 16-bit PCM, stopping at the end flag."""
    if not data or len(data) % 16:
        raise FormatError("%s: ADPCM size %d is not a positive multiple of 16" % (name, len(data)))
    pcm = []
    older = 0
    old = 0
    frame_flags = []
    ended = False
    for off in range(0, len(data), 16):
        control = data[off]
        predictor, shift = control >> 4, control & 0xF
        flags = data[off + 1]
        if predictor >= len(FILTERS) or shift > 12:
            raise FormatError("%s: invalid ADPCM control 0x%02X at 0x%X" % (name, control, off))
        if flags not in (0, 1, 2, 3, 6, 7):
            raise FormatError("%s: invalid ADPCM flags 0x%02X at 0x%X" % (name, flags, off))
        frame_flags.append(flags)
        f0, f1 = FILTERS[predictor]
        for i in range(28):
            packed = data[off + 2 + i // 2]
            nibble = (packed & 0xF) if i % 2 == 0 else (packed >> 4)
            if nibble & 8:
                nibble -= 16
            sample = (nibble << 12) >> shift
            sample += (old * f0 + older * f1 + 32) >> 6
            sample = max(-32768, min(32767, sample))
            pcm.append(sample)
            older, old = old, sample
        if flags & 1:
            ended = True
            break
    if not ended:
        raise FormatError("%s: ADPCM stream has no end frame" % name)
    return {"samples": pcm, "frame_flags": frame_flags, "decoded_frames": len(frame_flags)}


def pitch_sample_rate(pitch):
    """Convert an SPU pitch value (0x1000 = 44.1 kHz) to a WAV sample rate."""
    if not 1 <= pitch <= 0x3FFF:
        raise FormatError("SPU pitch 0x%X outside 1..0x3FFF" % pitch)
    return (44100 * pitch + 0x800) // 0x1000


def encode_wav_mono16(samples, sample_rate):
    pcm = struct.pack("<%dh" % len(samples), *samples)
    fmt = struct.pack("<HHIIHH", 1, 1, sample_rate, sample_rate * 2, 2, 16)
    return (b"RIFF" + struct.pack("<I", 4 + 8 + len(fmt) + 8 + len(pcm)) + b"WAVE" +
            b"fmt " + struct.pack("<I", len(fmt)) + fmt +
            b"data" + struct.pack("<I", len(pcm)) + pcm)
