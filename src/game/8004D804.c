void func_8004D804(unsigned char *object) {
    unsigned char *entry = object + 0xD8;

    entry[0x18] = 0;
    *(int *)(entry + 0x08) = 0;
    *(int *)(entry + 0x00) = 0;
    *(int *)(entry + 0x0C) = 0;
    *(int *)(entry + 0x10) = 0;
    *(short *)(entry + 0x14) = 0;
    entry[0x16] = 0;
    entry[0x17] = 0;
    entry[0x19] = 0;
    object[0xF1] = 1;
}
