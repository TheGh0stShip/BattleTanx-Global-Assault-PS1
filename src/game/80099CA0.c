typedef void (*Callback)(int operation, void *value, unsigned int active);

void func_80099CA0(unsigned int *state, int enabled) {
    if (enabled != 0 && state[1] != 0) {
        Callback callback = (Callback)state[4];

        callback(2, (void *)state[5], state[1]);
        state[1] = 0;
    }
}
