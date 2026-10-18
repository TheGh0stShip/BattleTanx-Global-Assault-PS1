extern unsigned char D_800EE028[];

void func_80085258(unsigned int index) {
    register unsigned char *base asm("$3") = D_800EE028;
    signed char *entry;

    asm("" : "+r"(base));
    entry = (signed char *)(index * 140 + (unsigned int)base);
    entry[0x12] = 0;
    entry[0x13] = 0;
    entry[0x14] = -128;
    entry[0x15] = -128;
    entry[0x16] = 127;
    entry[0x17] = 127;
    entry[0x18] = 0;
    entry[0x1B] = 0;
    entry[0x1C] = 0;
    entry[0x1D] = -128;
    entry[0x1E] = -128;
    entry[0x1F] = 127;
    entry[0x20] = 127;
    entry[0x21] = 0;
}
