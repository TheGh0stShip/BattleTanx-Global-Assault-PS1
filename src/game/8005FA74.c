typedef struct StateOwner {
    int unused;
    unsigned char *state;
} StateOwner;

extern unsigned char D_800AACD9;
extern unsigned char D_800AACDA;

int func_8005FA74(StateOwner *owner) {
    register unsigned char *state __asm__("$3") = owner->state;
    register int value __asm__("$2");

    value = D_800AACD9;
    if (value) {
        value = 1;
    } else {
        value = 9;
    }
    state[0x280] = value;

    value = D_800AACDA;
    if (!value) {
        goto disabled;
    }
    __asm__ volatile ("");
    value = 1;
    goto store;
disabled:
    value = 9;
store:
    state[0x2A0] = value;
    return 0;
}
