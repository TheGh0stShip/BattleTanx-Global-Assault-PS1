typedef struct TimerSource {
    int busy;
    int pad04;
    unsigned int start;
    unsigned int end;
    int enabled;
} TimerSource;

typedef struct TimerChannel {
    int device;
    int event;
    unsigned short pending;
    unsigned short rate;
} TimerChannel;

typedef struct TimerBlock {
    TimerSource source[4];
    TimerChannel channel[2];
    char pad068[8];
} TimerBlock;

extern TimerBlock D_800EDF08;
extern void func_8008AA48(void *, int, int);
extern void func_80094480(void (*)(void));
extern void func_8008359C(void);
extern void func_80094198(void);
extern void func_80094168(void);
extern void func_80091548(int);
extern void func_80091410(int, int, int);
extern void func_80091514(int);
extern int func_80094158(int, int, int, int (*)(void));
extern void func_800940B4(int);
extern int func_80083904(void);
extern int func_80083924(void);

void func_80083944(void) {
    func_8008AA48(&D_800EDF08, 0, sizeof(TimerBlock));
    func_80094480(func_8008359C);
    func_80094198();
    D_800EDF08.channel[0].device = 0xF2000001;
    D_800EDF08.channel[0].pending = 0;
    func_80091548(0xF2000001);
    func_80091410(0xF2000001, 0xFFFF, 0x1000);
    func_80091514(0xF2000001);
    D_800EDF08.channel[0].event = func_80094158(0xF2000001, 2, 0x1000, func_80083904);
    func_800940B4(D_800EDF08.channel[0].event);
    D_800EDF08.channel[1].device = 0xF2000002;
    D_800EDF08.channel[1].pending = 0;
    func_80091548(0xF2000002);
    func_80091410(0xF2000002, 0xFFFF, 0x1000);
    func_80091514(0xF2000002);
    D_800EDF08.channel[1].event = func_80094158(0xF2000002, 2, 0x1000, func_80083924);
    func_800940B4(D_800EDF08.channel[1].event);
    func_80094168();
}
