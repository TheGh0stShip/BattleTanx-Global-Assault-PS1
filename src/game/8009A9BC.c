extern unsigned int *D_800B7704;

void func_8009A9BC(void) {
    register unsigned int *state asm("$4") = *(unsigned int **)0x800B7704;
    register unsigned int value asm("$2");
    register unsigned int mask asm("$3");

    asm("" : "+r"(state));
    mask = 0xF0FFFFFF;
    value = *state;

    value &= mask;
    mask = 0x20000000;
    value |= mask;
    asm("" : "+r"(value), "+r"(mask));
    *state = value;
}
