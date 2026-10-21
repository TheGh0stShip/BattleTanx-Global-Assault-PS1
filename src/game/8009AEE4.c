unsigned short func_8009AEE4(unsigned short centerNote, unsigned short centerFine,
                             unsigned short note, unsigned short fine) {
    int center;
    int diff;
    int dist;
    int octave;
    int rem;
    int scale;
    int mag;
    unsigned int base;
    unsigned int factor;
    unsigned int low;
    unsigned int high;
    int steps;
    int frac;
    int i;
    unsigned int pitch;

    center = (centerNote << 7) + centerFine;
    diff = ((note << 7) + fine) - center;
    dist = diff;
    if (diff < 0) {
        dist = -diff;
    }
    octave = dist / 1536;
    rem = dist % 1536;
    if (diff >= 0) {
        scale = 4096 << octave;
    } else {
        if (rem != 0) {
            octave++;
            rem = 1536 - rem;
        }
        scale = 4096 >> octave;
    }
    base = (unsigned short)scale;
    low = base << 12;
    factor = 4155;
    high = base * factor;
    mag = __builtin_abs(rem);
    steps = (unsigned int)mag >> 5;
    frac = mag & 31;
    i = 0;
    if (steps != 0) {
        do {
            low = base * factor;
            factor *= 4155;
            factor >>= 12;
            high = base * factor;
        } while (++i < steps);
    }
    pitch = (low + ((high - low) >> 5) * frac) >> 12;
    if (pitch > 0x3FFF) {
        pitch = 0x3FFF;
    }
    return pitch;
}
