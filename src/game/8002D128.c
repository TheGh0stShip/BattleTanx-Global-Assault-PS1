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
typedef struct { int pad; unsigned short type; } Msg;
typedef struct { int pad[3]; unsigned short tilt; } MsgData;
extern Cell D_800C62B0[];
void func_80053790(int, int, int);
void func_80035878(int, Vector *, int, int, int);

static inline Cell *cell_at(int i) {
    return &D_800C62B0[i];
}

static inline void set_owner(int i, short owner) {
    cell_at(i)->owner = owner;
}

static inline void crush(Crate *c, unsigned short tilt) {
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

void func_8002D128(Crate *c, Msg *msg, MsgData *data, int *result) {
    switch ((short)msg->type) {
    case 7:
    case 12:
    case 39:
    case 52:
        if (c->broken == 0) {
            crush(c, data->tilt);
            *result = 1;
        }
        break;
    case 40:
        *result = 5;
        break;
    case 4:
        if (c->broken != 0) {
            *result = 8;
        } else {
            *result = 9;
            crush(c, data->tilt);
        }
        break;
    case 30:
        if (c->broken == 0) {
            *result = 1;
        }
        break;
    case 75:
        *result = 1;
        break;
    }
}
