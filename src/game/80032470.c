struct TimedEffect {
    unsigned char pad_00[8];
    unsigned char position[12];
    unsigned short effect;
    unsigned char pad_16[2];
    unsigned short timer;
    unsigned char pad_1A[6];
    void *owner;
};

void func_80035948(
    void *owner,
    unsigned char *position,
    unsigned int effect,
    int arg3,
    int arg4,
    int arg5,
    int arg6,
    int arg7
);

void func_80032470(struct TimedEffect *state, unsigned int elapsed) {
    if ((short)state->timer > 0) {
        state->timer -= elapsed;
        if ((short)state->timer <= 0) {
            func_80035948(
                state->owner,
                state->position,
                state->effect,
                0,
                0,
                0,
                0,
                0
            );
        }
    }
}
