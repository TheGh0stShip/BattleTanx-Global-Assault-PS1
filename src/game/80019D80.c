typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;
typedef struct Pos2 {
    int x;
    int z;
} Pos2;
typedef struct Cell {
    int flags;
    void *owner;
    unsigned short next[4];
    char pad10[0x28 - 0x10];
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
typedef struct Hit Hit;
extern Cell D_800C62B0[];
extern Grid D_800C6290;
extern unsigned short D_800A435C[4];
extern unsigned short D_800A4364[4];
extern unsigned short D_800A436C;
extern unsigned short D_800C60F8[];
int abs(int);
unsigned short func_80019828(Vector *, Vector *, unsigned short, unsigned short, int, unsigned short, void *, Hit *,
                             unsigned int *);

static inline int to_int(int v) {
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

static inline int idiv(int a, int b) {
    return a / b;
}

static inline short to_cell(int v) {
    return to_int(v) >> 2;
}

static inline unsigned short at_least_one(unsigned short v) {
    return v ? v : 1;
}

static inline void clear_visited(void) {
    unsigned short i;
    unsigned short idx;

    for (i = 0; i < D_800A436C; i++) {
        idx = D_800C60F8[i];
        D_800C62B0[idx].flags &= ~0x04000000;
    }
    D_800A436C = 0;
}

unsigned short func_80019D80(Vector *from, Vector *to, int mask, unsigned short reach, void *ignore, Hit *out) {
    Grid *g;
    Pos2 step;
    Pos2 d;
    unsigned int best;
    unsigned short count;
    unsigned short nx;
    unsigned short nz;
    unsigned short result;
    unsigned short i;
    unsigned short k;
    unsigned short idx;
    int col;
    unsigned short *cell;
    short gx;
    short gz;
    int ax;
    int dx;
    int az;

    dx = to->x - from->x;
    ax = idiv(abs(dx), 512);
    result = 0;
    best = 0xFFFFFFFF;
    g = &D_800C6290;
    d.z = to->z - from->z;
    d.x = dx;
    nx = to_int(ax) >> 2;
    az = abs(d.z);
    nz = to_cell(idiv(az, 512));
    nx = nx ? nx : 1;
    nz = nz ? nz : 1;
    step.x = 0;
    step.z = 0;
    if (nx >= nz) {
        step.x = d.x / nx;
        step.z = d.z / nx;
        count = nx;
    } else {
        step.x = d.x / nz;
        step.z = d.z / nz;
        count = nz;
    }
    gx = to_cell(from->x + idiv(step.x, 2)) - g->x0;
    gz = to_cell(from->z + idiv(step.z, 2)) - g->z0;
    if (gx < 0 || gz < 0 || gx >= g->cols << 10 || gz >= g->rows << 10) {
        clear_visited();
        return 0;
    }
    i = 0;
    for (;;) {
        if (gx < 0 || gz < 0 || gx >= g->cols << 10 || gz >= g->rows << 10) {
            break;
        }
        for (k = 0; k < 4; k++) {
            col = (gx + D_800A435C[k]) >> 10;
            idx = ((gz + D_800A4364[k]) >> 10) + k * g->rows;
            idx = idx * g->cols + col;
            cell = g->cells + idx + 1;
            result |= func_80019828(from, to, *cell, k, mask, reach, ignore, out, &best);
        }
        if (result) {
            break;
        }
        gx += to_cell(step.x);
        gz += to_cell(step.z);
        i++;
        if (i > count) {
            break;
        }
    }
    result |= func_80019828(from, to, g->cells[0], 0, mask, reach, ignore, out, &best);
    clear_visited();
    return result;
}
