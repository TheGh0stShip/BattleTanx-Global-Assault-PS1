extern void *(*D_800B8C88)(void *value);
extern void func_8009F39C(void *state, int value);

void func_80094CE4(void *value, int argument) {
    void *state = D_800B8C88(value);

    func_8009F39C(state, argument);
}
