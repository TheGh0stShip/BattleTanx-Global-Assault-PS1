void func_8009A964(int mode) {
    register unsigned int **globals asm("$5") = (unsigned int **)0x800B0000;
    register unsigned int *state asm("$5");
    register unsigned int value asm("$2");
    register unsigned int mask asm("$3");
    register unsigned int *next asm("$2");
    register unsigned int current asm("$3");
    register unsigned int bits asm("$4");

    asm("" : "+r"(globals));
    state = globals[0x1DC0];
    asm("" : "+r"(state));
    mask = 0xFFF8FFFF;
    value = *state;
    value &= mask;
    asm("" : "+r"(value), "+r"(mask));
    *state = value;

    if (mode != 0) {
        next = (unsigned int *)0x800B0000;
        asm("" : "+r"(next));
        next = ((unsigned int **)next)[0x1DC0];
        asm("" : "+r"(next));
        current = *next;
        asm("" : "+r"(current));
        bits = 0x00030000;
    } else {
        next = (unsigned int *)0x800B0000;
        asm("" : "+r"(next));
        next = ((unsigned int **)next)[0x1DC0];
        asm("" : "+r"(next));
        current = *next;
        asm("" : "+r"(current));
        bits = 0x00050000;
    }
    current |= bits;
    asm("" : "+r"(next), "+r"(current), "+r"(bits));
    *next = current;
}
