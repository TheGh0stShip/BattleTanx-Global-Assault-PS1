extern int D_800EF0D4;

int func_80096008(int value) {
    register int *state asm("$3") = &D_800EF0D4;
    int previous;

    asm("" : "+r"(state));
    previous = *state;
    *state = value;
    return previous;
}
