typedef struct Cell {
    int head;
    char pad04[4];
    unsigned short next[4];
    unsigned short x;
    unsigned short z;
    char pad14[2];
    short min_x;
    short max_x;
    short min_z;
    short max_z;
    char pad1E[0x28 - 0x1E];
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
void func_80015F64(unsigned short, short, short);

void func_80016190(unsigned short id, int x, int z) {
    Grid *g;
    Cell *e;
    short dx;
    short dz;
    short cx;

    g = &D_800C6290;
    dx = x - D_800C6290.x0;
    e = &D_800C62B0[id];
    cx = dx;
    dz = z - g->z0;

    if (dx < 0) {
        cx = 0;
        e->min_x += dx;
        e->max_x += dx;
    } else if (dx >= g->cols << 10) {
        dx -= g->cols << 10;
        e->min_x -= dx;
        e->max_x -= dx;
        cx = (g->cols << 10) - 1;
    }
    if (dz < 0) {
        e->min_z += dz;
        e->max_z += dz;
        dz = 0;
    } else if (dz >= g->rows << 10) {
        short d = dz - (g->rows << 10);

        e->min_z -= d;
        e->max_z -= d;
        dz = (g->rows << 10) - 1;
    }
    func_80015F64(id, cx + g->x0, dz + g->z0);
}
