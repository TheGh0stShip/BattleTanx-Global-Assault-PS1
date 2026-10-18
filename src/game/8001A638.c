typedef struct Cell {
    int flags;
    void *owner;
    unsigned short next[4];
    char pad10[0x28 - 0x10];
} Cell;
typedef struct Grid {
    short x0;
    short z0;
    short width;
    short depth;
    unsigned short cols;
    unsigned short rows;
    unsigned short *cells;
} Grid;
typedef struct Hit {
    void *owner;
    unsigned short id;
    char pad06[0x24 - 6];
} Hit;
typedef struct Pos2 {
    int x;
    int z;
} Pos2;
extern Cell D_800C62B0[];
extern Grid D_800C6290;
extern unsigned short D_800A436C;
extern unsigned short D_800C60F8[];
extern unsigned short D_800A435C[4];
extern unsigned short D_800A4364[4];
unsigned short func_8001A40C(Pos2 *, unsigned short, unsigned short, int, Hit *, unsigned short, unsigned short);

static inline int to_int(int v) {
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

static inline void clear_marks(void) {
    unsigned short i;

    for (i = 0; i < D_800A436C; i++) {
        unsigned short id = D_800C60F8[i];

        D_800C62B0[id].flags &= ~0x04000000;
    }
}

unsigned short func_8001A638(Pos2 *pos, int mask, Hit *hits, unsigned short first_only) {
    Grid *g = &D_800C6290;
    Pos2 rel;
    unsigned short found;
    unsigned short n;
    int k;
    short cx;
    int px;
    int pz;
    short cz;

    rel.x = pos->x - (D_800C6290.x0 << 14);
    rel.z = pos->z - (g->z0 << 14);
    found = func_8001A40C(&rel, g->cells[0], 0, mask, hits, 0, first_only);
    if (first_only && found) {
        clear_marks();
        D_800A436C = 0;
        return found;
    }
    for (k = 0; (unsigned short)k < 4; k++) {
        px = (short)(to_int(rel.x) >> 2) + D_800A435C[(unsigned short)k];
        cx = (short)px >> 10;
        pz = (short)(to_int(rel.z) >> 2) + D_800A4364[(unsigned short)k];
        cz = (short)pz >> 10;
        {
            unsigned short *cell = g->cells;

            cell += (unsigned short)((cz + k * g->rows) * g->cols + cx);
            n = func_8001A40C(pos, cell[1], k, mask, hits, found, first_only);
        }
        if (n) {
            found += n;
            if (first_only || found >= 8) {
                clear_marks();
                D_800A436C = 0;
                return found;
            }
        }
    }
    clear_marks();
    D_800A436C = 0;
    return found;
}
