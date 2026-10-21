typedef struct Cell {
    int flags;
    void *owner;
    unsigned short next[4];
    unsigned short x;
    unsigned short z;
    short y;
    short min_x;
    short max_x;
    short min_z;
    short max_z;
    short y_low;
    short y_high;
    short radius;
    unsigned short angle;
    char pad26[0x28 - 0x26];
} Cell;
typedef struct Grid {
    unsigned short x0;
    unsigned short z0;
    short width;
    short depth;
    unsigned short cols;
    unsigned short rows;
    unsigned short *cells;
} Grid;
extern Cell D_800C62B0[];
extern Grid D_800C6290;
extern unsigned short D_800C6288;
extern unsigned short D_800A4370;
extern short D_800A4372;
int abs(int);
int func_80047B7C(int, int);
void func_80015CF8(unsigned short);
void func_80016190(unsigned short, int, int);

static inline unsigned short cell_alloc(void) {
    unsigned short i;
    unsigned short id;
    Cell *c;

    if (D_800C6288 == 0xFFFF) {
        return 0xFFFF;
    }
    id = D_800C6288;
    c = &D_800C62B0[id];
    D_800C6288 = c->next[0];
    for (i = 0; i < 4; i++) {
        c->next[i] = 0xFFFF;
    }
    c->owner = 0;
    return id;
}

static inline int imax(int a, int b) {
    if (a < b) {
        a = b;
    }
    return a;
}

unsigned short func_800162F0(void *owner, short x, short z, short y, short min_x, short max_x, short min_z,
                             short max_z, short y_low, short y_high, unsigned short angle, int flags) {
    unsigned short id;
    Cell *c;
    short t;
    int ax;
    int bx;
    short ex;
    short ez;
    int big;
    int small;
    Grid *g;
    short dx;
    short dz;

    id = cell_alloc();
    if (id == 0xFFFF) {
        return 0xFFFF;
    }
    c = &D_800C62B0[id];
    c->flags = flags;
    c->owner = owner;
    if (flags & 0x4863) {
        if (flags == 0x800) {
            angle = 0;
        }
        switch (angle) {
        case 0:
        case 0x4000:
        case 0x8000:
        case 0xC000:
            break;
        default:
            if (func_80047B7C(0, angle) <= 4096) {
                angle = 0;
            } else if (func_80047B7C(0x4000, angle) <= 4096) {
                angle = 0x4000;
            } else if (func_80047B7C(0x8000, angle) <= 4096) {
                angle = 0x8000;
            } else if (func_80047B7C(0xC000, angle) <= 4096) {
                angle = 0xC000;
            }
            break;
        }
        switch (angle) {
        case 0:
            break;
        case 0x4000:
            t = min_z;
            min_z = -max_x;
            max_x = max_z;
            max_z = -min_x;
            min_x = t;
            angle = 0;
            break;
        case 0x8000:
            t = min_x;
            min_x = -max_x;
            max_x = -t;
            t = min_z;
            min_z = -max_z;
            max_z = -t;
            angle = 0;
            break;
        case 0xC000:
            t = min_z;
            min_z = min_x;
            min_x = -max_z;
            max_z = max_x;
            max_x = -t;
            angle = 0;
            break;
        }
    }
    ax = abs(max_x);
    c->x = x;
    c->z = z;
    c->y = y;
    c->min_x = min_x;
    c->max_x = max_x;
    c->min_z = min_z;
    c->max_z = max_z;
    bx = abs(min_x);
    c->y_low = y_low;
    c->y_high = y_high;
    c->angle = angle;
    ex = imax(ax, bx);
    ez = imax(abs(max_z), abs(min_z));
    big = abs(ez);
    if (big < abs(ex)) {
        big = abs(ex);
    }
    small = abs(ez);
    if (abs(ex) < small) {
        small = abs(ex);
    }
    c->radius = big + small * 3 / 8;
    if (D_800A4372 < c->radius) {
        D_800A4372 = c->radius;
    }
    g = &D_800C6290;
    dx = x - D_800C6290.x0;
    dz = z - g->z0;
    if (dx < 0 || dz < 0 || dx >= g->cols << 10 || dz >= g->rows << 10) {
        if (dx + max_x < 0 || dz + max_z < 0 || dx + min_x >= g->cols << 10 || dz + min_z >= g->rows << 10) {
            c->next[0] = D_800C6288;
            D_800C6288 = id;
            c->owner = 0;
            return 0xFFFF;
        }
        func_80016190(id, x, z);
    } else {
        func_80015CF8(id);
    }
    D_800A4370++;
    return id;
}
