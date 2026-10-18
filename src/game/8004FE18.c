void func_8004E2AC(unsigned char *object, int value);

void func_8004FE18(unsigned char *object) {
    int *state = (int *)(object + 0x184);
    int flags = state[0];

    if ((flags & 1) != 0) {
        if (*(int *)(object + 0xAC) != 0) {
            goto activate;
        }
    }
    if ((flags & 2) == 0) {
        return;
    }
    if (*(int *)(object + 0x210) >= *(int *)(object + 0x20C)) {
        return;
    }

activate:
    state[0] = 0;
    func_8004E2AC(object, state[1]);
}
