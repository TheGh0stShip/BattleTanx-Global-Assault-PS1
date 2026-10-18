extern void func_8009F79C(void *state);
extern void func_8009F7AC(void *state, int value, int mode);

void func_8009F6BC(void *state) {
    func_8009F79C(state);
    func_8009F7AC(state, 0x3F, 0);
}
