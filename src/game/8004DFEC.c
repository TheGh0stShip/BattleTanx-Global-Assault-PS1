typedef unsigned char u8;
typedef signed short s16;

typedef struct TargetObject {
    u8 pad_00[4];
    s16 type;
    u8 pad_06[0x18 - 6];
    s16 health;
} TargetObject;

typedef struct Vehicle {
    u8 pad_000[0xC9];
    u8 target_kind;
    u8 pad_0CA[2];
    void *target;
} Vehicle;

extern int func_80047658(void *target);
extern int func_80047688(void *target);

void *func_8004DFEC(Vehicle *vehicle) {
    void *result = 0;

    switch (vehicle->target_kind) {
    case 2:
        result = &vehicle->target;
        break;
    case 1: {
        void *target = vehicle->target;

        if (func_80047658(target) && func_80047688(target)) {
            result = (u8 *)target + 0x170;
        }
        break;
    }
    case 3: {
        TargetObject *target = vehicle->target;

        if (target != 0 && target->type == 30 && target->health > 0) {
            result = (u8 *)target + 8;
        }
        break;
    }
    }
    return result;
}
