typedef struct { int x, y, z; } Vector;
typedef struct { unsigned int flags; int link; int pad[6]; unsigned short owner; short pad2[3]; } Cell;
typedef struct { char pad[32]; Vector pos; int pad2[4]; int value; } Target;
typedef struct {
    int pad[2];
    Target *target;
    int model;
    int value;
    unsigned short cell;
    unsigned short angle;
    unsigned char broken;
} Crate;
typedef struct { int x; int z; } Hit;
extern Cell D_800C62B0[];
int func_8008AE30(int, int);
void func_80053790(int, int, int);
void func_80035878(int, Vector *, int, int, int);

static inline Cell *cell_at(int i) {
    return &D_800C62B0[i];
}

static inline void set_owner(int i, short owner) {
    cell_at(i)->owner = owner;
}

void func_8002D378(Crate *c, int arg, Hit *hit) {
    int tilt;

    if (c->broken == 0) {
        tilt = (func_8008AE30(c->target->pos.x - hit->x, c->target->pos.z - hit->z) & 0xFFF) << 4;
        if (c->broken == 0) {
            func_80053790(51, c->target->pos.x, c->target->pos.z);
            c->broken = 1;
            c->target->value = c->value;
            cell_at(c->cell)->flags |= 0x200;
            cell_at(c->cell)->flags &= ~0x00800400;
            func_80035878(c->model, &c->target->pos, c->angle, tilt, 0);
            set_owner(c->cell, 2);
        }
    }
}
