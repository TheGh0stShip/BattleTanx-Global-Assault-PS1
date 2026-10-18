typedef unsigned short u16;

int func_800914E4(u16 value) {
    register int index asm("$2") = value;
    register unsigned int offset asm("$4");
    register unsigned int *state asm("$5");
    register unsigned char *table asm("$1");
    register unsigned int bits asm("$3");

    asm("" : "+r"(index));
    offset = index << 2;
    asm("" : "+r"(offset));
    state = (unsigned int *)0x800B0000;
    asm("" : "+r"(state));
    state = *(unsigned int **)((unsigned char *)state + 0x593C);
    asm("" : "+r"(state));
    table = (unsigned char *)0x800B0000;
    asm("addu $1,$1,$4" : "+r"(table) : "r"(offset));
    offset = *(unsigned int *)(table + 0x5944);
    bits = state[1];
    index = index < 3;
    bits |= offset;
    state[1] = bits;
    return index;
}
