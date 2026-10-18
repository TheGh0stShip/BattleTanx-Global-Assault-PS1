extern int D_800EC334[];

void func_8007F740(unsigned int divisor) {
    register int *state asm("$5");
    register unsigned int value asm("$2");

    asm("lui $2,%%hi(D_800EC334)\n\t"
        "addiu $5,$2,%%lo(D_800EC334)" : "=r"(state));
    value = state[4] * state[5];

    if (divisor == 0) {
        divisor = 1;
    }
    asm volatile(
        ".set noreorder\n\t"
        "divu $0,%0,%1\n\t"
        "bne %1,$0,1f\n\t"
        ".word 0x0007000D\n"
        "1:\n\t"
        "mflo %0"
        : "+r"(value)
        : "r"(divisor)
    );
    state[5] = divisor;
    state[3] = 0;
    state[4] = value;
}
