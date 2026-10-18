int func_800569EC(unsigned short *state) {
    short timer = state[1] - 1;
    state[1] = timer;
    if (timer <= 0) {
        unsigned short frame = state[2];
        state[1] = timer + state[0];
        state[2] = frame + 1;
        if ((unsigned short)(frame + 1) >= state[3]) {
            state[2] = frame;
            return 1;
        }
    }
    return 0;
}
