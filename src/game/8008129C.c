int func_8008129C(int index) {
    register unsigned char *table asm("$2") = (unsigned char *)0x800F0000;

    asm("addu $2,$2,$4" : "+r"(table) : "r"(index));
    return table[-0x3C6C];
}
