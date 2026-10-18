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
void func_800167D0(Pos2 *, unsigned short, Pos2 *);

static inline int to_int(int v) {
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

static inline void set_pos2(Pos2 *p, short x, short z) {
    p->x = x << 14;
    p->z = z << 14;
}

void func_80016EE0(Cell *base, Cell *other, Cell *out) {
    Pos2 in;
    Pos2 rel;

    set_pos2(&in, other->x - base->x, other->z - base->z);
    func_800167D0(&in, base->angle, &rel);
    out->x = (unsigned int)to_int(rel.x) >> 2;
    out->z = (unsigned int)to_int(rel.z) >> 2;
    out->angle = other->angle - base->angle;
    out->min_x = other->min_x;
    out->max_x = other->max_x;
    out->min_z = other->min_z;
    out->max_z = other->max_z;
}
