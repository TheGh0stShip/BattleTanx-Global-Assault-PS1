typedef struct {
    char pad0[0xA4];
    unsigned char team;
    char pad1[0x114 - 0xA5];
} Waypoint;

typedef struct {
    char pad0[8];
    int pos[3];
    unsigned short angle;
    char pad16[0x1D - 0x16];
    unsigned char owner;
} Effect;

extern Waypoint D_800E3E68[];
extern int D_800D2F4C;
extern void func_80069494(int, int *, int, int, int, int);

static inline Waypoint *waypoint_get(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_80029A68(Effect *e) {
    Waypoint *w = waypoint_get(e->owner);

    func_80069494(D_800D2F4C, e->pos, 0, e->angle, 0, w->team);
}
