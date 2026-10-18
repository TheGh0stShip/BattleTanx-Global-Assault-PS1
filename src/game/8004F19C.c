typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    int x;
    int z;
} Area;
typedef struct {
    int state;
    Vector goal;
    Vector alt;
    char pad1C[0x2C - 0x1C];
    int far;
} Patrol;
typedef struct Tank Tank;
struct Tank {
    char pad0[8];
    Vector position;
    char pad14[0x94 - 0x14];
    Area *area;
    char pad98[0xA8 - 0x98];
    unsigned int bits;
    unsigned int enemy_mask;
    unsigned int friend_mask;
    char padB4[0x184 - 0xB4];
    Patrol patrol;
    char pad1B4[0x598 - 0x1B4];
};
extern Tank D_800DE33C[];
extern unsigned short func_80049E4C(unsigned int);
extern int func_800495D8(Vector *, Vector *);

static inline Tank *find_intruder(Tank *tank, unsigned int mask) {
    Tank *best = 0;
    int best_dist = 0xFA00000;
    Vector center;
    Patrol *patrol;
    Area *area;
    Tank *other;
    int dist;
    int near;

    area = tank->area;
    center.x = area->x;
    center.z = area->z;
    patrol = &tank->patrol;
    while (mask != 0) {
        other = &D_800DE33C[func_80049E4C(mask)];
        mask ^= other->bits;
        dist = func_800495D8(&other->position, &center) + func_800495D8(&other->position, &patrol->goal);
        if (dist <= patrol->far) {
            near = func_800495D8(&other->position, &tank->position);
            if (near < best_dist) {
                best = other;
                best_dist = near;
            }
        }
    }
    return best;
}

Tank *func_8004F19C(Tank *tank) {
    Tank *found = find_intruder(tank, tank->friend_mask);

    if (found == 0) {
        found = find_intruder(tank, tank->enemy_mask);
    }
    return found;
}
