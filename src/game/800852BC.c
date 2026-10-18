int func_800852BC(unsigned int value) {
    unsigned int mask;
    unsigned int shift;
    int bit;
    int result = 0;

    if (value != 0) {
        mask = 0xFFFF0000;
        shift = 16;
        bit = 31;
        do {
            if (value & mask) {
                value >>= shift;
            } else {
                bit -= shift;
            }
            shift >>= 1;
            mask >>= shift;
        } while (shift != 0);
        result = bit;
    }
    return result;
}
