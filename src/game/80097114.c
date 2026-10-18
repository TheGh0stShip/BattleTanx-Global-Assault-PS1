int func_80097114(int value) {
    register int state asm("$2") = 0x800C0000;
    register int *destination asm("$1");

    asm("" : "+r"(state));
    state = *(int *)(state - 0x72DC);
    asm("" : "+r"(state));
    destination = (int *)0x800C0000;
    asm("" : "+r"(destination));
    destination[-0x72DC / 4] = value;
    return state;
}
