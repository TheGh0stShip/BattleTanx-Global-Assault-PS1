extern void (*D_800EEE4C)(unsigned int value);

void func_800915D8(unsigned int value) {
    if (D_800EEE4C != 0) {
        D_800EEE4C((unsigned char)value);
    }
}
