typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    char pad0[8];
    Vector position;
    char pad14[0xFC - 0x14];
    unsigned short route;
    char padFE[0x13C - 0xFE];
    Vector side_goal;
    char pad148[0x148 - 0x148];
    unsigned short route_seen;
    unsigned short route_seen2;
    char pad14C[0x180 - 0x14C];
    int flags;
} Tank;
extern Vector *func_8004CFB4(Tank *);
extern int func_8004CFFC(Tank *, Vector *);
extern void func_8004AC64(Tank *);
extern void func_8004960C(Vector *, Vector *, Vector *);
extern int func_800494FC(Vector *, Vector *, Vector *);

static inline Vector *find_route_goal(Tank *tank, int pinned) {
    Vector dir;
    Vector side;
    Vector *sg;
    Vector *goal;

    goal = func_8004CFB4(tank);
    if (pinned) {
        __asm__("" : "+r"(goal));
    }
    if (goal != 0) {
        return goal;
    }
    if (!(tank->flags & 0x80)) {
        tank->route_seen = 0;
    } else {
        tank->route_seen2 = 0;
        tank->route_seen = tank->route;
        goal = func_8004CFB4(tank);
        if (goal != 0) {
            sg = &tank->side_goal;
            func_8004960C(&dir, &tank->position, goal);
            side.x = goal->x + dir.z;
            side.z = goal->z - dir.x;
            if (func_800494FC(&tank->position, &side, goal) == 1) {
                tank->side_goal.x = side.x;
                sg->z = side.z;
            } else {
                tank->side_goal.x = goal->x - dir.z;
                sg->z = goal->z + dir.x;
            }
        }
    }
    return goal;
}

void func_8004CCE8(Tank *tank) {
    Vector *goal = find_route_goal(tank, 1);

    if (goal != 0 && func_8004CFFC(tank, goal) != 0) {
        func_8004AC64(tank);
        find_route_goal(tank, 0);
    }
}
