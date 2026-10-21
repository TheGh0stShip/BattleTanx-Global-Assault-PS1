typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    int x;
    int y;
    int z;
    int pad;
} Vector4;
typedef struct {
    short x;
    short y;
    short z;
    short pad;
} SVector;
typedef struct {
    int a;
    int b;
} Segment;
typedef struct {
    unsigned char kind;
    char pad1;
    short current;
    int x;
    int pad8;
    int z;
    SVector point;
    unsigned char mode;
    char pad19;
    short d;
} MoveC;
typedef struct {
    char data[40];
} Hit;
typedef struct {
    char pad0[0x10];
    int probe_mask;
} Owner;
typedef struct {
    char pad0[4];
    unsigned short head;
    unsigned short count;
    char pad8[0x40 - 8];
    int width;
} Route;
typedef struct {
    int id;
    char pad04[4];
    Vector position;
    char pad14[0xF8 - 0x14];
    Route route;
    char pad13C[0x208 - 0x13C];
    Owner *owner;
} Tank;
typedef struct {
    char pad0[0xE010];
    unsigned short max_route;
} MoveSystem;
extern MoveSystem *D_800A5B24;
extern short D_800C628C;
extern void func_800493E4(void *, int, Segment *);
extern void func_80049468(Segment *, int, Vector4 *, Vector4 *);
extern int func_800494FC(Vector *, Vector4 *, Vector4 *);
extern int func_80049560(Tank *, int);
extern unsigned short func_80019D80(Vector *, Vector4 *, int, int, int, Hit *);
extern unsigned short func_8004A694(MoveC **, int);
extern void func_800493C0(void *, SVector *);
extern void func_8004BE9C(Tank *);
extern int func_8004A554(int, unsigned short *, unsigned short);
extern int func_8004A820(unsigned short *, unsigned short, Route *);
extern void func_8004CCE8(Tank *);

static inline int path_clear(Tank *tank, Vector4 *to, int mask, Hit *hit) {
    unsigned short reach = func_80049560(tank, 1);

    D_800C628C = 0;
    return func_80019D80(&tank->position, to, mask + 0x2C700F, reach, tank->id, hit) == 0;
}

int func_8004C970(Tank *tank, void *hit_point) {
    Vector4 *chosen = 0;
    int result = 0;
    register int mask asm("$21") = tank->owner->probe_mask;
    register Route *route asm("$20") = &tank->route;
    Segment segment;
    Vector4 near;
    Vector4 far;
    Hit hit;
    MoveC *move;
    MoveC *m;
    unsigned short id;
    int probe_mask;
    register Vector4 *farp asm("$18") = &far;

    func_800493E4(hit_point, 2, &segment);
    probe_mask = mask;
    func_80049468(&segment, route->width, farp, &near);
    if (func_800494FC(&tank->position, &near, farp) != 1 && path_clear(tank, farp, probe_mask, &hit)) {
        chosen = farp;
    } else if (path_clear(tank, &near, probe_mask, &hit)) {
        chosen = &near;
    }
    if (chosen != 0) {
        id = func_8004A694(&move, 3);
        func_800493C0(hit_point, &move->point);
        m = move;
        m->x = near.x;
        m->z = near.z;
        m->mode = 2;
        func_8004BE9C(tank);
        route->count += func_8004A554(0, &route->head, id);
        if (route->count >= D_800A5B24->max_route) {
            route->count -= func_8004A820(&route->head, D_800A5B24->max_route, route);
        }
        func_8004CCE8(tank);
        result = 1;
    }
    return result;
}
