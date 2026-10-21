typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    char pad0[0xB4];
    int slots[2];
} Owner;
typedef struct {
    char pad0[8];
    Vector position;
    char pad14[0xD8 - 0x14];
    Vector target;
    char padE4[0xF0 - 0xE4];
    unsigned char has_target;
    char padF1[0x1F0 - 0xF1];
    int range;
    char pad1F4[0x200 - 0x1F4];
    int chance;
    char pad204[0x208 - 0x204];
    Owner *owner;
} Tank;
extern int func_800495D8(Vector *, Vector *);
extern unsigned int func_80086C84(void);

static inline int slot_weapon(int slot, int dist) {
    int weapon;

    switch (slot) {
    case 1:
        return 2;
    case 2:
        return 3;
    case 3:
        return 4;
    case 10:
        return 9;
    case 14:
        weapon = 0;
        if (dist <= 0x3E8000) {
            weapon = 12;
        }
        return weapon;
    case 16:
        weapon = 0;
        if (dist <= 0x7D0000) {
            weapon = 14;
        }
        return weapon;
    }
    return 0;
}

static inline Vector *tank_target(Tank *tank) {
    if (tank->has_target) {
        return &tank->target;
    }
    return 0;
}

int func_8004D510(Tank *tank) {
    int result = 1;
    int dist;
    unsigned int first;
    int second;
    int *slots;

    dist = func_800495D8(&tank->position, tank_target(tank));
    if (dist <= tank->range) {
        if ((int)(func_80086C84() & 0xFFF) < tank->chance) {
        slots = tank->owner->slots;
        if (func_80086C84() & 1) {
            first = slot_weapon(slots[0], dist);
            second = slot_weapon(slots[1], dist);
        } else {
            first = slot_weapon(slots[1], dist);
            second = slot_weapon(slots[0], dist);
        }
if (first == 0) {
            result = second;
            if (result == 0) {
                result = 1;
            }
        } else {
            result = first;
        }

        }
    } else {
        result = 0;
    }
    return result;
}
