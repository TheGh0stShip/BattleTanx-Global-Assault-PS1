typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    char pad0[0xC];
    int team;
    char pad10[0x114 - 0x10];
} RuntimeObject;
typedef struct {
    char pad0[0x17];
    unsigned char kind;
} ObjectInfo;
typedef struct {
    char pad0[8];
    int alive;
    Vector position;
    unsigned char waypoint;
    char pad19[3];
    ObjectInfo *info;
} WorldObject;
typedef struct {
    int state;
    WorldObject *object;
    int pad8;
    int time;
} Capture;
typedef struct {
    char pad0[0xC];
    int team;
} Owner;
typedef struct {
    int id;
    char pad04[4];
    Vector position;
    char pad14[0x98 - 0x14];
    int home;
    char pad9C[0xA4 - 0x9C];
    void *active;
    char padA8[0x184 - 0xA8];
    Capture capture;
    char pad194[0x1F0 - 0x194];
    int range;
    char pad1F4[0x208 - 0x1F4];
    Owner *owner;
} Tank;
typedef struct {
    char data[40];
} Hit;
extern RuntimeObject D_800E3E68[];
extern int D_800D2FE0;
extern short D_800C628C;
extern WorldObject *func_80023870(WorldObject *, int);
extern void func_8004E160(Tank *, Vector *, int, int);
extern void func_8004E2AC(Tank *, int);
extern unsigned short func_80019D80(Vector *, Vector *, int, int, int, Hit *);
extern int func_800495D8(Vector *, Vector *);
extern void func_8004D838(Tank *, WorldObject *);

static inline int object_alive(WorldObject *obj) {
    return obj != 0 && obj->alive != 0;
}

static inline RuntimeObject *waypoint_lookup(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

static inline int is_base(WorldObject *obj) {
    return obj->info->kind == 7;
}

static inline int at_base(Tank *tank, WorldObject *obj) {
    if (!is_base(obj)) {
        return 0;
    }
    return func_800495D8(&tank->position, &obj->position) <= 0x12C000;
}

static inline WorldObject *find_home(Tank *tank) {
    register WorldObject *obj asm("$5");
    for (obj = func_80023870(0, 21); obj != 0; obj = func_80023870(obj, 21)) {
        if (obj->waypoint == tank->home) {
            return obj;
        }
    }
    return obj;
}

void func_8004ED14(Tank *tank) {
    Capture *cap = &tank->capture;
    WorldObject *obj;
    RuntimeObject *wp;
    Hit hit;
    int now;

    switch (tank->capture.state) {
    case 1:
        for (obj = func_80023870(0, 21); obj != 0; obj = func_80023870(obj, 21)) {
            wp = waypoint_lookup(obj->waypoint);
            if (wp->team != tank->owner->team && obj->alive != 0) {
                break;
            }
        }
        cap->object = obj;
        if (tank->active != 0) {
            cap->state = 4;
        } else if (obj != 0) {
            func_8004E160(tank, &obj->position, 0, 1);
            cap->state = 2;
        } else {
            func_8004E2AC(tank, 6);
        }
        break;
    case 2:
        if (tank->active != 0) {
            cap->state = 4;
            break;
        }
        if (!object_alive(cap->object)) {
            cap->state = 1;
            break;
        }
        if (cap->time > D_800D2FE0) {
            break;
        }
        cap->time = D_800D2FE0 + 30;
        obj = cap->object;
        if (is_base(obj)) {
            break;
        }
        D_800C628C = 0;
        if (func_80019D80(&tank->position, &obj->position, 0x241009, 0, tank->id, &hit) != 0) {
            break;
        }
        if (func_800495D8(&tank->position, &cap->object->position) > tank->range) {
            break;
        }
        func_8004D838(tank, cap->object);
        cap->state = 3;
        break;
    case 3:
        if (tank->active == 0) {
            if (!object_alive(cap->object)) {
                cap->state = 1;
            }
        } else {
            cap->state = 4;
        }
        break;
    case 4:
        obj = cap->object;
        if (object_alive(obj) && at_base(tank, obj)) {
            break;
        }
        obj = find_home(tank);
        if (obj != 0) {
            func_8004E160(tank, &obj->position, 0, 1);
            cap->state = 5;
        } else {
            func_8004E2AC(tank, 6);
        }
        break;
    case 5:
        if (tank->active == 0) {
            cap->state = 6;
        }
        break;
    case 6:
        func_8004E2AC(tank, 6);
        break;
    }
}
