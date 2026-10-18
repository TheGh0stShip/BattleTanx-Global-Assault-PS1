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

void **func_80052F9C(WaypointObject *, void *, int, int);

WaypointRef *func_80047DD4(WaypointStack *stack, unsigned short index) {
    WaypointRef *ref = &stack->refs[index];
    WaypointObject *object;
    void **found;

    if (!waypoint_ref_valid(ref)) {
        return waypoint_ref_reset(stack, index);
    }
    object = waypoint_from_index(index);
    switch (ref->object->type) {
    case 76:
        found = func_80052F9C(object, 0, 1, 0);
        if (found == 0) {
            return waypoint_ref_reset(stack, index);
        }
        ref->object = (WaypointObject *)*found;
        ref->serial = ref->object->serial;
        return ref;
    case 4:
        found = func_80052F9C(object, ref->object->link, 1, 0);
        if (found == 0) {
            return waypoint_ref_reset(stack, index);
        }
        ref->object = *(WaypointObject **)((WaypointObject *)*found)->link;
        ref->serial = ref->object->serial;
        return ref;
    default:
        return waypoint_ref_reset(stack, index);
    }
}
