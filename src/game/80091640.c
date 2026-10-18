extern unsigned char D_800EEE3C[];

int func_80091604(int value);

void func_80091640(void) {
    register unsigned char *state asm("$2");

    func_80091604(0);
    state = D_800EEE3C;
    asm("" : "+r"(state));
    asm("sb $0,5($2)" : : "r"(state) : "memory");
}
