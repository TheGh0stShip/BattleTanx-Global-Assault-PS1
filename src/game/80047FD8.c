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

typedef struct GameRules {
    char pad00[0xD];
    unsigned char player_count;
} GameRules;

extern GameRules D_800D2FE0;
extern char *D_800A5B24;

WaypointRef *func_80047DD4(WaypointStack *stack, unsigned short index);

WaypointRef *func_80047FD8(WaypointStack *stack) {
    WaypointRef *ref;

    if (stack->done) {
        stack->depth++;
        if (stack->depth >= D_800D2FE0.player_count) {
            if (stack->depth == D_800D2FE0.player_count) {
                return (WaypointRef *)(D_800A5B24 + 0xE06C);
            }
            stack->depth = 0;
        }
        ref = func_80047DD4(stack, stack->depth);
    } else {
        stack->done = 1;
        ref = &stack->refs[stack->depth];
        if (!waypoint_ref_valid(ref)) {
            ref = waypoint_ref_reset(stack, stack->depth);
        }
    }
    return ref;
}
