typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    short id;
} HitObject;
typedef struct {
    HitObject *object;
    char pad4[36 - 4];
} Hit;
typedef struct Pending Pending;
struct Pending {
    unsigned char kind;
    char pad1;
    unsigned short prev;
    int key;
    Pending *next;
};
typedef struct {
    unsigned char kind;
    char pad1;
    unsigned short prev;
    int x;
    char pad8[4];
    int z;
    char pad10[0x18 - 0x10];
    unsigned char mode;
    char pad19;
    unsigned short link;
} Node;
typedef struct {
    char pad0[0xC];
    int team;
    int probe_mask;
} Owner;
typedef struct {
    Pending *pending;
    unsigned short head;
    unsigned short count;
} Route;
typedef struct Tank Tank;
struct Tank {
    int id;
    char pad04[4];
    Vector position;
    char pad14[0x2C - 0x14];
    unsigned short heading;
    char pad2E[2];
    unsigned short turret;
    char pad32[0x9C - 0x32];
    int type;
    char padA0[0xC9 - 0xA0];
    unsigned char mode;
    char padCA[2];
    Tank *target;
    char padD0[0xF8 - 0xD0];
    Route route;
    char pad100[0x180 - 0x100];
    int flags;
    char pad184[0x208 - 0x184];
    Owner *owner;
    char pad20C[0x218 - 0x20C];
    int state;
};
typedef struct {
    char pad0[0xAA];
    unsigned short reach;
    char padAC[0xD0 - 0xAC];
} VehicleType;
extern VehicleType D_800A4EF4[];
extern short D_800C628C;
extern unsigned short func_80019D80(Vector *, Vector *, int, unsigned short, int, Hit *);
extern void func_80049680(Vector *, int, int);
extern void func_80049840(Vector *, Vector *);
extern int func_800495D8(Vector *, Vector *);
extern Node *func_8004A794(unsigned short);
extern unsigned short func_8004A694(void *, int);
extern void func_8004BF64(Tank *);
extern void func_8004CCE8(Tank *);
int abs(int);

static inline void gte_ldlzc(int value) {
    __asm__ volatile("mtc2 %0, $30\n\tnop\n\tnop" : : "r"(value));
}

static inline void gte_stlzc(int *result) {
    __asm__ volatile("swc2 $31, 0(%0)" : : "r"(result) : "memory");
}

static inline int leading_zeros(int value) {
    int count;

    gte_ldlzc(value);
    gte_stlzc(&count);
    return count;
}

static inline int fixed_div(int numerator, int denom) {
    register int denominator asm("$5") = denom;
    int negative;
    int n;
    int d;
    int n_zeros;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;
    int divisor;
    int result;

    negative = (numerator & 0x80000000) ^ (denominator & 0x80000000);
    __asm__("" : : "r"(negative));
    n = abs(numerator);
    d = abs(denominator);
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        n <<= n_zeros;
        d_zeros = leading_zeros(d);
        n_zeros = d_zeros - n_zeros;
        if (n_zeros >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                divisor = d >> scale;
            } else {
                divisor = d << -scale;
            }
            quotient = (unsigned int)n / divisor;
            quotient <<= n_zeros;
        } else {
            quotient = (unsigned int)n / (d >> -excess);
        }
    } else {
        n <<= 12;
        quotient = (unsigned int)n / denominator;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

static inline int probe_clear(Vector *from, Vector *to, int mask, unsigned short reach, int id, Hit *hit) {
    D_800C628C = 0;
    return func_80019D80(from, to, mask, reach, id, hit) == 0;
}

int func_8004C278(Tank *tank) {
    int result = 0;
    Tank *target;
    Route *route;
    int mask;
    unsigned short angle;
    Vector left;
    Vector right;
    Vector ahead;
    Vector *order[2];
    Hit hit;
    Node *first;
    Pending *second;
    unsigned short i;
    int near;

    if (!(tank->flags & 2)) {
        goto end;
    }
    if (tank->mode != 1) {
        goto end;
    }
    target = tank->target;
    if (target == 0) {
        goto end;
    }
    if (!(target->state & 1)) {
        goto end;
    }
    if (target->owner->team == tank->owner->team) {
        goto end;
    }
    route = &tank->route;
    mask = tank->owner->probe_mask | 0x2C700F;
    angle = target->heading + target->turret;
    func_80049680(&left, 0x3E8000, (unsigned short)(angle - 0x4000));
    func_80049680(&right, 0x3E8000, (unsigned short)(angle + 0x4000));
    func_80049840(&left, &target->position);
    func_80049840(&right, &target->position);
    func_80049680(&ahead, fixed_div(func_800495D8(&tank->position, &target->position), 0x2000), tank->heading);
    func_80049840(&ahead, &tank->position);
    if (func_800495D8(&ahead, &left) < func_800495D8(&ahead, &right)) {
        order[0] = &left;
        order[1] = &right;
    } else {
        order[0] = &right;
        order[1] = &left;
    }
    for (i = 0; i < 2; i++) {
        if (probe_clear(&tank->position, order[i], mask, D_800A4EF4[tank->type].reach, tank->id, &hit)) {
            near = 0;
            if (route->pending != 0) {
                first = func_8004A794(route->pending->prev);
                near = func_800495D8((Vector *)&first->x, order[i]) < 0x64000;
            }
            if (!near) {
                func_8004BF64(tank);
                route->head = func_8004A694(&first, 3);
                first->link = func_8004A694(&second, 4);
                first->prev = 0;
                first->x = order[i]->x;
                first->z = order[i]->z;
                first->mode = 3;
                second->prev = route->head;
                second->key = func_800495D8(&tank->position, order[i]);
                second->next = 0;
                route->count = 2;
                route->pending = second;
                func_8004CCE8(tank);
            }
            result = 1;
            break;
        }
    }
end:
    return result;
}
