extern unsigned char *D_800D2FE4;

void func_800247DC(unsigned char *src) {
    unsigned char *dst = D_800D2FE4;

    dst[0x1B4] = 1;
    dst[0x1B5] = src[4];
    dst[0x1B6] = src[5];
    dst[0x1B7] = src[6];
    dst[0x1BB] = src[10];
    dst[0x1BC] = src[11];
    dst[0x1BD] = src[12];
    dst[0x1B8] = src[7];
    dst[0x1B9] = src[8];
    dst[0x1BA] = src[9];
    dst[0x1BE] = src[13];
    dst[0x1BF] = src[14];
    dst[0x1C0] = src[15];
    dst[0x1C1] = src[1];
    dst[0x1C2] = src[2];
    dst[0x1C3] = src[3];
}
