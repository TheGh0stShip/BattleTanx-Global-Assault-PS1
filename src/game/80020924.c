typedef struct {
    void *screen;
    int mode;
    unsigned char players;
    unsigned char total;
    unsigned char teams;
    unsigned char slot_kind[5];
    int timer;
    int timer2;
    char pad18[8];
    int slot_id[5];
    unsigned char rank[5];
    unsigned char order[5];
    char pad3E[2];
    void *level;
    int map;
    unsigned char streak;
    unsigned char won;
    char pad4A[2];
    unsigned char active;
} Globals;

extern Globals D_800D2FE4;
extern unsigned char D_800D3030;
extern int D_800ADED8;
extern int D_800EC0F8[];
extern unsigned int D_800A6070;
extern unsigned int D_800A6084[];
extern unsigned int D_800A60A4[];
extern int D_800A60C4[];
extern int D_800D2FE0;
extern int D_800AAF38;
extern int D_800AAF3C;
extern void func_8007A0E8(unsigned char, int);
extern unsigned int func_80086C84(void);
extern void func_80052604(void);
extern void func_8003C8D4(void);
extern void func_80048124(void);
extern void func_80051C94(void);
extern void func_8004842C(void);
extern void func_800335C0(void);
extern void func_80033690(void);
extern void func_80032C18(void);

void func_80020924(void) {
    int i;
    int j;
    int kind;
    unsigned char t;

    D_800D2FE4.streak = 0;
    D_800D2FE4.won = 0;
    D_800ADED8 = 0;
    for (i = 0; i < 2; i++) {
        func_8007A0E8(i, D_800EC0F8[i]);
    }
    switch (D_800A6070) {
    case 7:
        D_800D2FE4.mode = 6;
        break;
    case 8:
        D_800D2FE4.mode = 5;
        break;
    case 3:
        D_800D2FE4.mode = 0;
        break;
    case 5:
        D_800D2FE4.mode = 2;
        break;
    case 4:
        D_800D2FE4.mode = 1;
        break;
    case 6:
        D_800D2FE4.mode = 3;
        break;
    }
    D_800D2FE4.total = 0;
    D_800D2FE4.teams = 4;
    D_800D2FE4.slot_kind[0] = 0;
    D_800D2FE4.slot_kind[1] = 0;
    D_800D2FE4.slot_kind[2] = 0;
    D_800D2FE4.slot_kind[3] = 0;
    for (i = 0; i < 4; i++) {
        if (D_800A6084[i] != 0 && (kind = 0, D_800A60A4[i] < 3)) {
            if (D_800A60A4[i] != 0) {
                switch (D_800A6084[i]) {
                case 1:
                    kind = 1;
                    break;
                case 2:
                    kind = 2;
                    break;
                case 3:
                    kind = 3;
                    break;
                }
                D_800D2FE4.slot_kind[D_800D2FE4.total] = kind;
                D_800D2FE4.slot_id[D_800D2FE4.total] = D_800A60C4[i];
                D_800D2FE4.total++;
            }
        }
    }
    for (i = 0; i < 5; i++) {
        D_800D2FE4.rank[i] = i;
        D_800D2FE4.order[i] = i;
    }
    for (i = 0; i < 4; i++) {
        j = (func_80086C84() >> 16) & 3;
        if (i != j) {
            t = D_800D2FE4.order[i];
            D_800D2FE4.order[i] = D_800D2FE4.order[j];
            D_800D2FE4.order[j] = t;
        }
    }
    for (i = 0; i < 4; i++) {
        D_800D2FE4.rank[D_800D2FE4.order[i]] = i;
    }
    func_80052604();
    D_800D3030 = 1;
    func_8003C8D4();
    func_80048124();
    func_80051C94();
    func_8004842C();
    switch (D_800A6070) {
    case 7:
        D_800D2FE4.timer = 5;
        for (i = 0; i < D_800D2FE4.players; i++) {
            func_8007A0E8(i, 2);
        }
        break;
    case 3:
        D_800D2FE4.timer = 5;
        break;
    case 8:
        D_800D2FE4.timer = D_800D2FE0 + 10800;
        break;
    case 5:
        D_800D2FE4.timer = 10;
        break;
    default:
        D_800D2FE4.timer = 0;
        break;
    }
    switch (D_800D2FE4.mode) {
    case 1:
        func_800335C0();
        func_80033690();
        D_800AAF38 = D_800D2FE4.timer;
        D_800AAF3C = D_800D2FE4.timer;
        break;
    case 3:
        func_80033690();
        D_800AAF38 = 1;
        D_800AAF3C = 1;
        D_800D2FE4.timer = 1200;
        break;
    case 2:
        func_80032C18();
    case 0:
    case 6:
        D_800AAF3C = 0;
        D_800AAF38 = D_800D2FE4.timer;
        break;
    default:
        D_800AAF38 = 0;
        D_800AAF3C = 0;
        break;
    }
}
