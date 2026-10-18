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
extern int D_800A6070;
extern int D_800A4750;
extern Pickup *func_800237D0(int, int);
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

int func_80029BF0(Vector *pos, int kind, int lifetime, int team, int mode) {
    Pickup *p;
    int r;

    if (D_800A6070 == 7 && (kind == 9 || kind == 6 || kind == 15)) {
        kind = 11;
    }
    if (kind == 8) {
        mode = 0;
    }
    p = func_800237D0(9, 48);
    if (p == 0) {
        return -1;
    }
    if (D_800A4750 != 0 && kind != 5 && lifetime == 0) {
        D_800A46F4[kind]++;
        D_800A474C++;
    }
    if (kind == 21) {
        p->random = 1;
        r = func_80086C84() % D_800A474C;
        for (kind = 0; r >= D_800A46F4[kind]; kind++) {
            r -= D_800A46F4[kind];
        }
        if (kind == 5) {
            D_800A46F4[5] = 0;
            D_800A474C--;
        }
        if ((unsigned int)kind >= 22) {
            kind = 19;
        }
        if (kind == 21) {
            kind = 11;
        }
        if (kind == 0) {
            kind = 19;
        }
    } else {
        p->random = 0;
    }
    p->kind = kind;
    p->taken = 0;
    p->pos.x = pos->x;
    p->pos.y = pos->y;
    p->pos.z = pos->z;
    p->cell = func_800162F0(p, to_cell(p->pos.x), to_cell(p->pos.z), 0, -35, 35, -35, 35,
                            (short)(to_cell(p->pos.y) - 35), (short)(to_cell(p->pos.y) + 35), 0, 16);
    if (lifetime > 0) {
        p->expire = D_800D2FE0 + lifetime;
    } else {
        p->expire = 0;
    }
    p->respawn = 0;
    p->team = team;
    p->b28 = 255;
    p->mode = mode;
    return 0;
}
