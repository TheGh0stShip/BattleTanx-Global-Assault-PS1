extern int D_800EC334[];

void func_8007F708(int first, unsigned int size) {
    register int *state asm("$3") = D_800EC334;
    register unsigned int divisor asm("$2") = state[5];
    register unsigned int quotient asm("$5") = size;

    asm volatile(
        ".set noreorder\n\t"
        "nop\n\t"
        "divu $0,%0,%1\n\t"
        "bne %1,$0,1f\n\t"
        "break 0x1C00\n"
        "1:\n\t"
        "mflo %0"
        : "+r"(quotient)
        : "r"(divisor)
    );
    state[2] = first;
    asm volatile("" : : : "memory");
    quotient &= ~3U;
    state[4] = quotient;
}
