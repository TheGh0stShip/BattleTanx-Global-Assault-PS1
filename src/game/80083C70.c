extern unsigned char D_800EE028[];

void func_80083C70(unsigned int index) {
    register unsigned char *base asm("$3") = D_800EE028;
    unsigned char *entry;

    asm("" : "+r"(base));
    entry = (unsigned char *)(index * 140 + (unsigned int)base);

    *(unsigned int *)(entry + 0x00) = 0;
    *(unsigned short *)(entry + 0x04) = 0;
    *(unsigned short *)(entry + 0x06) = 0;
    *(unsigned short *)(entry + 0x08) = 0;
    *(unsigned short *)(entry + 0x0A) = 0;
    *(unsigned short *)(entry + 0x0C) = 0;
    *(unsigned short *)(entry + 0x0E) = 0;
    entry[0x10] = 0;
    entry[0x11] = 0;
    entry[0x19] = 0;
    entry[0x1A] = 0;
    entry[0x22] = 0;
    entry[0x23] = 0;
    *(unsigned short *)(entry + 0x24) = 0;
    *(unsigned short *)(entry + 0x26) = 0;
    *(unsigned short *)(entry + 0x28) = 0;
}
