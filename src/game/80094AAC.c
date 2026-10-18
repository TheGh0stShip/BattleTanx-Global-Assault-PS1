int func_80094AAC(int value) {
    register int result asm("$3") = value;
    register unsigned int index asm("$2") = (unsigned char)result;
    register unsigned char *table asm("$1");
    register unsigned int flags asm("$2");

    asm("" : "+r"(result), "+r"(index));
    table = (unsigned char *)0x800B0000;
    asm("addu $1,$1,$2" : "+r"(table) : "r"(index));
    flags = table[0x6B31];
    if ((flags & 1) != 0) {
        result = value + 32;
    }
    return (signed char)result;
}
