unsigned char func_800A195C(void);
int func_800A2094(unsigned char *state, int value);
void func_800A19E4(int value);

void func_800A1BEC(unsigned char *state) {
    state[0x31] = func_800A195C();
    (*(unsigned int *)(state + 0x28))++;
    if (func_800A2094(state, 0) == 0) {
        func_800A19E4(0);
    }
}
