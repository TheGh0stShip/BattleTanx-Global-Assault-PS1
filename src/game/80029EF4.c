typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    char pad0[8];
    Vector pos;
    unsigned short angle;
    unsigned short cell;
    int kind;
    int respawn;
    int expire;
    int team;
    unsigned char b28;
    unsigned char random;
    unsigned char b2A;
    unsigned char taken;
    int mode;
} Pickup;

extern int D_800D2FE0;
extern short D_800A46F4[];
extern unsigned int D_800A474C;
extern int func_80022814(void);
extern void func_8001B094(int);
extern unsigned int func_80086C84(void);
extern unsigned short func_800162F0(Pickup *, int, int, int, int, int, int, int, int, int, int, int);

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

static inline short to_cell(int value) {
    return fixed_to_int(value) >> 2;
}

void func_80029EF4(Pickup *p, int *done) {
    int r;
    int i;

    if (p->taken && func_80022814() && p->mode != 1) {
        *done = 1;
        func_8001B094(p->cell);
        return;
    }
    if (p->expire != 0) {
        if (p->taken || D_800D2FE0 >= p->expire) {
            *done = 1;
            func_8001B094(p->cell);
        }
        return;
    }
    if (p->taken) {
        p->taken = 0;
        func_8001B094(p->cell);
        p->respawn = D_800D2FE0 + 600 + func_80086C84() % 1200;
        return;
    }
    if (p->respawn != 0 && p->respawn < D_800D2FE0) {
        p->respawn = 0;
        if (p->random) {
            i = 0;
            r = func_80086C84() % D_800A474C;
            for (; r >= D_800A46F4[i]; i++) {
                r -= D_800A46F4[i];
            }
            if (i == 5) {
                D_800A46F4[5] = 0;
                D_800A474C--;
            }
            if ((unsigned int)i >= 22) {
                i = 19;
            }
            if (i == 21) {
                i = 11;
            }
            if (i == 0) {
                i = 19;
            }
            p->kind = i;
        }
        p->cell = func_800162F0(p, to_cell(p->pos.x), to_cell(p->pos.z), 0, -35, 35, -35, 35,
                                (short)(to_cell(p->pos.y) - 35), (short)(to_cell(p->pos.y) + 35), 0, 16);
    }
}
