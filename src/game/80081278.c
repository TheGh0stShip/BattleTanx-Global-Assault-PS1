extern unsigned int *D_800B0D38;

void func_80081278(unsigned int value) {
    register unsigned int index asm("$2");
    register unsigned char *table asm("$1");

    *D_800B0D38 = value;
    asm("" : : : "memory");
    index = value >> 24;
    asm("" : "+r"(index));
    table = (unsigned char *)0x800F0000;
    asm("addu $1,$1,$2" : "+r"(table) : "r"(index));
    table[-0x3C6C] = (unsigned char)value;
}
