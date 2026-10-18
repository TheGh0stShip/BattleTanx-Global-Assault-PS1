typedef struct Waypoint {
    char pad000[6];
    unsigned char flags;
    char pad007[0x58 - 7];
    int state;
    char pad05C[0x114 - 0x5C];
} Waypoint;
typedef struct Game {
    char pad0[9];
    unsigned char count;
} Game;
extern Waypoint D_800E3E68[];
extern Game D_800D2FE4;

static inline Waypoint *waypoint(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_80022840(void) {
    int i;

    for (i = 0; i < D_800D2FE4.count; i++) {
        Waypoint *w = waypoint(i);
        if (w->flags & 2) {
            w->state = 1;
        }
    }
}
