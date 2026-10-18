void func_80050AAC(unsigned char *object, unsigned char *destination) {
    unsigned char *state = object + 0x184;
    int value;

    if (*(int *)(state + 0x1C) != 0) {
        value = *(int *)(state + 0x20);
        *(int *)(destination + 0x04) = value;
        return;
    }
    value = *(int *)(state + 0x20);
    *(int *)(destination + 0x04) = -value;
}
