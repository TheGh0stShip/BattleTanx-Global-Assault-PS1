extern unsigned char D_800EFE11;

unsigned char func_800A195C(void);
void func_800A19E4(int value);

void func_800A1C3C(unsigned char *state) {
    if (D_800EFE11 == 1) {
        state[0x31] = func_800A195C();
        (*(unsigned int *)(state + 0x28))++;
    }
    func_800A19E4(1);
}
