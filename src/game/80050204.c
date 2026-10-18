typedef struct Tank Tank;
struct Tank {
    char pad0[0xA4];
    void *active;
    char padA8[0xC9 - 0xA8];
    unsigned char mode;
    char padCA[2];
    Tank *mode_target;
    char padD0[0x1F4 - 0xD0];
    int weapon;
    char pad1F8[0x208 - 0x1F8];
    char *owner;
};
typedef struct {
    char pad[0xC];
    int type;
} WorldObject;

extern void func_8004E0FC(Tank *, Tank *, int, int);
extern WorldObject *func_80023870(int, int);
extern void func_8004E2AC(Tank *, int);

void func_80050204(Tank *tank) {
    Tank *target = 0;
    WorldObject *obj;
    char *mode;

    do { } while (0);

    if (tank->active != 0) {
        func_8004E2AC(tank, 20);
        return;
    }
    if (tank->mode == 1) {
        target = tank->mode_target;
    }
    if (target == 0) {
        mode = tank->owner + 0x10;
        if (*(int *)(mode + 4) == 3) {
            target = *(Tank **)(mode + 0x3C);
            func_8004E0FC(tank, target, tank->weapon, 1);
        }
        if (target == 0) {
            func_8004E2AC(tank, 6);
            return;
        }
    }
    if (target->active != 0) {
        return;
    }
    obj = func_80023870(0, 8);
    if (obj == 0) {
        func_8004E2AC(tank, 6);
        return;
    }
    if (obj->type == 1) {
        func_8004E2AC(tank, 18);
    } else {
        func_8004E2AC(tank, 6);
    }
}
