typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    short id;
} HitObject;
typedef struct {
    HitObject *object;
    char pad4[36];
} Hit;
typedef struct {
    int x;
    int z;
} Point;
typedef struct Pending Pending;
struct Pending {
    unsigned char kind;
    char pad1;
    unsigned short prev;
    int key;
    Pending *next;
};
typedef struct {
    unsigned char kind;
    char pad1;
    unsigned short prev;
    int x;
    char pad8[4];
    int z;
    char pad10[0x18 - 0x10];
    unsigned char mode;
    char pad19;
    unsigned short link;
} Node;
typedef struct {
    char pad0[0x10];
    int probe_mask;
} Owner;
typedef struct {
    Pending *pending;
    unsigned short head;
    unsigned short count;
    char pad8[0x3C - 8];
    int ignore_id;
} Route;
typedef struct {
    int x;
    int y;
    int z;
    unsigned short route_seen;
    unsigned short route_seen2;
} SideGoal;
typedef struct {
    int id;
    char pad04[4];
    Vector position;
    char pad14[0x9C - 0x14];
    int type;
    char padA0[0xC9 - 0xA0];
    unsigned char mode;
    char padCA[0xF8 - 0xCA];
    Route route;
    char pad138[4];
    SideGoal side;
    char pad14C[0x180 - 0x14C];
    int flags;
    char pad184[0x208 - 0x184];
    Owner *owner;
} Tank;
typedef struct {
    char pad0[0xA8];
    unsigned short reach;
    char padAA[0xD0 - 0xAA];
} VehicleType;
extern VehicleType D_800A4EF4[];
extern short D_800C628C;
extern unsigned short func_80019D80(Vector *, Vector *, int, unsigned short, int, Hit *);
extern void func_8004BF64(Tank *);
extern Node *func_8004A794(unsigned short);
extern Node *func_8004BE20(Tank *);
extern Node *func_8004A02C(Node *, unsigned short *);
extern Vector *func_8004DFEC(Tank *);
extern Vector *func_8004BE44(Tank *, Node *);
extern int func_80049560(Tank *, int);
extern unsigned short func_8004A694(void *, int);
extern int func_800495D8(Vector *, Vector *);
extern void func_8004CCE8(Tank *);
extern void func_8004AC64(Tank *);

static inline int probe_clear(Tank *tank, Vector *to, int mask, unsigned short reach, Hit *hit) {
    D_800C628C = 0;
    return func_80019D80(&tank->position, to, mask, reach, tank->id, hit) == 0;
}

int func_8004C678(Tank *tank) {
    unsigned short seen = 0;
    Route *route = &tank->route;
    SideGoal *side = &tank->side;
    int mask = tank->owner->probe_mask | 0x2C700F;
    int result = 0;
    Vector *target;
    Node *node;
    Node *way;
    Node *after;
    Hit hit;
    Hit hit2;
    Vector p;
    Node *first;
    Pending *second;

    if (tank->flags & 0x100) {
        if (tank->flags & 8) {
            if (probe_clear(tank, &tank->position, mask, D_800A4EF4[tank->type].reach, &hit)) {
                func_8004BF64(tank);
                tank->flags &= ~8;
            }
        } else {
            target = 0;
            side->route_seen2 = 0;
            node = func_8004A794(0);
            if (node == 0) {
                node = func_8004BE20(tank);
            }
            way = func_8004A02C(node, &seen);
            if (way != 0) {
                after = func_8004A794(way->link);
                if (after != 0 && after->kind == 4 && (tank->mode == 1 || tank->mode == 3)) {
                    target = func_8004DFEC(tank);
                } else {
                    do {
                        target = func_8004BE44(tank, way);
                    } while (0);
                }
            }
            if (target != 0) {
                if (!probe_clear(tank, target, mask, func_80049560(tank, 1), &hit2)) {
                    if (route->ignore_id != 0 && hit2.object != 0 && route->ignore_id == hit2.object->id) {
                        p.x = target->x;
                        p.z = target->z;
                        func_8004BF64(tank);
                        route->head = func_8004A694(&first, 3);
                        first->link = func_8004A694(&second, 4);
                        first->prev = 0;
                        first->x = p.x;
                        first->z = p.z;
                        first->mode = 3;
                        second->prev = route->head;
                        second->key = func_800495D8(&tank->position, &p);
                        second->next = 0;
                        route->count = 2;
                        route->pending = second;
                        func_8004CCE8(tank);
                    }
                } else {
                    while (route->head != 0) {
                        if (route->head == seen) {
                            break;
                        }
                        func_8004AC64(tank);
                    }
                    func_8004CCE8(tank);
                    result = 1;
                }
            }
        }
    }
    side->route_seen2 = seen;
    return result;
}
