typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    int x;
    int z;
    int dir_x;
    int dir_z;
    int radius;
} Area;
typedef struct {
    int state;
    Vector goal;
    Vector alt;
    char pad1C[0x20 - 0x1C];
    int speed;
    int time;
    int near;
    int far;
} Patrol;
typedef struct {
    char pad0[0x94];
    Area *area;
    char pad98[0x184 - 0x98];
    Patrol patrol;
    char pad1B4[0x218 - 0x1B4];
    int status;
} Tank;
extern int D_800D2FE0;
extern void func_8004E2AC(Tank *, int);
extern void func_80049638(Vector *, int);
extern void func_80049840(Vector *, Vector *);
extern unsigned int func_80086C84(void);
extern void func_800509F4(Tank *);
extern void func_8004E0BC(Tank *);
extern void func_8004D804(Tank *);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline void patrol_pick_alt(Tank *tank) {
    Area *area = tank->area;
    Vector offset;

    if (area != 0) {
        offset.x = area->dir_x;
        offset.z = area->dir_z;
        func_80049638(&offset, fixed_mul(func_80086C84() & 0xFFF, area->radius));
        tank->patrol.alt.x = area->x;
        tank->patrol.alt.z = area->z;
        func_80049840(&tank->patrol.alt, &offset);
    }
}

void func_8004F388(Tank *tank) {
    Area *area;
    Patrol *patrol;
    Vector center;
    Vector dir;

    tank->status |= 0x100;
    area = tank->area;
    if (area == 0) {
        func_8004E2AC(tank, 4);
        return;
    }
    center.x = area->x;
    center.z = area->z;
    tank->patrol.state = 1;
    dir.x = area->dir_x;
    dir.z = area->dir_z;
    patrol = &tank->patrol;
    func_80049638(&dir, area->radius);
    patrol->goal.x = center.x;
    patrol->goal.z = center.z;
    func_80049840(&tank->patrol.goal, &dir);
    patrol_pick_alt(tank);
    func_800509F4(tank);
    patrol->speed = 819;
    patrol->time = D_800D2FE0 + 10;
    patrol->near = fixed_mul(2048, area->radius);
    patrol->far = fixed_mul(6144, area->radius);
    func_8004E0BC(tank);
    func_8004D804(tank);
}
