typedef void (*DisplayCallback)(void *state, unsigned int enabled,
                                unsigned int mode, unsigned int option);

extern DisplayCallback D_800B0C5C;
extern unsigned char D_800B0C62[];
extern unsigned char D_800C4B58;

unsigned int func_8007F980(unsigned int enabled)
{
    volatile char outgoing[16];
    register unsigned char *state asm("$3") = D_800B0C62;
    register unsigned int previous asm("$16");
    register unsigned int result asm("$2");
    register unsigned int argument asm("$4") = enabled;

    asm("" : "+r"(state), "+r"(argument));
    previous = state[0];
    state[0] = argument;
    argument &= 0xFF;
    asm volatile(
        ".set noreorder\n\t"
        "beqz %3,1f\n\t"
        "addu %0,%2,$zero\n\t"
        "lui $2,%%hi(D_800B0C5C)\n\t"
        "lw $2,%%lo(D_800B0C5C)($2)\n\t"
        "lbu $5,0(%1)\n\t"
        "lbu $6,-2(%1)\n\t"
        "lbu $7,1(%1)\n\t"
        "lui $4,%%hi(D_800C4B58)\n\t"
        "jalr $2\n\t"
        "addiu $4,$4,%%lo(D_800C4B58)\n\t"
        "addu %0,%2,$zero\n"
        "1:\n\t"
        ".set reorder"
        : "=r"(result)
        : "r"(state), "r"(previous), "r"(argument)
        : "$4", "$5", "$6", "$7", "$31", "memory"
    );
    return result;
}
