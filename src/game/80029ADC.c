void func_80029ADC(unsigned char *object, void *value) {
    if (*(short *)(object + 0) != 0 && *(short *)(object + 4) == 0x11 &&
        *(void **)(object + 0x3C) == value) {
        *(int *)(object + 0x38) = 0;
    }
}
