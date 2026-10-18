typedef struct { int x, y, z; } Vector;
typedef struct { int pad[2]; int progress; } Counter;
typedef struct { char pad[12]; Counter *counter; char rest[0x114 - 16]; } Waypoint;
typedef struct { int pad; unsigned int mode; unsigned char teams; char pad2[7]; int goal; } Rules;
typedef struct {
    int pad[2];
    int carrier;
    int active;
    int pad2;
    int base;
    int pad3[2];
    Vector pos;
    int last_time;
    unsigned char waypoint;
    unsigned char pad4;
    unsigned short cell;
} Flag;
extern Rules D_800D2FE4;
extern unsigned int D_800D2FE8;
extern int D_800D2FE0;
extern int D_800DE30C;
extern Waypoint D_800E3E68[];
void func_8001B094(int);
short func_800162F0(Flag *, int, int, int, int, int, int, int, int, int, int, int);
void func_800531D4(Waypoint *, int);
void func_800324C8(Flag *, int);

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

static inline int to_int_inplace(int v) {
    if (v >= 0) {
        v >>= 12;
    } else {
        v = -(-v >> 12);
    }
    return v;
}

static inline short quarter(int v) {
    return (to_int(v) << 14) >> 16;
}

static inline Waypoint *waypoint_at(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_800326E4(Flag *f, int *done) {
    int prev;
    int cur;
    Counter *c;
    int i;

    if (f->active == 3) {
        *done = 1;
        if (f->cell != 0xFFFF) {
            func_8001B094(f->cell);
        }
        return;
    }
    if (f->active != 2 && f->cell == 0xFFFF) {
        f->cell = func_800162F0(f, quarter(f->pos.x), quarter(f->pos.z), quarter(f->pos.y), -60, 60, -60, 60, -60, 60, 0,
                                0x20000);
    }
    if (D_800D2FE8 == 3 && f->active == 0) {
        prev = to_int_inplace(waypoint_at(f->waypoint)->counter->progress);
        c = waypoint_at(f->waypoint)->counter;
        c->progress += D_800DE30C;
        cur = to_int(c->progress);
        if (D_800D2FE4.goal - cur < 300 && D_800D2FE4.goal - prev >= 300) {
            for (i = 0; i < D_800D2FE4.teams; i++) {
                func_800531D4(waypoint_at(i), 3);
            }
        } else if (D_800D2FE4.goal - cur < 900 && D_800D2FE4.goal - prev >= 900) {
            for (i = 0; i < D_800D2FE4.teams; i++) {
                func_800531D4(waypoint_at(i), 2);
            }
        }
    }
    if (f->carrier == 0 && f->active == 1 && D_800D2FE0 - f->last_time > 120) {
        func_800324C8(f, f->base);
    }
}
