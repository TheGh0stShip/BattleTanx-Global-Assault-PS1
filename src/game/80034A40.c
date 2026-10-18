typedef struct { char pad[24]; int a; int b; } Profile;
typedef struct {
    char pad[6];
    unsigned char flags;
    unsigned char team;
    char pad2[84 - 8];
    int profile;
    char pad3[176 - 88];
    int group;
    char pad4[188 - 180];
    unsigned char active;
    char rest[0x114 - 189];
} Waypoint;
typedef struct {
    int x;
    int y;
    int z;
    unsigned short angle;
    unsigned char team;
    char pad;
    int slot;
    int one;
    int kind;
    int group;
    int flags;
    int a;
    int b;
    void *owner;
} SpawnRequest;
typedef struct {
    int pad[2];
    int x;
    int z;
    unsigned short angle;
    unsigned char waypoint;
    char pad1;
    unsigned short remaining;
    unsigned char slot;
    char pad2;
    unsigned short slots;
    short pad3;
    int last_time;
    int interval;
    unsigned char mode;
    unsigned char kind;
    unsigned char max_alive;
    unsigned char alive;
    char pad4[8];
    int arg48;
} Spawner;
extern int D_800D2FE0;
extern Waypoint D_800E3E68[];
unsigned int func_80086C84(void);
int func_80052E54(Waypoint *);
int func_8004305C(int, int, int, int, int, int, int);
Profile *func_80053338(int);
int func_8003EEF8(SpawnRequest *);

static inline Waypoint *waypoint_at(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

static inline int has_flag(Waypoint *wp, int flag) {
    return wp->flags & flag;
}

static inline int gate_closed(Spawner *s, Waypoint *wp) {
    int closed = 0;

    if (s->mode == 4) {
        closed = !has_flag(wp, 4);
    }
    return closed;
}

void func_80034A40(Spawner *s, int *done) {
    Waypoint *wp;
    int slot;
    SpawnRequest req;

    wp = waypoint_at(s->waypoint);
    if (s->remaining == 0 && s->alive == 0) {
        *done = 1;
        wp->active--;
        return;
    }
    if (s->alive >= s->max_alive || s->remaining == 0) {
        return;
    }
    if ((func_80086C84() & 0xF) != 0 && s->mode != 2 && s->mode != 3) {
        return;
    }
    if (D_800D2FE0 < s->last_time + s->interval) {
        return;
    }
    if (func_80052E54(wp) == 0) {
        return;
    }
    if (gate_closed(s, wp)) {
        return;
    }
    do {
        if (++s->slot == 15) {
            s->slot = 0;
        }
    } while (((s->slots >> (slot = s->slot)) & 1) == 0);
    if (func_8004305C(slot, s->x, s->z, s->angle, 1, 0, s->arg48) == 0) {
        return;
    }
    req.one = 1;
    req.slot = slot;
    req.kind = s->kind;
    req.group = wp->group;
    req.angle = s->angle;
    req.x = s->x;
    req.y = 0;
    req.z = s->z;
    req.flags = (s->mode == 3) << 6;
    req.team = wp->team;
    req.a = func_80053338(wp->profile)->a;
    req.b = func_80053338(wp->profile)->b;
    req.owner = s;
    if (func_8003EEF8(&req) != 0) {
        s->last_time = D_800D2FE0;
        s->alive++;
        if (s->remaining != 0xFFFF) {
            s->remaining--;
        }
    }
}
