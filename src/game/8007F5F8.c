extern unsigned char D_800EC204[];

void func_8008DA04(void *state, void *input);
int func_80090184(void *input);

void func_8007F5F8(void *input) {
    func_8008DA04(D_800EC204, input);
    *(int *)(D_800EC204 + 0x80) = func_80090184(input);
}
