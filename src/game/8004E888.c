typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct WorldObject WorldObject;
struct WorldObject {
    char pad0[8];
    Vector position;
    char pad14[0x18 - 0x14];
    short health;
};
typedef struct {
    char pad0[0x14];
    int mode;
    char pad18[0x52 - 0x18];
    unsigned char hold;
} Owner;
typedef struct {
    int state;
    int flag;
} Block;
typedef struct {
    char pad0[8];
    Vector position;
    char pad14[0x184 - 0x14];
    Block block;
    char pad18C[0x208 - 0x18C];
    Owner *owner;
} Tank;
extern WorldObject *func_80023870(WorldObject *, int);
extern int func_800495D8(Vector *, Vector *);
extern void func_8004E254(Tank *, WorldObject *, int, int);
extern void func_8004D88C(Tank *, WorldObject *);
extern void func_8004DD5C(Tank *);
extern void func_8004D804(Tank *);
extern void func_8004E2AC(Tank *, int);

void func_8004E888(Tank *tank) {
    Block *block = &tank->block;
    Owner *owner;
    WorldObject *obj;
    WorldObject *best;
    int best_dist;
    int dist;

    switch (block->state) {
    case 1:
        owner = tank->owner;
        if (owner->mode == 7 && (owner->hold != 0 || block->flag == 0)) {
            best = 0;
            best_dist = 0;
            for (obj = func_80023870(0, 30); obj != 0; obj = func_80023870(obj, 30)) {
                if (obj->health > 0) {
                    dist = func_800495D8(&tank->position, &obj->position);
                    if (best == 0 || dist < best_dist) {
                        best = obj;
                        best_dist = dist;
                    }
                }
            }
            if (best != 0) {
                func_8004E254(tank, best, 0x190000, 0);
                func_8004D88C(tank, best);
                block->state = 2;
            }
        } else {
            func_8004DD5C(tank);
        }
        break;
    case 2:
        if (tank->owner->mode != 7) {
            func_8004E2AC(tank, 6);
        }
        if (block->flag != 0 && tank->owner->hold == 0) {
            func_8004DD5C(tank);
            func_8004D804(tank);
            tank->block.state = 1;
        }
        break;
    }
}
