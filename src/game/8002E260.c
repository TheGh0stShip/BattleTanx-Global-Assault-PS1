typedef struct { int x, y, z; } Vector;
typedef struct { unsigned int flags; int link; int pad[6]; short owner; short pad2[3]; } Cell;
typedef struct { char pad[32]; Vector pos; int pad2[4]; int value; char pad3[5]; unsigned char dead; } Target;
typedef struct {
    int pad[2];
    Target *target;
    int model;
    int value;
    int pad2[4];
    unsigned short cell;
    unsigned short angle;
    unsigned char dead;
    unsigned char solid;
} Obj;
extern Cell D_800C62B0[];
static inline Cell *cell_at(int i) {
    return &D_800C62B0[i];
}

void func_80035878(int, Vector *, int, int, int);
void func_80035948(int, Vector *, int, int, int, int, int, int);
void func_8001B094(int);
void func_80022CAC(Obj *);

static inline void set_owner(int i, short owner) {
    cell_at(i)->owner = owner;
}

void func_8002E260(Obj *o, unsigned short tilt, unsigned char tilted) {
    int cell;

    if (o->dead == 0) {
        o->dead = 1;
        o->target->dead = 1;
        if (o->value != 0) {
            o->target->value = o->value;
        } else {
            o->target->value = 0;
        }
        if (tilted) {
            func_80035878(o->model, &o->target->pos, o->angle, tilt, 0);
        } else {
            func_80035948(o->model, &o->target->pos, o->angle, 0, 0, 0, 0, 0);
        }
        cell = o->cell;
        if (cell != 0xFFFF) {
            if (o->solid) {
                cell_at(cell)->flags |= 0x200;
                cell_at(o->cell)->flags &= 0xFFEFFFFD;
                set_owner(o->cell, 2);
            } else {
                func_8001B094(cell);
                func_80022CAC(o);
            }
        }
    }
}
