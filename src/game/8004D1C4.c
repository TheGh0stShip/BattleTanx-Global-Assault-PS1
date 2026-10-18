typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct Tank Tank;
typedef struct {
    char pad0[4];
    short kind;
    char pad6[2];
    int x;
    int y;
    int z;
    char pad14[4];
    short health;
} Object;
typedef struct {
    Vector position;
    char padC[0x18 - 0xC];
    unsigned char valid;
    unsigned char mode;
    char pad1A[2];
    Tank *target;
} Track;
struct Tank {
    char pad0[8];
    int x;
    int y;
    int z;
    char pad14[0xA8 - 0x14];
    unsigned int bits;
    unsigned int enemy_mask;
    char padB0[4];
    Tank *other;
    char padB8[0xD8 - 0xB8];
    Track track;
    char padF8[0x170 - 0xF8];
    Vector eye;
};
extern unsigned int D_800E3CC0;
extern int func_80050338(void *);
extern int func_80050354(void *);
extern int func_80047658(Tank *);
extern int func_8004D968(Tank *, Tank *);
extern Tank *func_80049E70(unsigned int);
extern void func_8004D804(Tank *);

void func_8004D1C4(Tank *tank) {
    Track *track = &tank->track;
    Tank *other;
    Object *obj;

    track->valid = 0;
    switch (track->mode) {
    case 0:
        return;
    case 5:
    case 6:
        switch (track->mode) {
        case 5:
            other = track->target;
            if (func_80050338(other) != 0 && func_80050354(other) == 0) {
                track->valid = 1;
            }
            break;
        case 6:
            obj = (Object *)track->target;
            if (obj != 0 && obj->kind == 30 && obj->health > 0) {
                track->position.x = obj->x;
                track->position.z = obj->z;
                track->valid = 1;
            }
            break;
        }
        if (track->valid != 0) {
            return;
        }
    case 1:
    case 2:
    case 3:
    case 4:
        break;
    default:
        return;
    }
    if (func_80047658(tank) != 0 && (tank->enemy_mask != 0 || tank->other != 0)) {
        switch (track->mode) {
        case 2:
            other = track->target;
            if (other != 0 && (other->bits & tank->enemy_mask) && func_80047658(other) != 0) {
                track->position.x = other->eye.x;
                track->position.z = other->eye.z;
                track->valid = 1;
            }
            break;
        case 3:
            other = track->target;
            if ((other->bits & tank->enemy_mask) && func_80047658(other) != 0) {
                track->position.x = other->eye.x;
                track->position.z = other->eye.z;
                track->valid = 1;
            }
            break;
        case 4:
            other = track->target;
            if (func_8004D968(tank, other) != 0) {
                track->position.x = other->x;
                track->position.z = other->z;
                track->valid = 1;
            }
            break;
        case 1:
        case 5:
        case 6:
            break;
        }
        if (track->valid != 0) {
            return;
        }
        if (tank->enemy_mask != 0) {
            other = func_80049E70(tank->enemy_mask & D_800E3CC0);
            if (func_80047658(other) != 0) {
                track->mode = 3;
            } else {
                other = func_80049E70(tank->enemy_mask & ~D_800E3CC0);
                if (func_80047658(other) == 0) {
                    goto skip;
                }
                track->mode = 2;
            }
            track->target = other;
            track->position.x = other->eye.x;
            track->position.z = other->eye.z;
            track->valid = 1;
        }
    skip:
        if (track->valid != 0) {
            return;
        }
        other = tank->other;
        if (func_8004D968(tank, other) != 0) {
            track->mode = 4;
            track->target = other;
            track->position.x = other->x;
            track->position.z = other->z;
            track->valid = 1;
        } else {
            tank->other = 0;
        }
    }
    if (track->valid == 0 && track->mode != 1) {
        func_8004D804(tank);
    }
}
