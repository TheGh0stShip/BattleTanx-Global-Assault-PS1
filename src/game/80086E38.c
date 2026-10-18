extern unsigned char D_800EE676;

int func_80086E38(int value) {
    value = (unsigned char)value;
    if (value < 20) {
        if (value >= 17) {
            return D_800EE676 * 128 - 1920;
        }
    }
    return 128;
}
