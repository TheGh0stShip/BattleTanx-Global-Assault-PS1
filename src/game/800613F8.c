int func_800613F8(void *unused, unsigned char *object) {
    int *state = *(int **)(object + 0x10);
    int value = state[1];

    if (value < 0x5000) {
        state[1] = value + 0x1000;
        asm("");
        return 0;
    }
    state[1] = 0;
    return 1;
}
