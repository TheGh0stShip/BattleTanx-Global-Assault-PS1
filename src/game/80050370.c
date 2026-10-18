void func_8004D804(unsigned char *object);

void func_80050370(unsigned char *object, int first, int second, int *source) {
    int *state = (int *)(object + 0x184);

    state[0] = 1;
    state[1] = first;
    state[2] = second;
    state[3] = source[0];
    state[5] = source[2];
    func_8004D804(object);
}
