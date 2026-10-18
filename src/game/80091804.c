extern unsigned char D_800EEE3C[];

int func_8009B04C(int value);

int func_80091804(void) {
    register unsigned char *state asm("$2") = D_800EEE3C;
    int result = 0;

    asm("" : "+r"(state));
    if (state[4] != 0) {
        result = func_8009B04C(1) == 2;
    }
    return result;
}
