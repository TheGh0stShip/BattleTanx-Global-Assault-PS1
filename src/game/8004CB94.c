typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;

typedef struct HitObject {
    short id;
    short pad02;
    short kind;
} HitObject;

typedef struct Hit {
    HitObject *object;
    u8 pad04[0x20 - 4];
    u16 value;
    u8 pad22[0x28 - 0x22];
} Hit;

typedef struct SmallState {
    int value;
    u16 index;
    u8 mode;
} SmallState;

typedef struct Owner {
    u8 pad00[0x10];
    int probe_mask;
} Owner;

typedef struct Tank {
    int id;
    u8 pad04[4];
    Vector position;
    u8 pad14[0xFC - 0x14];
    u16 route;
    u8 padFE[0x134 - 0xFE];
    int target_id;
    u8 pad138[0x148 - 0x138];
    u16 route_seen;
    u8 pad14A[0x208 - 0x14A];
    Owner *owner;
} Tank;

extern short D_800C628C;
extern Vector *func_8004CFB4(Tank *tank);
extern u16 func_80049560(Tank *tank, int primary);
extern u16 func_80019D80(Vector *from, Vector *to, int mask, u16 reach,
                         int ignore, Hit *hit);
extern int func_80049374(u16 value);
extern void func_80049384(SmallState *state, Hit *hit);
extern int func_8004C970(Tank *tank, SmallState *state);

static inline short hit_kind(HitObject **object)
{
    return (*object)->kind;
}

int func_8004CB94(Tank *tank)
{
    Hit hit;
    SmallState state;
    register int result asm("$18") = 0;
    register int probe_mask asm("$19") = tank->owner->probe_mask;
    register u8 *route asm("$20") = (u8 *)tank + 0xF8;
    register Vector *goal asm("$16");

    goal = func_8004CFB4(tank);
    if (goal == 0) {
        register unsigned int seen asm("$3") = tank->route_seen;
        if (seen == tank->route) {
            result = (unsigned int)result < seen;
        }
        goto done;
    }

    {
        u16 reach = func_80049560(tank, 1);
        D_800C628C = 0;
        if (func_80019D80(&tank->position, goal,
                          probe_mask + 0x2C700F, reach,
                          tank->id, &hit) == 0) {
            result = 1;
            goto done;
        }
    }

    if (*(int *)(route + 0x3C) != 0) {
        if (hit.object != 0 && hit.object->id == *(int *)(route + 0x3C)) {
            result = 1;
            goto done;
        }
    }
    if (func_80049374(hit.value) != 0) {
        if (hit.object != 0 && hit_kind(&hit.object) == 4) {
            register SmallState *point asm("$16") = &state;
            __asm__("" : "+r"(point));
            func_80049384(point, &hit);
            result = func_8004C970(tank, point);
        }
    }
done:
    return result;
}
