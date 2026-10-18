typedef struct {
    char pad0[0xC];
    int score;
    char pad10[8];
    int kills;
} Player;

typedef struct {
    char pad0[0xC];
    Player *player;
    char pad10[0x114 - 0x10];
} Waypoint;

typedef struct {
    void *screen;
    int mode;
    unsigned char count;
} Globals;

typedef struct {
    int round;
    int score;
    int kills[4];
} Record;

typedef struct {
    char pad0[6];
    unsigned short buttons;
} Pad;

extern unsigned char D_800A4381;
extern Waypoint D_800E3E68[];
extern Globals D_800D2FE4;
extern Record D_800E53FC;
extern int D_800A66FC;
extern unsigned char D_800ABA5B;
extern unsigned int D_800A6074;
extern int D_800A6070;
extern Pad D_800EE028;
extern int D_800C60C8;
extern int D_800C60DC;
extern int D_800C60E4;
extern short D_800AACEA;
extern short D_800E4744;
extern unsigned char D_800E4740;
extern int D_800EC0F8[];
extern int *func_8006A7FC(void);
extern void func_8006A8B8(void);
extern void func_800611D4(int *);
extern void func_8006A290(void);
extern void func_8006AB60(int);
extern void func_80088870(int);
extern void func_80084898(int);
extern void func_800147E0(void);
extern void func_8007A0E8(unsigned char, int);

static inline Waypoint *waypoint_get(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_800203E0(void) {
    int result;
    int i;

    if (D_800A4381 == 0) {
        if (*func_8006A7FC() == 0) {
            int n;

            D_800E53FC.score = D_800E3E68[0].player->score;
            if (D_800E53FC.score % 5 != 0) {
                D_800E53FC.score = (D_800E53FC.score + 5) / 5 * 5;
            }
            for (n = 0; n < D_800D2FE4.count; n++) {
                D_800E53FC.kills[n] = waypoint_get(n)->player->kills;
            }
        }
        D_800E53FC.round++;
    } else {
        func_8006A8B8();
    }
    if (D_800E53FC.round == 57) {
        func_800611D4(&D_800A66FC);
        D_800ABA5B = 0;
        func_8006A290();
        switch (D_800A6074) {
        case 1:
            func_8006AB60(12);
            break;
        case 2:
            func_8006AB60(13);
            break;
        case 3:
            func_8006AB60(14);
            break;
        }
        do {
            func_80088870(0);
            func_80084898(20);
        } while (!(D_800EE028.buttons & 0x4000));
        func_800147E0();
        D_800C60C8 = 0;
        D_800C60DC = 2;
    } else {
        result = *func_8006A7FC();
        if (result == 0) {
            D_800A6070 = 1;
            D_800C60E4 = -1;
            D_800C60DC = 4;
            D_800AACEA = 0;
            D_800E4744 = 260;
            D_800E4740 = 0;
        } else if (result == 1) {
            D_800A6070 = 10;
            D_800C60E4 = -1;
            D_800C60DC = 3;
        } else if (result == 2) {
            D_800A6070 = 10;
            D_800C60E4 = -1;
            D_800C60DC = 3;
        } else if (result == 3) {
            D_800A6070 = 1;
            D_800C60E4 = -1;
            D_800C60DC = 4;
            D_800AACEA = 0;
            D_800E4744 = 260;
            D_800E4740 = 0;
        }
    }
    for (i = 0; i < 2; i++) {
        func_8007A0E8(i, D_800EC0F8[i]);
    }
}
