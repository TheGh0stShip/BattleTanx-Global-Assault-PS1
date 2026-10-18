extern unsigned char *D_800D2FE0;

void func_8004DFC0(unsigned char *object) {
    unsigned char *entry = D_800D2FE0 + 0x12C;

    *(unsigned int *)(object + 0x00) = 0;
    *(unsigned int *)(object + 0x04) = 0;
    *(unsigned int *)(object + 0x08) = 0x0FA00000;
    object[0x10] = 0;
    object[0x11] = 0;
    *(unsigned char **)(object + 0x0C) = entry;
}
