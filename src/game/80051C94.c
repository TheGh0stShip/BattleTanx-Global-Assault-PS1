typedef struct {
    short a0;
    short a2;
    short a4;
    char pad6[2];
    int a8;
    int aC;
    int a10;
    char pad14[0x20 - 0x14];
    unsigned char id;
    unsigned char a21;
    char pad22[2];
} Team;
typedef struct {
    char *models;
    unsigned int mode;
    unsigned char humans;
    unsigned char count;
    char padA;
    unsigned char team[46];
    unsigned char type[7];
} Setup;
typedef struct {
    unsigned char flags;
    unsigned char index;
    char pad2[2];
    Team *team;
    int a8;
    int aC;
    int value;
    int stats[7];
    char *model;
    unsigned char kind;
    char pad35[3];
    int mode;
    int a3C;
    int pair[2];
} Desc;
typedef struct {
    char data[0x114];
} Player;
typedef struct {
    char pad0[0x18];
    int pair[2];
    int a20;
} Profile;
extern Player D_800E3E68[];
extern Team D_800E3DB4[];
extern Setup D_800D2FE4;
extern int D_800A6070;
extern unsigned int D_800A6094[];
extern int D_800A60C4[];
extern int D_800B028C[][7];
extern void func_8008AA48(void *, int, int);
extern void func_8008A7BC(void *, void *, int);
extern Profile *func_80053338(int);
extern void func_800516B8(Player *, Desc *);

void func_80051C94(void) {
    Desc desc;
    int i;
    int j;
    int level;
    int flags;

    func_8008AA48(D_800E3E68, 0, 0x564);
    for (i = 0; i < D_800D2FE4.count; i++) {
        desc.flags = 0;
        if (i < D_800D2FE4.humans) {
            flags = 2;
            desc.flags = flags;
        }
        desc.model = D_800D2FE4.models + (D_800D2FE4.type[i] * 60 + 36);
        desc.index = i;
        desc.team = &D_800E3DB4[D_800D2FE4.team[i]];
        desc.aC = desc.a8 = 0;
        desc.value = D_800A60C4[i];
        desc.a3C = func_80053338(desc.value)->a20;
        func_8008A7BC(desc.pair, func_80053338(desc.value)->pair, 8);
        level = 0;
        switch (D_800A6094[i]) {
        case 1:
            level = 0;
            break;
        case 2:
            level = 1;
            break;
        case 3:
            level = 2;
            break;
        }
        if (desc.flags & 2) {
            level = 2 - level;
        }
        for (j = 0; j < 7; j++) {
            desc.stats[j] = D_800B028C[level][j];
        }
        desc.kind = 0;
        if (desc.flags & 2) {
            if (D_800A6070 == 10) {
                desc.mode = 8;
            } else {
                switch (D_800D2FE4.mode) {
                case 1:
                case 3:
                    desc.mode = 2;
                    break;
                case 5:
                    desc.mode = 5;
                    break;
                default:
                    desc.mode = 0;
                    break;
                }
            }
        } else {
            switch (D_800D2FE4.mode) {
            case 1:
            case 3:
                desc.mode = 1;
                break;
            case 5:
                desc.mode = 6;
                break;
            default:
                desc.mode = 8;
                break;
            }
        }
        func_800516B8(&D_800E3E68[i], &desc);
    }
}
