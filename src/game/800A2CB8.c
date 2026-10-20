typedef struct SoundTransfer {
    int unused0;
    unsigned int flags;
    unsigned char unused8[28];
    unsigned int timestamp;
} SoundTransfer;

typedef struct VideoConfig {
    int unused0;
    int rate;
} VideoConfig;

extern VideoConfig D_80086058;
extern unsigned int func_80088870(int source);
extern void func_8008F824(void);
extern unsigned int func_8008F978(void);
extern void func_800A2DFC(unsigned int ticks);

int func_800A2CB8(SoundTransfer *transfer, int repeat) {
    register SoundTransfer *saved_transfer asm("$17") = transfer;
    register int saved_repeat asm("$21") = repeat;
    register int clear_wait asm("$19") = -0x1001;
    VideoConfig *config = &D_80086058;
    register unsigned int ready asm("$18");
    register unsigned int now asm("$16");
    register unsigned int current_flags asm("$2");
    unsigned int delay;

    asm("" : "+r"(saved_transfer), "+r"(saved_repeat),
              "+r"(clear_wait));
    do {
        current_flags = saved_transfer->flags;
        asm("" : "+r"(current_flags));
        ready = current_flags ^ 1U;
        ready &= 1U;
        if (ready == 0 && (func_8008F978() & 4U) != 0) {
            func_8008F824();
            now = func_80088870(1);
            if ((saved_transfer->flags & 0x1000U) == 0) {
                delay = 0x147;
                if (config->rate == 0x3C) {
                    delay = 0x189;
                }
                if (now - saved_transfer->timestamp >= delay) {
                    func_800A2DFC(0x19);
                    saved_transfer->timestamp = now;
                    saved_transfer->flags &= clear_wait;
                }
            } else {
                saved_transfer->timestamp = now;
                saved_transfer->flags &= clear_wait;
            }
            func_8008F824();
        } else {
            saved_transfer->timestamp = 0;
        }
    } while (ready == 0 && saved_repeat != 0);
    return ready;
}
