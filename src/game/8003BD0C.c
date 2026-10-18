extern unsigned char D_800DE030[];

void func_8008D0A8(void *state, void *input, void *output);
void func_8008D028(void *state);

void func_8003BD0C(void *input) {
    unsigned char state[32];

    func_8008D0A8(D_800DE030, input, state);
    func_8008D028(state);
}
