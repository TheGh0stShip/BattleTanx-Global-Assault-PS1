extern unsigned char *D_800B5940;

int func_80091548(unsigned int value) {
    register unsigned int index asm("$3") = value & 0xFFFF;
    register unsigned char *base asm("$4");
    register int result asm("$2");

    if ((int)index < 3) {
        result = 1;
        base = D_800B5940;
        index <<= 4;
        index += (unsigned int)base;
        *(unsigned short *)index = 0;
    } else {
        result = 0;
    }
    asm volatile("");
    return result;
}
