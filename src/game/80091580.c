extern void (*D_800EEE44)(unsigned int value);

void func_80091580(unsigned int value) {
    if (D_800EEE44 != 0) {
        D_800EEE44((unsigned char)value);
    }
}
