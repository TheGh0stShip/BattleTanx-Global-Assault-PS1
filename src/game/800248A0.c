extern unsigned char *D_800D2FE4;

void func_800248A0(const unsigned char *source) {
    unsigned char *destination = D_800D2FE4;

    destination[0x1C4] = source[1];
    destination[0x1C5] = source[2];
    destination[0x1C6] = source[3];
}
