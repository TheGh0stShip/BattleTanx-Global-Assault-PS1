int func_80094D6C(unsigned int *state, unsigned int second, unsigned int third, unsigned int enabled) {
    state[0] = enabled != 0;
    state[6] = -1;
    state[1] = 0;
    state[2] = second;
    state[3] = third;
    state[4] = 0;
    state[5] = 0;
    state[7] = 0;
    return 1;
}
