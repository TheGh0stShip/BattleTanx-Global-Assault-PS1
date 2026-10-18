void func_8002B624(int *state, int unused, int mode) {
    if (mode != 0) {
        if (mode == 3) {
            if (state[3] <= 0x27FFF) {
                state[9] = -9000;
            }
        }
    }
}
