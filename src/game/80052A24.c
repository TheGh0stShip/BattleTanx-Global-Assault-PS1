extern void func_800149B8(void *value, int setting, int extra);

void func_80052A24(unsigned char *object, int setting) {
    register unsigned char *state asm("$16") = object;

    asm("" : "+r"(state));
    *(int *)(state + 0x60) = setting;
    if (state[0x64] != 0) {
        func_800149B8(*(void **)(state + 0x5C), setting, 0);
    }
}
