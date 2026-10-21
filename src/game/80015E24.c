typedef struct Cell {
    int flags;
    void *owner;
    unsigned short next[4];
    unsigned short x;
    unsigned short z;
    char pad14[0x28 - 0x14];
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

void func_80015E24(unsigned short id) {
    Cell *e = &D_800C62B0[id];
    Grid *g = &D_800C6290;
    int dx = e->x - D_800C6290.x0;
    int dz = e->z - g->z0;
    unsigned char k;
    unsigned short idx;
    int col;
    short sx;
    short sz;

    if ((unsigned short)func_80015C2C(id, g->cells, 0)) {
        return;
    }
    sx = dx;
    sz = dz;
    for (k = 0; k < 4; k++) {
        col = (sx + D_800A435C[k]) >> 10;
        idx = ((sz + D_800A4364[k]) >> 10) + k * g->rows;
        idx = idx * g->cols + col;
        func_80015C2C(id, g->cells + idx + 1, k);
    }
}
