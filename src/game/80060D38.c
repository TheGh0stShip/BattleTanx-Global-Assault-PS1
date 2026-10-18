extern unsigned char D_800A8B18;
extern unsigned short D_800AACDE;
int func_80060D38(void) {
    D_800A8B18 = 0;
    D_800AACDE = 0;
    asm("" : : : "memory");
    {
        register unsigned char *base asm("$2") = (unsigned char *)0x800B0000;
        asm("" : "+r"(base));
        base -= 0x74DC;
        asm("" : "+r"(base));
        *(unsigned int *)(base + 0x3A8) = 0;
        *(unsigned int *)(base + 0x3E8) = 0;
    }
    return 0;
}
