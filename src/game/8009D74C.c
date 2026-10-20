typedef struct RegisterState {
    unsigned int ra;
    unsigned int sp;
    unsigned int fp;
    unsigned int s0;
    unsigned int s1;
    unsigned int s2;
    unsigned int s3;
    unsigned int s4;
    unsigned int s5;
    unsigned int s6;
    unsigned int s7;
    unsigned int gp;
} RegisterState;

int func_8009D74C(RegisterState *state) {
    register int result asm("$2");

    asm volatile("sw $31,0(%0)\n\t"
                 "sw $28,44(%0)\n\t"
                 "sw $29,4(%0)\n\t"
                 "sw $30,8(%0)\n\t"
                 "sw $16,12(%0)\n\t"
                 "sw $17,16(%0)\n\t"
                 "sw $18,20(%0)\n\t"
                 "sw $19,24(%0)\n\t"
                 "sw $20,28(%0)\n\t"
                 "sw $21,32(%0)\n\t"
                 "sw $22,36(%0)\n\t"
                 "sw $23,40(%0)"
                 : : "r"(state) : "memory");
    result = 0;
    asm volatile("" : "+r"(result) : : "memory");
    return result;
}
