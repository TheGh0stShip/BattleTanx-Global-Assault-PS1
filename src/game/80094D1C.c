extern void *(*D_800B8C88)(void *value);
extern void func_8009ED98(void *state, int value, int kind);

void func_80094D1C(void *value, int argument, int kind) {
    void *state = D_800B8C88(value);

    func_8009ED98(state, argument, kind);
}
