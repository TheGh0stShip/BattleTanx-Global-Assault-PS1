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
typedef struct Pos2 {
    int x;
    int z;
} Pos2;
extern Cell D_800C62B0[];
void func_800167D0(Pos2 *, unsigned short, Pos2 *);


void func_8001AD5C(unsigned short id, unsigned short heading, Pos2 *out) {
    Cell *e = &D_800C62B0[id];
    Pos2 dir;
    short ext[2];
    short *width = &ext[0];
    short *depth = &ext[1];
    Cell *c = e;

    *width = c->max_x - c->min_x < 0 ? c->min_x - c->max_x : c->max_x - c->min_x;
    *depth = c->max_z - c->min_z < 0 ? c->min_z - c->max_z : c->max_z - c->min_z;
    if (ext[0] >= ext[1]) {
        dir.x = 0;
        dir.z = (short)(heading - 0x4000) >= 0 ? 4096 : -4096;
    } else {
        dir.z = 0;
        dir.x = (short)heading >= 0 ? -4096 : 4096;
    }
    func_800167D0(&dir, e->angle, out);
}
