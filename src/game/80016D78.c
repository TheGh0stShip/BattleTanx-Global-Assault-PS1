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
    char pad1E[0x24 - 0x1E];
    unsigned short angle;
    char pad26[0x28 - 0x26];
} Cell;
typedef struct Pos2 {
    int x;
    int z;
} Pos2;
extern Cell D_800C62B0[];
void func_800167D0(Pos2 *, unsigned short, Pos2 *);

static inline int to_int(int v) {
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

static inline void set_pos2(Pos2 *p, int x, int z) {
    p->x = x;
    p->z = z;
}

int func_80016D78(int x, int z, unsigned short id) {
    Cell *e = &D_800C62B0[id];
    Pos2 in;
    Pos2 out;

    set_pos2(&in, (short)(x - e->x) << 14, (short)(z - e->z) << 14);
    func_800167D0(&in, e->angle, &out);
    if ((short)(to_int(out.x) >> 2) < e->min_x || (short)(to_int(out.x) >> 2) > e->max_x || (short)(to_int(out.z) >> 2) < e->min_z || (short)(to_int(out.z) >> 2) > e->max_z) {
        return 0;
    }
    return 1;
}
