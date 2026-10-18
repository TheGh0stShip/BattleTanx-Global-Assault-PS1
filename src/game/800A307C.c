extern int D_800EFE34;

int func_800A307C(int value) {
    register int *state asm("$3") = &D_800EFE34;
    int previous;

    asm("" : "+r"(state));
    previous = *state;
    *state = value;
    return previous;
}
