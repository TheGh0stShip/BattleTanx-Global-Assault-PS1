typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    int x;
    int z;
} Point2;
typedef struct {
    char pad0[0xA8];
    Point2 *rally;
} Owner;
typedef struct {
    char pad0[0xAC];
    unsigned int enemy_mask;
    unsigned int friend_mask;
    char padB4[0x180 - 0xB4];
    int flags;
    unsigned int state;
    char pad188[0x1FC - 0x188];
    int value;
    char pad200[0x208 - 0x200];
    Owner *owner;
    int saved;
    int current;
} Tank;
extern unsigned int D_800E3CC0;
extern unsigned int D_800D2FE8;
extern void func_8004E160(Tank *, Vector *, int, int);
extern void func_8004E2AC(Tank *, int);

void func_8004F050(Tank *tank) {
    Vector goal;
    unsigned int *state = &tank->state;

    switch (tank->state) {
    case 1:
        goal.x = tank->owner->rally->x;
        goal.z = tank->owner->rally->z;
        func_8004E160(tank, &goal, 100 << 12, 1);
        tank->state = 2;
        break;
    case 2:
        if ((D_800E3CC0 & (tank->friend_mask | tank->enemy_mask)) == 0) {
            tank->state = 3;
        } else if (tank->flags & 1) {
            tank->state = 4;
        }
        break;
    case 3:
        if (D_800D2FE8 < 7) {
            tank->value >>= 1;
        } else if (D_800D2FE8 < 15) {
            tank->current = tank->saved;
        }
        *state = 4;
        break;
    case 4:
        func_8004E2AC(tank, 6);
        break;
    }
}
