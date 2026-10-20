typedef struct SoundState {
    int unused0;
    unsigned int flags;
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
extern void func_800A1B2C(SoundState *state, unsigned char mode, int value);

void func_800A2B78(SoundState *state, int enabled, int argument) {
    register SoundState *call_state asm("$4");
    register int call_value asm("$6");
    register unsigned int flags asm("$2");
    register unsigned int mode asm("$5");

    if (state->flags & 1) {
        func_800A19E4(0);
    }
    state->mode = enabled ? 1 : 3;
    asm volatile("lui $2,%%hi(D_800EFE14)\n\t"
                 "addu %0,%2,$0\n\t"
                 "addiu %1,$0,10\n\t"
                 "sw $0,52(%2)\n\t"
                 "sw $0,60(%2)\n\t"
                 "sw $0,68(%2)\n\t"
                 "sw %3,72(%2)\n\t"
                 "sw %2,%%lo(D_800EFE14)($2)"
                 : "=r"(call_state), "=r"(call_value)
                 : "r"(state), "r"(argument) : "$2", "memory");
    flags = state->flags;
    mode = call_state->mode;
    flags |= 1;
    call_state->flags = flags;
    asm volatile("" : : "m"(call_state->flags) : "memory");
    func_800A1B2C(call_state, mode, call_value);
}
