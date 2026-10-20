typedef struct CallbackState {
    int context;
    void (*first)(int, int);
    void (*second)(int);
    void (*third)(int);
} CallbackState;

extern CallbackState D_800EEDE4;

void func_8008EF5C(int unused0, int unused1, int unused2, int status) {
    register CallbackState *base asm("$4");
    register CallbackState *state asm("$3");
    register void (*callback2)(int, int) asm("$2");
    register void (*callback1)(int) asm("$2");
    register int context asm("$4");

    base = (CallbackState *)0x800F0000;
    asm("" : "+r"(base));
    state = (CallbackState *)((unsigned char *)base - 0x121C);
    asm("" : "+r"(state));
    callback2 = state->first;
    if (callback2 != 0) {
        register int callback_status asm("$5");
        asm volatile("lw %0,%%lo(D_800EEDE4)(%2)\n\t"
                     "addu %1,$7,$0"
                     : "=r"(context), "=r"(callback_status) : "r"(base));
        state->first = 0;
        callback2(context, callback_status);
        return;
    }
    callback1 = state->second;
    if (callback1 != 0) {
        context = ((CallbackState *)((unsigned char *)base - 0x121C))->context;
        state->second = 0;
    } else {
        callback1 = state->third;
        if (callback1 == 0) {
            return;
        }
        context = ((CallbackState *)((unsigned char *)base - 0x121C))->context;
        state->third = 0;
    }
    callback1(context);
}
