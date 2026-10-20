typedef struct TimerSource {
    int busy;
    unsigned int counter;
    unsigned int current;
    unsigned int limit;
    void (*callback)(void *);
} TimerSource;

typedef struct TimerChannel {
    int device;
    int field04;
    unsigned short pending;
    unsigned short rate;
} TimerChannel;

typedef struct TimerBlock {
    TimerSource source[4];
    TimerChannel channel[4];
} TimerBlock;

typedef char TimerSource_size[(sizeof(TimerSource) == 20) ? 1 : -1];
typedef char TimerChannel_size[(sizeof(TimerChannel) == 12) ? 1 : -1];

extern TimerBlock D_800EDF08;
extern int func_80094AE8(void);
extern int func_80094AFC(int);
extern void func_80083540(unsigned int, unsigned int);
extern void func_800836E8(int);

void func_80083854(int channel) {
    int previous = func_80094AE8();
    unsigned int rate = D_800EDF08.channel[channel].rate;

    D_800EDF08.source[channel].counter += rate;
    if (D_800EDF08.source[channel].busy == 0 &&
        D_800EDF08.source[channel].callback != 0 &&
        D_800EDF08.source[channel].limit != 0)
        func_80083540(channel, rate);
    func_800836E8(channel);
    func_80094AFC(previous);
}
