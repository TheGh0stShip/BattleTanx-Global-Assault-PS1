typedef struct SoundInitState {
    int source;
    int argument;
    unsigned char unused8[4];
    unsigned int flags;
    int sector_size;
    unsigned char unused14[8];
    int timestamp;
    unsigned char unused20[4];
    int handle24;
    int handle28;
    int handle2C;
    unsigned int mode_flags;
} SoundInitState;

extern SoundInitState D_800B90BC;
extern int func_80088870(int source);
extern int func_8009701C(void);
extern int func_80097114(int channel, int argument);
extern int func_80097128(int channel);
extern void func_800973AC(int command, int first, int second);
extern int func_80097558(int channel);
extern int func_800A1520(int mode);

int func_800A1710(int source, int argument, unsigned int flags) {
    SoundInitState *state = &D_800B90BC;
    unsigned int mode;

    state->flags = flags;
    mode = state->flags & 0x30;
    if (mode == 0) {
        state->sector_size = 0x200;
    } else if (mode == 0x20) {
        state->sector_size = 0x249;
    } else {
        state->sector_size = 0x246;
    }
    state->flags |= 0x20;
    state->argument = argument;
    state->source = source;
    state->handle24 = func_80097114(0, argument);
    state->handle28 = func_80097128(0);
    if ((state->mode_flags & 1) != 0) {
        state->handle2C = func_80097558(0);
    }
    state->timestamp = func_80088870(-1);
    if ((func_8009701C() & 0xE0) != 0) {
        func_800973AC(9, 0, 0);
    }
    return func_800A1520(0) > 0;
}
