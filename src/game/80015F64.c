typedef struct Cell {
    int flags;
    void *owner;
    unsigned short next[4];
    unsigned short x;
    unsigned short z;
    short y;
    char pad16[0x22 - 0x16];
    short radius;
    char pad24[0x28 - 0x24];
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
extern unsigned short D_800A435C[4];
extern unsigned short D_800A4364[4];
int func_80015C2C(unsigned short, unsigned short *, unsigned short);

void func_80015F64(unsigned short id, short x, short z) {
    Grid *g;
    Cell *e;
    short nx;
    short nz;
    short ox;
    short oz;
    unsigned short k;
    int ncx;
    int ncz;
    int ocx;
    int ocz;
    unsigned short *cell;
    unsigned short idx;
    Cell *c;

    if (id == 0xFFFF) {
        return;
    }
    e = &D_800C62B0[id];
    g = &D_800C6290;
    if (e->radius > 1024) {
        e->x = x;
        e->z = z;
        return;
    }
    nx = x - D_800C6290.x0;
    nz = z - g->z0;
    ox = e->x - D_800C6290.x0;
    oz = e->z - g->z0;
    for (k = 0; k < 4; k++) {
        ocx = (ox + D_800A435C[k]) >> 10;
        ocz = (oz + D_800A4364[k]) >> 10;
        ncx = (nx + D_800A435C[k]) >> 10;
        ncz = (nz + D_800A4364[k]) >> 10;
        if (ocx != ncx || ocz != ncz) {
            idx = ocz + k * g->rows;
            idx = idx * g->cols + ocx;
            func_80015C2C(id, g->cells + idx + 1, k);
            idx = ncz + k * g->rows;
            idx = idx * g->cols + ncx;
            cell = g->cells + idx + 1;
            c = &D_800C62B0[id];
            c->next[k] = *cell;
            *cell = id;
        }
    }
    e->x = x;
    e->z = z;
}
