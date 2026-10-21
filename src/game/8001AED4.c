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
    short x;
    short z;
    int pad4;
    unsigned short width;
    unsigned short depth;
} Grid;
extern Cell D_800C62B0[];
extern Grid D_800C6290;
int abs(int);


static inline int abs_max(short a, short b) {
    int r = abs(a);
    int s = abs(b);
    if (r < s) r = s;
    return r;
}

static inline short approx_len(short a, short b) {
    int big = abs(a);
    int bb = abs(b);
    int small;
    if (big < bb) big = bb;
    small = abs(a);
    if (bb < small) small = bb;
    return big + small * 3 / 8;
}

int func_8001AED4(void *owner, int x, int z, short y,
                  short min_x, short max_x, short min_z, short max_z,
                  short y_low, short y_high, unsigned short angle, int flags) {
    int id = 1300;
    int off = id * sizeof(Cell);
    register Cell *cells asm("$3") = D_800C62B0;
    Cell *c = (Cell *)((char *)cells + off);
    int dx, dz;

    c->x = x;
    c->z = z;
    c->y = y;
    c->min_x = min_x;
    c->max_x = max_x;
    c->min_z = min_z;
    c->max_z = max_z;
    c->y_low = y_low;
    c->y_high = y_high;
    c->angle = angle;
    {
        int mx = abs_max(max_x, min_x);
        int mz = abs_max(max_z, min_z);
        c->radius = approx_len(mz, mx);
    }
    c->flags = flags;
    c->owner = owner;
    {
        Grid *g = &D_800C6290;
        dx = (short)x - g->x;
        dz = (short)z - g->z;
    }
    if (dx < 0 || dz < 0 || dx >= D_800C6290.width << 10 || dz >= D_800C6290.depth << 10)
        return 0xFFFF;
    return id;
}
