typedef struct { void *obj; int pad[8]; } Hit;
typedef struct { char pad[88]; int state; char rest[0x114 - 92]; } Waypoint;
typedef struct {
    short pad[3];
    unsigned short cell;
    int x;
    int y;
    int z;
    unsigned short angle;
    unsigned char team;
    char pad1;
    short hp;
    short pad2[13];
    int speed;
    int max_speed;
    int last_time;
} Gate;
extern short D_800C628C;
extern unsigned char D_800D5A98[];
extern Waypoint D_800E3E68[];
extern int D_800D2FE0;
extern int D_800DE30C;
int func_80017AAC(int, int, Hit *, int, int);
void func_80032470(Gate *, int);
void func_8001B094(int);
int func_80031928(Gate *, int);
int func_8008AD60(int);
int func_8008ACC0(int);
void func_80015F64(int, int, int);
void func_80031830(Gate *);
void func_80061CC0(int, int, int, int, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
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

static inline unsigned short query_cell(unsigned short cell, int mask, Hit *hits, int a, int b) {
    D_800C628C = 0;
    return func_80017AAC(cell, mask, hits, a, b);
}

void func_80031BC4(Gate *gate, int *done) {
    Gate *g = gate;

    Hit hits[8];
    int step;

    if (query_cell(g->cell, 0x200000, hits, 0, 1) != 0) {
        func_80032470(g, 10000);
    }
    if (g->hp <= 0) {
        func_8001B094(g->cell);
        *done = 1;
        D_800D5A98[g->team]--;
        if (D_800D5A98[g->team] == 0) {
            waypoint_at(g->team)->state = 2;
        }
        return;
    }
    if (g->speed == 0) {
        if (D_800D2FE0 - g->last_time > 90) {
            if (func_80031928(g, 0x32000) != 0) {
                g->speed = 4;
            } else {
                g->last_time = D_800D2FE0;
            }
        }
    } else {
        g->speed += 409;
        if (g->max_speed < g->speed) {
            g->speed = g->max_speed;
        }
        if (func_80031928(g, fixed_mul(D_800DE30C, g->speed) + 0x32000) == 0) {
            g->speed -= 1638;
            if (g->speed <= 0 || func_80031928(g, fixed_mul(D_800DE30C, g->speed)) == 0) {
                g->speed = 0;
                g->last_time = D_800D2FE0;
            }
        }
        if (g->speed > 0) {
            step = fixed_mul(D_800DE30C, g->speed);
            g->x += fixed_mul(func_8008AD60(g->angle >> 4), step);
            g->z += fixed_mul(func_8008ACC0(g->angle >> 4), step);
            func_80015F64(g->cell, quarter(g->x), quarter(g->z));
        }
    }
    func_80031830(g);
    func_80061CC0((short)to_int(g->x), (short)to_int(g->z), 0, 0, 0);
}
