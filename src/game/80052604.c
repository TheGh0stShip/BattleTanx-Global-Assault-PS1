typedef struct {
    char pad0[0x14];
    unsigned char team;
} Player;
typedef struct {
    char pad0[0x18];
    void *slots[1];
} Roster;
typedef struct {
    char pad0[9];
    unsigned char count;
    char padA;
    unsigned char player_team[0x18 - 0xB];
    unsigned char team[8];
    void *slot_data[(0x39 - 0x20) / 4];
    char pad3C[0x39 - 0x3C + 4];
    unsigned char slot_index[7];
    Roster *roster;
} Game;
typedef struct {
    short a;
    short b;
    short c;
    short pad6;
    int d;
    int e;
    int f;
    char pad14[0x20 - 0x14];
    unsigned char id;
    unsigned char color;
    char pad22[2];
} Team;
extern Game D_800D2FE4;
extern Team D_800E3DB4[];
extern unsigned char D_800A5B38[];
extern void func_8008AC90(void *, int);
extern int func_80022814();
extern Player *func_80053338(void *);

static inline void init_team(Team *t, int id, unsigned char color) {
    t->id = id;
    t->a = 0;
    t->b = 0;
    t->c = 0;
    t->d = 0;
    t->e = 0;
    t->f = 0;
    t->color = color;
}

void func_80052604(void) {
    int i;

    func_8008AC90(D_800D2FE4.team, 5);
    if (func_80022814() != 0) {
        for (i = 0; i < D_800D2FE4.count; i++) {
            D_800D2FE4.team[i] = func_80053338(D_800D2FE4.roster->slots[D_800D2FE4.slot_index[i]])->team;
            D_800D2FE4.slot_data[i] = D_800D2FE4.roster->slots[D_800D2FE4.slot_index[i]];
        }
    } else {
        for (i = 0; i < 4; i++) {
            init_team(&D_800E3DB4[i], i, D_800A5B38[i]);
        }
        for (i = 0; i < D_800D2FE4.count; i++) {
            D_800D2FE4.team[i] = D_800E3DB4[D_800D2FE4.player_team[i]].color;
        }
    }
}
