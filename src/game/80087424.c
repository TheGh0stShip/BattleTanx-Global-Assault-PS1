extern unsigned char D_800EE588[];

void func_80087424(int first, int second, int type, int enabled) {
    register unsigned char *state asm("$2");

    if (type != 4) {
        enabled = 0;
    }
    state = (unsigned char *)0x800F0000;
    if (enabled != 0) {
        register unsigned int value asm("$3");
        asm("" : "+r"(state));
        state -= 0x1A78;
        asm("" : "+r"(state));
        value = 1;
        asm("" : "+r"(state), "+r"(value));
        state[9] = value;
        asm("");
        return;
    }
    asm("" : "+r"(state));
    state -= 0x1A78;
    asm("" : "+r"(state));
    state[9] = 0;
    asm("");
}
