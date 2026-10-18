typedef unsigned short u16;

int func_80091514(u16 value) {
    register unsigned int offset asm("$4") = value;
    register unsigned int *state asm("$5");
    register unsigned char *table asm("$2");
    register unsigned int bits asm("$3");

    asm("" : "+r"(offset));
    offset <<= 2;
    asm("" : "+r"(offset));
    state = (unsigned int *)0x800B0000;
    asm("" : "+r"(state));
    state = *(unsigned int **)((unsigned char *)state + 0x593C);
    asm("" : "+r"(state));
    table = (unsigned char *)0x800B0000;
    asm("" : "+r"(table));
    table += offset;
    asm("" : "+r"(table));
    table = (unsigned char *)(unsigned long)*(unsigned int *)(table + 0x5944);
    bits = state[1];
    table = (unsigned char *)~(unsigned long)table;
    bits &= (unsigned long)table;
    table = (unsigned char *)1;
    state[1] = bits;
    return (int)(unsigned long)table;
}
