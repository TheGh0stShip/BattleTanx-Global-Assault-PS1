extern void func_80054EF4(unsigned int value);

void func_80031344(unsigned char *state) {
    if (state[0x32] != 100) {
        func_80054EF4(state[0x32]);
    }
}
