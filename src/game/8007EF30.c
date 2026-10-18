extern unsigned char D_800EC200[];

int func_8007EF30(int enabled) {
    register int *state asm("$3");
    int previous;

    asm("lui $2,%%hi(D_800EC200)\n\t"
        "addiu $3,$2,%%lo(D_800EC200)" : "=r"(state));
    previous = state[0x108 / 4] == 2;
    state[0x108 / 4] = enabled ? 2 : 1;
    return previous;
}
