typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    void *pending;
    unsigned short head;
    unsigned short count;
    unsigned short last_count;
    unsigned short next;
    char padC[0x1C - 0xC];
    int request;
    unsigned int budget;
    Vector from;
    Vector to;
    int stamp;
} Route;
typedef struct {
    char pad0[8];
    Vector position;
    char pad14[0xBC - 0x14];
    int stamp;
    char padC0[0xF8 - 0xC0];
    Route route;
    char pad138[0x180 - 0x138];
    int flags;
} Tank;
typedef struct {
    char pad0[0xE010];
    unsigned short max_route;
} MoveSystem;
extern MoveSystem *D_800A5B24;
extern Vector *func_8004DFEC(Tank *);
extern int func_800495D8(Vector *, Vector *);
extern void func_8004AF4C(Tank *);
extern unsigned int func_80083A5C(int);
extern int func_8004B880(Tank *);
extern void func_8004C17C(Tank *);
extern void func_8004BB98(Tank *);

static inline int route_mode(Tank *tank, Route *route, Vector *target) {
    register int mode asm("$18") = 0;

    goto test;
body:
    if (tank->flags & 1) {
        goto out;
    }
    if (route->head == 0 || func_800495D8(&route->from, target) < func_800495D8(&route->to, target) * 4) {
        goto rebuild;
    }
    if (route->pending != 0) {
        goto out;
    }
    if (route->next != 0) {
        mode = 1;
        goto out;
    }
rebuild:
    mode = 2;
    goto out;
test:
    if (target != 0) {
        goto body;
    }
out:
    return mode;
}

void func_8004A9BC(Tank *tank) {
    Route *route = &tank->route;
    Vector *target;
    int mode;
    unsigned int deadline;
    unsigned int now;
    int flags;

    if (route->request == 2) {
        return;
    }
    target = func_8004DFEC(tank);
    if (target == 0) {
        return;
    }
    route->stamp = tank->stamp;
    mode = route_mode(tank, &tank->route, target);
    if (mode == 1) {
        goto expand;
    }
    if (mode == 0) {
        return;
    }
    if (mode == 2) {
        route->from.x = tank->position.x;
        route->from.z = tank->position.z;
        route->to.x = target->x;
        route->to.z = target->z;
        func_8004AF4C(tank);
        if (route->request == mode) {
            route->request = 0;
            tank->flags |= 8;
            return;
        }
    expand:
        now = func_80083A5C(2);
        if (route->budget <= 100) {
            deadline = now + route->budget;
        } else {
            deadline = now + 100;
        }
        goto check;
    step:
        if (func_8004B880(tank) == 0) {
            goto done;
        }
        if (route->pending != 0) {
            goto check_end;
        }
        if (!(deadline < func_80083A5C(2))) {
            goto done;
        }
    check:
        if (route->count < D_800A5B24->max_route) {
            goto step;
        }
    check_end:
        route->budget = 0;
    done:
        if (route->head != 0 && route->request != 0) {
            route->request = 0;
        }
        if (route->pending == 0) {
            flags = tank->flags | 4;
            tank->flags = flags;
            if (route->count >= 5) {
                flags &= ~0x600;
                tank->flags = flags | 0x80;
                if (route->count >= 6) {
                    tank->flags = flags | 0x180;
                }
            }
            func_8004C17C(tank);
        } else {
            tank->flags = (tank->flags & ~0x604) | 0x180;
            func_8004BB98(tank);
        }
        route->last_count = route->count;
    }
}
