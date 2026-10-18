typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    char pad0[4];
    short x0;
    short y0;
    short z0;
    short pad0A;
    short x1;
    short y1;
    short z1;
} Box;

typedef struct {
    char pad0[8];
    Box *box;
} Shape;

typedef struct {
    char pad0[0x18];
    int shape;
    char pad1C[0x48 - 0x1C];
    int health;
    char pad4C[0x54 - 0x4C];
} Kind;

typedef struct {
    char pad0[6];
    unsigned char flags;
    char pad7;
    Vector pos;
    unsigned short angle;
    unsigned short angle2;
    unsigned char state;
    unsigned char b19;
    unsigned char b1A;
    unsigned char b1B;
    unsigned char alpha;
    unsigned char owner;
    char pad1E[6];
    unsigned short cell;
    char pad26[2];
    int t28;
    int t2C;
    int t30;
    int t34;
    int health;
    int forced;
} Building;

extern Kind D_800A44D4[];
extern Shape *D_800D2E14[];
extern unsigned char D_800AED57;
extern Building *func_800237D0(int, int);
extern int func_8002857C(unsigned char, Vector *, unsigned short);
extern unsigned short func_800162F0(Building *, int, int, int, int, int, int, int, int, int, int, int);

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

static inline short to_cell(int value) {
    return fixed_to_int(value) >> 2;
}

Building *func_80028720(unsigned char kind, Vector *pos, unsigned short angle, unsigned char owner, int forced) {
    Shape *shape = D_800D2E14[D_800A44D4[kind].shape];
    Building *b;
    int x;
    int z;
    int y0;
    int y1;
    int health;

    if (forced == 0 && !func_8002857C(kind, pos, angle)) {
        return 0;
    }
    b = func_800237D0(17, 64);
    if (b == 0) {
        return 0;
    }
    b->angle = angle;
    b->b1B = 0;
    b->b1A = 0;
    x = to_cell(pos->x);
    z = to_cell(pos->z);
    y0 = (short)(shape->box->y0 + to_cell(pos->y));
    y1 = (short)(shape->box->y1 + to_cell(pos->y));
    b->cell = func_800162F0(b, x, z, 0, shape->box->x0, shape->box->x1, shape->box->z0, shape->box->z1, y0, y1,
                            angle, 4096);
    b->alpha = 255;
    b->b19 = 0;
    b->t2C = -1000;
    b->angle2 = angle;
    b->t34 = 0;
    b->pos = *pos;
    b->t28 = -1000;
    b->t30 = -1000;
    b->owner = owner;
    b->state = 0;
    b->flags = 0;
    health = D_800A44D4[kind].health;
    b->health = health;
    if (D_800AED57 & 1) {
        b->health = health * 2;
    }
    b->forced = forced;
    return b;
}
