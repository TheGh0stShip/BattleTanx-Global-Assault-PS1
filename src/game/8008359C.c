typedef struct VideoInfo {
    int unk00;
    int rate;
} VideoInfo;

typedef struct Timer {
    char pad00[0x28];
    int paused;
    int ticks;
    int pad30;
    int ch2_ready;
    int ch2_enabled;
    int stopped;
    int frames;
    int pad44;
    int ch3_ready;
    int ch3_enabled;
    char pad50[0x18];
    int phase;
    void (*on_tick)(int, int);
} Timer;

extern Timer D_800EDF08;
extern VideoInfo D_80086058;
extern void func_80083540(int, int);

void func_8008359C(void) {
    int step = 0;

    if (D_800EDF08.paused == 0) {
        step = 20;
        if (D_80086058.rate != 50) {
            step = 17;
            if (D_800EDF08.phase >= 2) {
                step = 16;
                D_800EDF08.phase = 0;
            } else {
                D_800EDF08.phase++;
            }
        }
        D_800EDF08.ticks += step;
    }
    if (D_800EDF08.stopped == 0) {
        D_800EDF08.frames++;
    }
    if (D_800EDF08.paused == 0 && D_800EDF08.ch2_enabled != 0 && D_800EDF08.ch2_ready != 0) {
        func_80083540(2, step);
    }
    if (D_800EDF08.stopped == 0 && D_800EDF08.ch3_enabled != 0 && D_800EDF08.ch3_ready != 0) {
        func_80083540(3, 1);
    }
    if (D_800EDF08.on_tick != 0) {
        D_800EDF08.on_tick(D_800EDF08.frames, step);
    }
}
