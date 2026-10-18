extern unsigned char D_800A8B24[];
extern unsigned char D_800EAD64[];
extern unsigned char D_800EADD0[];

void func_80060B54(unsigned int flags) {
    register unsigned char *base asm("$2");
    register int value asm("$3");

    flags &= 1;
    if (flags) {
        base = D_800A8B24;
        *(unsigned char **)(base + 0x3E8) = D_800EAD64;
        value = 2;
    } else {
        base = D_800A8B24;
        *(unsigned char **)(base + 0x3E8) = D_800EADD0;
        value = 1;
    }
    base[0x3A1] = value;
    base[0x3E1] = value;
}
