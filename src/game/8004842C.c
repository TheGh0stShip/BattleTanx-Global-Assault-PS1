typedef struct WaypointObject {
    short serial;
    short pad02;
    short type;
    short pad06;
    void *link;
} WaypointObject;

typedef struct WaypointRef {
    WaypointObject *object;
    int serial;
} WaypointRef;

typedef struct WaypointStack {
    unsigned char active;
    unsigned char done;
    unsigned short depth;
    WaypointRef refs[5];
} WaypointStack;

typedef struct UnitSlot {
    short serial;
    char pad02[0x114 - 0x2];
} UnitSlot;

extern UnitSlot D_800E3E68[];

static inline WaypointObject *waypoint_from_index(unsigned int index) {
    if (index == 127) {
        return 0;
    }
    return (WaypointObject *)&D_800E3E68[index];
}

static inline int waypoint_ref_valid(WaypointRef *ref) {
    WaypointObject *object = ref->object;

    if (object == 0 || object->serial != ref->serial) {
        return 0;
    }
    switch (object->type) {
    case 76:
        return 1;
    case 4:
        return object->link != 0;
    }
    return 0;
}

static inline WaypointRef *waypoint_ref_reset(WaypointStack *stack, unsigned short index) {
    WaypointObject *fallback = waypoint_from_index(index);
    WaypointRef *ref = &stack->refs[index];

    ref->object = fallback;
    ref->serial = fallback->serial;
    return ref;
}

typedef struct World {
    short serial;
    short pad02;
    short type;
    short pad06;
    char steps[0xE014 - 0x8];
    WaypointStack first;
    WaypointStack second;
    WaypointRef current;
    unsigned char flag;
    unsigned char pad075;
    unsigned short count;
    int team;
} World;

extern World *D_800A5B24;

extern int D_800A48DC;

void *func_80068DA4(int size);
void func_80049F84(void *steps);

static inline void waypoint_ref_clear(WaypointRef *ref) {
    ref->object = 0;
    ref->serial = 0;
}

static inline void waypoint_stack_reset(WaypointStack *stack) {
    unsigned short i;

    stack->active = 1;
    stack->done = 0;
    stack->depth = 0;
    for (i = 0; i < 5; i++) {
        waypoint_ref_clear(&stack->refs[i]);
    }
}

static inline void world_init(World *world) {
    world->serial = 0;
    world->pad02 = 0;
    world->type = 5;
    func_80049F84(world->steps);
    waypoint_stack_reset(&world->first);
    waypoint_stack_reset(&world->second);
    waypoint_ref_clear(&world->current);
    world->current.object = (WaypointObject *)world;
    world->flag = 0;
    world->count = 0;
    world->team = 0;
}

void func_8004842C(void) {
    if (D_800A48DC == 0) {
        D_800A5B24 = func_80068DA4(sizeof(World));
    }
    if (D_800A5B24 != 0) {
        world_init(D_800A5B24);
    }
}
