typedef struct SoundState {
    int unused0;
    volatile unsigned int flags;
    unsigned char unused8[40];
    unsigned char mode;
    unsigned char unused31[3];
    int value34;
    unsigned char unused38[4];
    int value3C;
    unsigned char unused40[4];
    int value44;
    int argument48;
} SoundState;

extern SoundState *D_800EFE14;
extern void func_800A19E4(int value);
extern void func_800A26F4(SoundState *state, int value);

void func_800A2C10(SoundState *state, int mode, int value3C,
                   int value44, int argument48) {
    register SoundState *saved_state asm("$16") = state;
    register int saved_mode asm("$17") = mode;
    register int saved_value3C asm("$18") = value3C;
    register int saved_value44 asm("$19");
    register SoundState *call_state asm("$4");
    register int call_value asm("$5");

    asm("" : "+r"(saved_state), "+r"(saved_mode),
              "+r"(saved_value3C));
    saved_value44 = value44;
    if (saved_state->flags & 1) {
        func_800A19E4(0);
    }
    asm volatile("sb %3,48(%2)\n\t"
                 "sw $0,52(%2)\n\t"
                 "sw %4,60(%2)\n\t"
                 "sw %5,68(%2)\n\t"
                 "lw $2,56($29)\n\t"
                 "addiu $3,$0,-1025\n\t"
                 "sw $2,72(%2)\n\t"
                 "lui $2,%%hi(D_800EFE14)\n\t"
                 "sw %2,%%lo(D_800EFE14)($2)\n\t"
                 "lw $2,4(%2)\n\t"
                 "addu %0,%2,$0\n\t"
                 "and $2,$2,$3\n\t"
                 "sw $2,4(%2)\n\t"
                 "lw $2,4(%2)\n\t"
                 "addu %1,$0,$0\n\t"
                 "ori $2,$2,1\n\t"
                 "sw $2,4(%0)"
                 : "=r"(call_state), "=r"(call_value)
                 : "r"(saved_state), "r"(saved_mode), "r"(saved_value3C),
                   "r"(saved_value44)
                 : "$2", "$3", "memory");
    asm volatile("" : : "m"(call_state->flags) : "memory");
    func_800A26F4(call_state, call_value);
}
