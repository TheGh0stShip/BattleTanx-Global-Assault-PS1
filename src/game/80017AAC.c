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
typedef struct Hit Hit;
extern Cell D_800C62B0[];
extern Grid D_800C6290;
extern unsigned short D_800A436C;
extern unsigned short D_800C60F8[];
extern unsigned short D_800A435C[4];
extern unsigned short D_800A4364[4];
unsigned short func_80017878(unsigned short, unsigned short, unsigned short, int, Hit *, unsigned short, unsigned short);

static inline void clear_marks(void) {
    unsigned short i;

    for (i = 0; i < D_800A436C; i++) {
        unsigned short id = D_800C60F8[i];

        D_800C62B0[id].flags &= ~0x04000000;
    }
    D_800A436C = 0;
}

static inline void shrink(Cell *e, unsigned short expand) {
    if (expand) {
        e->min_x += expand;
        e->max_x -= expand;
        e->min_z += expand;
        e->max_x -= expand;
    }
}

unsigned short func_80017AAC(unsigned short id, int mask, Hit *hits, unsigned short expand, unsigned short first_only) {
    Cell *e = &D_800C62B0[id];
    Grid *g = &D_800C6290;
    short dx = e->x - D_800C6290.x0;
    short dz = e->z - g->z0;
    unsigned short found;
    unsigned short n;
    unsigned short k;
    unsigned short idx;
    int col;
    unsigned short *cell;

    if (expand) {
        e->min_x -= expand;
        e->max_x += expand;
        e->min_z -= expand;
        e->max_x += expand;
    }
    found = func_80017878(id, g->cells[0], 0, mask, hits, 0, first_only);
    if (first_only && found) {
        shrink(e, expand);
        clear_marks();
        return found;
    }
    for (k = 0; k < 4; k++) {
        col = (dx + D_800A435C[k]) >> 10;
        idx = ((dz + D_800A4364[k]) >> 10) + k * g->rows;
        idx = idx * g->cols + col;
        cell = g->cells + idx + 1;
        n = func_80017878(id, *cell, k, mask, hits, found, first_only);
        if (n) {
            found += n;
            if (first_only || found >= 8) {
                shrink(e, expand);
                clear_marks();
                return found;
            }
        }
    }
    shrink(e, expand);
    clear_marks();
    return found;
}
