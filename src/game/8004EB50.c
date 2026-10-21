typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    unsigned int state;
    int time;
    short heading;
    short pad0A;
    Vector mid;
    int dist;
    Vector goal;
    int goal_dist;
} Wander;
typedef struct {
    char pad0[8];
    Vector position;
    char pad14[0x2C - 0x14];
    unsigned short heading;
    char pad2E[0x180 - 0x2E];
    int flags;
    Wander wander;
} Tank;
typedef struct {
    int clock;
} Clock;
extern Clock D_800D2FE0;
extern int func_8004986C(Vector *, Vector *, int);
extern void func_8004D7D8(Tank *);
extern void func_8004D804(Tank *);

static inline int take_flag(Tank *tank, int bit) {
    int flags = tank->flags;

    tank->flags = flags & ~bit;
    flags &= bit;
    return flags;
}

static inline void set_goal(Wander *w, Vector *p) {
    int z;

    w->goal.x = p->x;
    z = p->z;
    w->time = D_800D2FE0.clock + 90;
    w->goal_dist = 0x12C000;
    w->goal.z = z;
}

void func_8004EB50(Tank *tank) {
    Wander *w = &tank->wander;
    Vector p;

    switch (tank->wander.state) {
    case 2:
        if (take_flag(tank, 0x10) && w->goal_dist > 0x12C000) {
            p.x = tank->position.x;
            p.z = tank->position.z;
            if (func_8004986C(&p, &w->goal, 0x12C000) != 0) {
                set_goal(w, &p);
                w->heading = tank->heading;
                tank->wander.state = 3;
            } else {
                w->time = D_800D2FE0.clock + 60;
                tank->wander.state = 5;
            }
            func_8004D7D8(tank);
            break;
        }
        if (take_flag(tank, 0x20)) {
            w->time = D_800D2FE0.clock + 60;
            w->state = 5;
            func_8004D7D8(tank);
        }
        break;
    case 3:
        if (D_800D2FE0.clock >= w->time) {
            tank->wander.state = 4;
        }
        break;
    case 4:
        break;
    case 5:
        if (D_800D2FE0.clock >= w->time) {
            tank->wander.state = 2;
            func_8004D804(tank);
        }
        break;
    }
}
