typedef struct {
    char pad0[0x58];
    int state;
    char pad5C[0x114 - 0x5C];
} Waypoint;

typedef struct {
    char pad0[0xC];
    int level;
} Player;

extern Waypoint D_800E3E68[];
extern Player *D_800E3E74;
extern unsigned char D_800D2FEC;
extern int D_800D2FE8;
extern int D_800D3028;
extern int D_800AE784;
extern int D_800AE788;
extern int D_800AE78C;
extern int D_800AE790[];
extern void func_80063018(int, int, int);

static inline Waypoint *waypoint_get(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

static inline int any_waypoint_active(void) {
    int i;

    for (i = 0; i < D_800D2FEC; i++) {
        if (waypoint_get(i)->state == 1) {
            return 1;
        }
    }
    return 0;
}

void func_80021B98(void) {
    int music;

    if (any_waypoint_active()) {
        func_80063018(0, D_800AE790[D_800D3028], 1000);
        return;
    }
    if (D_800E3E74->level >= 5) {
        switch (D_800D2FE8) {
        case 10:
            func_80063018(0, D_800AE788, 1000);
            return;
        case 11:
            func_80063018(0, D_800AE78C, 1000);
            return;
        }
    }
    func_80063018(0, D_800AE784, 1000);
}
