int func_8004778C(unsigned short value, unsigned int mask, int mode);
void func_8004E2AC(unsigned char *state, unsigned int value);

void func_80050584(unsigned char *state) {
    unsigned char *entry = state + 0x184;

    if (func_8004778C(*(unsigned short *)(state + 0x2B8),
                      0x002C7007, 0) == 0) {
        func_8004E2AC(state, *(unsigned int *)(entry + 0x24));
    }
}
