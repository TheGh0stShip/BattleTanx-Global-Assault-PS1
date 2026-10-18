typedef struct { int x, y, z; } Vector;
typedef struct { int pad[5]; short height; short pad2; int pad3[4]; } Cell;
typedef struct { char pad[32]; Vector pos; char pad2[68 - 44]; unsigned char active; } Base;
typedef struct {
    int pad[2];
    int floor;
    unsigned short cell;
    short pad2;
    int y;
    unsigned int state;
    int timer;
    Base *base;
    int pad3[3];
    int hp;
    int rider;
} Lift;
extern Cell D_800C62B0[];
extern int D_800D2FE0;
void func_80029ADC(int, Lift *);
void func_80015F64(int, int, int);
unsigned int func_80086C84(void);
void func_8001B094(int);

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

static inline Cell *cell_at(int i) {
    return &D_800C62B0[i];
}

static inline void move_lift(Lift *l, int delta) {
    short x;
    short z;
    int h;
    int cell;

    l->y += delta;
    x = (unsigned int)to_int(l->base->pos.x) >> 2;
    z = (unsigned int)to_int(l->base->pos.z) >> 2;
    h = (to_int(l->y) << 14) >> 16;
    cell = l->cell;
    func_80015F64(cell, x, z);
    cell_at(cell)->height = h;
}

static inline void wait_state(Lift *l, int state) {
    l->state = state;
    l->timer = D_800D2FE0 + func_80086C84() % 60;
}

void func_800359E8(Lift *l, int *done) {
    if (l->hp < 0) {
        l->state = 4;
        if (l->rider != 0) {
            func_80029ADC(l->rider, l);
            l->rider = 0;
        }
    }
    switch (l->state) {
    case 0:
        move_lift(l, -8192);
        if (l->y < -0x32000 - l->floor) {
            wait_state(l, 1);
        }
        break;
    case 1:
        if (D_800D2FE0 - l->timer > 120) {
            l->state = 2;
        }
        break;
    case 2:
        move_lift(l, 8192);
        if (l->y > 0) {
            wait_state(l, 3);
        }
        break;
    case 3:
        if (D_800D2FE0 - l->timer > 120) {
            l->state = 0;
        }
        break;
    case 4:
        move_lift(l, -8192);
        if (l->y < -0x96000 - l->floor) {
            l->base->active = 0;
            *done = 1;
            func_8001B094(l->cell);
        }
        break;
    }
}
