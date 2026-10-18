typedef struct {
    int x;
    int y;
    int z;
    int pad;
} Vector4;
typedef struct {
    int a;
    int b;
} Segment;
typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    unsigned char kind;
    char pad1;
    unsigned short prev;
    Vector position;
} PathNode;
typedef struct {
    char pad0[0xC];
    unsigned short left;
    unsigned short right;
    char pad10[0x1A - 0x10];
    unsigned short link;
} Junction;
typedef struct {
    char pad0[2];
    unsigned short prev;
    Vector position;
    Segment dir;
    unsigned char kind;
} Pending;
typedef struct {
    short id;
} HitObject;
typedef struct {
    HitObject *object;
    char pad4[4];
    Vector4 position;
    char pad18[0x20 - 0x18];
    unsigned short kind;
    char pad22[0x28 - 0x22];
} Hit;
typedef struct {
    int active;
    unsigned short pad4;
    unsigned short count;
    char pad8[2];
    unsigned short next;
    char padC[0x14 - 0xC];
    unsigned short a14;
    unsigned short a16;
    int a18;
    int stuck;
    char pad20[0x24 - 0x20];
    Vector home;
    Vector target;
    int target_id;
    int width;
} Route;
typedef struct {
    int id;
    char pad4[0xF8 - 0x4];
    Route route;
    char pad13C[0x14A - 0x13C];
    short f14A;
    char pad14C[0x180 - 0x14C];
    int flags;
} Tank;
extern short D_800C628C;
extern unsigned short func_8004A694(Pending **, int);
extern PathNode *func_8004A794(unsigned short);
extern void func_8004A8B0(PathNode *, Segment *);
extern void func_80049468(Segment *, int, Vector4 *, Vector4 *);
extern int func_80049438(Segment *, Segment *);
extern int func_800494FC(Vector *, Vector *, Vector *);
extern int func_80049560(Tank *, int);
extern unsigned short func_80019D80(Vector4 *, Vector *, int, unsigned short, int, Hit *);
extern int func_8004A160(unsigned short *, int);
extern void func_8004986C(Vector *, Vector *, int);
extern void func_80049384(Segment *, Hit *);
extern void func_800493E4(Segment *, int, Segment *);

static inline void reset_route(Tank *tank, Route *route) {
    tank->f14A = 0;
    func_8004A160(&route->pad4, 0);
    route->count = 0;
    route->active = 0;
    route->next = 0;
    route->a14 = 0;
    route->a16 = 0;
    route->a18 = 0;
    tank->flags &= ~0x180;
}

unsigned short func_8004B328(Tank *tank, unsigned short id, int mode) {
    Route *route = &tank->route;
    int flag = 0;
    unsigned short index;
    PathNode *node;
    PathNode *p;
    PathNode *q;
    PathNode *w;
    Vector *pos;
    Vector *ppos;
    Vector *target;
    int ok;
    int r2;
    unsigned short reach;
    Segment seg;
    Vector4 a;
    Vector4 b;
    Segment seg2;
    Hit hit;
    Vector4 from;
    Pending *pending;

    if (mode == 1 || mode == 17) {
        flag = 1;
    }
    index = func_8004A694(&pending, 3);
    if (pending == 0) {
        return 0;
    }
    node = func_8004A794(id);
    p = node;
    while (1) {
        if (p == 0) {
            pos = &tank->route.home;
            break;
        }
        if (p->kind == 3) {
            pos = &p->position;
            break;
        }
        p = func_8004A794(p->prev);
    }
    func_8004A8B0(node, &seg);
    func_80049468(&seg, route->width, &a, &b);
    if (node->kind == 2) {
        if (flag) {
            ((Junction *)node)->left = index;
        } else {
            ((Junction *)node)->right = index;
        }
        pending->prev = id;
        route->count++;
        ok = 1;
    } else {
        ((Junction *)node)->link = index;
        pending->prev = id;
        route->count++;
        q = func_8004A794(node->prev);
        func_8004A8B0(q, &seg2);
        if (func_80049438(&seg, &seg2) != 0) {
            w = q;
            while (1) {
                if (w == 0) {
                    ppos = &tank->route.home;
                    break;
                }
                if (w->kind == 3) {
                    ppos = &w->position;
                    break;
                }
                w = func_8004A794(w->prev);
            }
            if (flag) {
                ok = func_800494FC(ppos, &route->target, pos) == 2;
                r2 = func_800494FC(pos, &route->target, (Vector *)&b) == 1;
            } else {
                ok = func_800494FC(ppos, &route->target, pos) == 1;
                r2 = func_800494FC(pos, &route->target, (Vector *)&a) == 2;
            }
            ok = (ok && r2) == 0;
        } else {
            ok = 1;
        }
    }
    target = &route->target;
    if (ok) {
        target = (Vector *)&b;
        if (!flag) {
            target = (Vector *)&a;
        }
    }
    from.x = pos->x;
    from.z = pos->z;
    reach = func_80049560(tank, 0);
    D_800C628C = 0;
    if (func_80019D80(&from, target, 0x87007, reach, tank->id, &hit) != 0 &&
        !(route->target_id != 0 && hit.object != 0 && route->target_id == hit.object->id)) {
        if (hit.kind == 7) {
            route->stuck = 1;
            reset_route(tank, &tank->route);
            return 0;
        }
        pending->position.x = hit.position.x;
        pending->position.z = hit.position.z;
        func_8004986C(&pending->position, pos, route->width);
        func_80049384(&pending->dir, &hit);
        if (ok) {
            pending->kind = flag ? 17 : 18;
        }
        return index;
    }
    pending->position.x = target->x;
    pending->position.z = target->z;
    if (ok) {
        pending->kind = flag ? 1 : 2;
        func_800493E4(&seg, pending->kind, &pending->dir);
    } else {
        pending->kind = 3;
    }
    return index;
}
