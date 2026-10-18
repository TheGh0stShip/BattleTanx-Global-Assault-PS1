typedef struct { char pad[12]; int team; } Owner;
typedef struct { char pad[0x208]; Owner *owner; } Tank;
typedef struct { char pad[24]; unsigned char index; } Ref;
typedef struct { char pad[12]; int team; char rest[0x114 - 16]; } Waypoint;
extern Waypoint D_800E3E68[];
void func_80033894(Tank *, Ref *);

static inline Waypoint *waypoint_at(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_80033F64(Tank *tank, Ref *ref) {
    Owner *owner = tank->owner;

    if (owner->team == waypoint_at(ref->index)->team) {
        func_80033894(tank, ref);
    }
}
