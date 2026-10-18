extern unsigned char *D_800D2FE0;

void func_8004E0BC(unsigned char *object) {
    register unsigned char *entry asm("$3") = object + 0xB8;
    unsigned char *texture = D_800D2FE0 + 0x12C;

    asm("" : "+r"(entry));
    *(unsigned int *)(object + 0xB8) = 0;
    *(unsigned int *)(entry + 0x04) = 0;
    *(unsigned int *)(entry + 0x08) = 0x0FA00000;
    entry[0x10] = 0;
    entry[0x11] = 0;
    *(unsigned char **)(entry + 0x0C) = texture;
    *(unsigned int *)(object + 0x180) &= ~1U;
}
