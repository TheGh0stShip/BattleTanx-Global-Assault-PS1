typedef struct {
    unsigned short score;
    char pad2[0x20 - 2];
    unsigned char team;
} Player;

typedef struct {
    char pad0[0xC];
    Player *player;
    char pad10[0x58 - 0x10];
    int result;
    char pad5C[0x114 - 0x5C];
} Waypoint;

typedef struct {
    void *screen;
    int mode;
    char pad8;
    unsigned char count;
    char padA[6];
    int target;
} Globals;

extern Globals D_800D2FE4;
extern Waypoint D_800E3E68[];
extern void func_8008AA48(void *, int, int);
extern void func_80052DB4(Waypoint *);

static inline Waypoint *waypoint_get(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_800219AC(void) {
    unsigned char alive[5];
    Waypoint *w;
    int i;

    if (D_800D2FE4.mode == 0 || D_800D2FE4.mode == 6) {
        for (i = 0; i < D_800D2FE4.count; i++) {
            w = waypoint_get(i);
            if (w->player->score >= D_800D2FE4.target) {
                w->result = 1;
            } else {
                w->result = 2;
            }
        }
    } else {
        func_8008AA48(alive, 0, 5);
        for (i = 0; i < D_800D2FE4.count; i++) {
            w = waypoint_get(i);
            func_80052DB4(w);
            if (w->result != 2) {
                alive[w->player->team] = 1;
            }
        }
        for (i = 0; i < D_800D2FE4.count; i++) {
            w = waypoint_get(i);
            if (alive[w->player->team]) {
                w->result = 1;
            } else {
                w->result = 2;
            }
        }
    }
}
