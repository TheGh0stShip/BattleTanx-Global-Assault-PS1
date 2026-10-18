extern void func_800A1AB0(void *state);
extern void func_800A2914(unsigned char *value, int first, int second);
extern unsigned char D_800EFE0F;

void func_800A1AF8(unsigned int *state, unsigned int value) {
    state[2] = value;
    func_800A1AB0(state);
    func_800A2914(&D_800EFE0F, 1, 0);
}
