typedef struct {
    char pad0[4];
    int mode;
    int map;
    unsigned char players;
    unsigned char slots[16];
    char padD;
    char pad1E[0x50 - 0x1E];
    int timer;
} Level;

typedef struct {
    void *screen;
    int mode;
    volatile unsigned char players;
    unsigned char total;
    unsigned char teams;
    unsigned char slot_kind[5];
    char pad10[0x10 - 0x10];
    int timer;
    int timer2;
    char pad18[0x34 - 0x18];
    unsigned char rank[5];
    unsigned char order[5];
    char pad3E[2];
    Level *level;
    int map;
    unsigned char streak;
    unsigned char won;
    char pad4A[2];
    unsigned char active;
} Globals;

extern Globals D_800D2FE4;
extern unsigned char D_800D302D;
extern unsigned char D_800D3030;
extern int D_800D2FF4;
extern int D_800ADED8;
extern unsigned char D_800AED4F;
extern short D_800A570C;
extern int D_800AAF38;
extern int D_800AAF3C;
extern int D_800AAF40;
extern Level *func_8006A7FC(void);
extern void func_8003C8D4(void);
extern void func_80048124(void);
extern void func_80051F54(void);
extern void func_8004842C(void);
extern void func_800335C0(void);
extern void func_80033690(void);
extern void func_80034DEC(void);

void func_800206B0(void) {
    Level *level;
    int i;
    int j;

    D_800ADED8 = 0;
    if (D_800D2FE4.won != 0) {
        if (D_800D2FE4.streak < 100) {
            D_800D2FE4.streak++;
        }
    } else {
        D_800D2FE4.streak = 0;
    }
    D_800D302D = 0;
    if (D_800AED4F & 1) {
        D_800A570C = 5;
    } else {
        D_800A570C = 20;
    }
    level = func_8006A7FC();
    D_800D2FE4.level = level;
    D_800D2FE4.mode = level->map;
    D_800D2FE4.timer = level->timer;
    D_800D2FE4.map = level->mode;
    D_800D2FE4.total = D_800D2FE4.players + level->players;
    D_800D2FE4.teams = 4;
    if (D_800D2FE4.players == 1) {
        D_800D2FE4.order[0] = 0;
        D_800D2FE4.order[1] = 2;
        D_800D2FE4.order[2] = 3;
        D_800D2FE4.order[3] = 4;
        D_800D2FE4.order[4] = 1;
    } else {
        D_800D2FE4.order[0] = 0;
        D_800D2FE4.order[1] = 1;
        D_800D2FE4.order[2] = 2;
        D_800D2FE4.order[3] = 3;
        D_800D2FE4.order[4] = 4;
    }
    for (j = 0; j < 5; j++) {
        D_800D2FE4.rank[D_800D2FE4.order[j]] = j;
    }
    for (i = 0; i < 5; i++) {
        D_800D2FE4.slot_kind[i] = D_800D2FE4.level->slots[D_800D2FE4.order[i]];
    }
    if (D_800D2FE4.mode == 12) {
        D_800D2FE4.timer = 0;
        D_800D2FE4.timer2 = 0;
    }
    D_800D3030 = 1;
    func_8003C8D4();
    func_80048124();
    func_80051F54();
    func_8004842C();
    switch (D_800D2FE4.mode) {
    case 11:
        func_800335C0();
    case 14:
        D_800AAF40 = 0;
        func_80033690();
        D_800AAF38 = D_800D2FF4;
        D_800AAF3C = D_800D2FF4;
        break;
    case 7:
        func_80033690();
        D_800AAF38 = 0;
        D_800AAF3C = 0;
        break;
    case 13:
        func_80033690();
    case 12:
        D_800AAF3C = 0;
        D_800AAF38 = D_800D2FF4;
        break;
    default:
        D_800AAF38 = 0;
        D_800AAF3C = 0;
        break;
    }
    func_80034DEC();
}
