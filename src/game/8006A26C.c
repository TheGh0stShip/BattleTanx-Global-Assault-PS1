typedef unsigned char u8;

typedef struct State {
    u8 pad_00[0x14];
    int lower;
    u8 pad_18[4];
    int upper;
} State;

extern State D_800ADD14;

void func_8006A26C(int amount) {
    register State *state asm("$3") = &D_800ADD14;
    register int lower asm("$2");
    register int upper asm("$5");
    register int lower_result asm("$6");

    asm("" : "+r"(state));
    lower = state->lower;
    asm("" : "+r"(lower));
    upper = state->upper;
    asm("" : "+r"(upper));
    lower_result = lower + amount;
    asm("" : "+r"(lower_result));
    upper -= amount;
    state->lower = lower_result;
    state->upper = upper;
}
