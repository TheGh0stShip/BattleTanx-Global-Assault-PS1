typedef struct TimerSource {
    int busy;
    int pad04;
    unsigned int start;
    unsigned int end;
    int enabled;
} TimerSource;

typedef struct TimerChannel {
    int device;
    int pad04;
    unsigned short pending;
    unsigned short rate;
} TimerChannel;

typedef struct TimerBlock {
    TimerSource source[4];
    TimerChannel channel[4];
} TimerBlock;

extern TimerBlock D_800EDF08;
extern void func_80091514(int);
extern void func_80091410(int, int, int);
extern void func_80091548(int);
extern void func_800914E4(int);

void func_800836E8(int ch) {
    int device = D_800EDF08.channel[ch].device;
    unsigned short rate;
    unsigned int span;

    if (D_800EDF08.source[ch].busy != 0
        || (D_800EDF08.source[ch].enabled == 0 && D_800EDF08.channel[ch].pending == 0)) {
        if (D_800EDF08.channel[ch].rate != 0) {
            func_80091514(device);
            D_800EDF08.channel[ch].rate = 0;
        }
        func_80091410(device, 0xFFFF, 0x1000);
        func_80091548(device);
    } else {
        rate = 0xFFFF;
        if (D_800EDF08.source[ch].enabled != 0 && D_800EDF08.source[ch].end != 0) {
            span = D_800EDF08.source[ch].end - D_800EDF08.source[ch].start;
            if (span <= 0xFFFF || (span >>= 1) <= 0xFFFF) {
                rate = span;
            }
        }
        if (D_800EDF08.channel[ch].rate != rate) {
            func_80091410(device, rate, 0x1000);
            func_80091548(device);
            func_800914E4(device);
            D_800EDF08.channel[ch].rate = rate;
        }
    }
}
