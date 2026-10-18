int func_80094A48(int value) {
    register int state asm("$2") = 0x800B0000;
    register int *destination asm("$1");

    asm("" : "+r"(state));
    state = *(int *)(state + 0x6B20);
    asm("" : "+r"(state));
    destination = (int *)0x800B0000;
    asm("" : "+r"(destination));
    destination[0x6B20 / 4] = value;
    return state;
}
