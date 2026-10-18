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

WaypointRef *func_80047FD8(WaypointStack *stack);
void func_80048548(WaypointObject *object);
void func_80048EE4(WaypointObject *object);
void func_80050CF8(WaypointObject *object);
void func_800499AC(void);

void func_8004866C(void) {
    WaypointObject *object;

    if (D_800A5B24 == 0) {
        return;
    }
    object = func_80047FD8(&D_800A5B24->first)->object;
    switch (object->type) {
    case 5:
        func_80048548(object);
        break;
    case 76:
        func_80050CF8(object);
        break;
    case 4:
        func_80048EE4(object);
        break;
    }
    func_800499AC();
}
