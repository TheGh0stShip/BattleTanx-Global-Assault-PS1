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
    unsigned int state;
    Vector goal;
    Vector alt;
    char pad1C[0x20 - 0x1C];
    int speed;
    int time;
    char pad28[0x30 - 0x28];
} Patrol;
typedef struct {
    char pad0[0xC];
    int team;
} Squad;
typedef struct Tank Tank;
struct Tank {
    char pad0[8];
    Vector position;
    char pad14[0x94 - 0x14];
    Area *area;
    char pad98[0xAC - 0x98];
    int hurried;
    char padB0[0x184 - 0xB0];
    Patrol patrol;
    char pad1B4[0x208 - 0x1B4];
    Squad *squad;
};
extern int D_800D2FE0;
extern void func_8004E2AC(Tank *, int);
extern Tank *func_8004F19C(Tank *);
extern void func_8004960C(Vector *, Vector *, Vector *);
extern void func_80049638(Vector *, int);
extern void func_80049840(Vector *, Vector *);
extern unsigned int func_80086C84(void);
extern int func_800509F4(Tank *);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline void vec_sub(Vector *out, Vector *from, Vector *to) {
    func_8004960C(out, from, to);
}

void func_8004F534(Tank *tank) {
    Patrol *patrol;
    Area *area;
    Area *zone;
    Area *field;
    Tank *other;
    Tank *intruder;
    Vector offset;
    Vector to_other;
    Vector to_self;
    Vector center;
    int other_side;
    int self_side;
    int lateral;
    Vector *alt;

    if (tank->area == 0) {
        func_8004E2AC(tank, 4);
        return;
    }
    patrol = &tank->patrol;
    switch (patrol->state) {
    case 1:
        patrol->state = 2;
        break;
    case 2:
        if (D_800D2FE0 >= patrol->time) {
            patrol->time = D_800D2FE0 + 10;
            intruder = func_8004F19C(tank);
            if (intruder != 0) {
                if (intruder->squad->team == tank->squad->team) {
                    patrol->state = 3;
                } else {
                    patrol->state = 4;
                }
                return;
            }
        }
        patrol->speed = tank->hurried != 0 ? 4096 : 819;
        if (func_800509F4(tank) != 0) {
            zone = tank->area;
            if (zone != 0) {
                offset.x = zone->dir_x;
                offset.z = zone->dir_z;
                func_80049638(&offset, fixed_mul(func_80086C84() & 0xFFF, zone->radius));
                tank->patrol.alt.x = zone->x;
                tank->patrol.alt.z = zone->z;
                func_80049840(&tank->patrol.alt, &offset);
            }
            func_800509F4(tank);
        }
        break;
    case 3:
        other = func_8004F19C(tank);
        if (other == 0 || other->squad->team != tank->squad->team) {
            patrol->state = 2;
            break;
        }
        area = tank->area;
        center.x = area->x;
        center.z = area->z;
        vec_sub(&to_other, &center, &other->position);
        other_side = fixed_mul(area->dir_x, to_other.x) + fixed_mul(area->dir_z, to_other.z);
        vec_sub(&to_self, &center, &tank->position);
        self_side = fixed_mul(area->dir_x, to_self.x) + fixed_mul(area->dir_z, to_self.z);
        if (other_side < self_side) {
            patrol->alt.x = patrol->goal.x;
            patrol->alt.z = patrol->goal.z;
        } else {
            patrol->alt.x = center.x;
            patrol->alt.z = center.z;
        }
        func_800509F4(tank);
        break;
    case 4:
        other = func_8004F19C(tank);
        if (other == 0 || other->squad->team == tank->squad->team) {
            patrol->state = 2;
            break;
        }
        field = tank->area;
        offset.x = field->x;
        offset.z = field->z;
        func_8004960C(&to_other, &offset, &other->position);
        lateral = fixed_mul(field->dir_x, to_other.x) + fixed_mul(field->dir_z, to_other.z);
        func_8004960C(&to_self, &offset, &tank->position);
        self_side = fixed_mul(field->dir_x, to_self.x) + fixed_mul(field->dir_z, to_self.z);
        alt = &tank->patrol.alt;
        alt->x = field->dir_x;
        alt->z = field->dir_z;
        func_80049638(alt, lateral);
        func_80049840(alt, &offset);
        func_800509F4(tank);
        break;
    }
}
