typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    short x;
    short y;
    short z;
    short pad;
} SVector;
typedef struct {
    short id;
} HitObject;
typedef struct {
    HitObject *object;
    char pad4[4];
    Vector position;
    char pad14[12];
    unsigned short surface;
    char pad22[6];
} Hit;
typedef struct {
    unsigned char kind;
    char pad1;
    short current;
    int x;
    int pad8;
    int z;
    SVector point;
    unsigned char mode;
} Move;
typedef struct {
    int state;
    unsigned short head;
    unsigned short count;
    char pad8[2];
    unsigned short current;
    char padC[8];
    unsigned short a14;
    unsigned short a16;
    int a18;
    int mode;
    char pad20[4];
    Vector from;
    Vector goal;
    int ignore_id;
    int width;
} Route;
typedef struct {
    int id;
    char pad04[0xF8 - 4];
    Route route;
    char pad13C[0x14A - 0x13C];
    unsigned short route_seen2;
    char pad14C[0x180 - 0x14C];
    int flags;
} Tank;
extern short D_800C628C;
extern int func_8004A160(unsigned short *, int);
extern int func_80049560(Tank *, int);
extern unsigned short func_80019D80(Vector *, Vector *, int, int, int, Hit *);
extern unsigned short func_8004A694(Move **, int);
extern void func_80049384(SVector *, Hit *);
extern void func_80049468(SVector *, int, Vector *, Vector *);
extern int func_800495D8(Vector *, Vector *);
extern void func_8004986C(int *, Vector *, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

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


int abs(int);

static inline int fixed_div(int numerator, int denominator) {
    int negative;
    int n;
    int sign;
    int d;
    int n_zeros;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;
    int result;

    sign = numerator & 0x80000000;
    negative = sign ^ (denominator & 0x80000000);
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
                quotient = (unsigned int)n / (d >> scale);
            } else {
                quotient = (unsigned int)n / (d << -scale);
            }
            quotient <<= n_zeros;
        } else {
            quotient = (unsigned int)n / (d >> -excess);
        }
    } else {
        n <<= 12;
        quotient = (unsigned int)n / d;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

void func_8004AF4C(Tank *tank) {
    Route *route = &tank->route;
    Hit hit;
    Vector near;
    Vector far;
    Move *move;
    unsigned short reach;
    int d_near;
    int sum;
    int t;

    tank->route_seen2 = 0;
    func_8004A160(&route->head, 0);
    route->count = 0;
    tank->route.state = 0;
    route->current = 0;
    route->a14 = 0;
    route->a16 = 0;
    route->a18 = 0;
    tank->flags &= ~0x180;
    reach = func_80049560(tank, 0);
    D_800C628C = 0;
    if (func_80019D80(&route->from, &route->goal, 0x87007, reach, tank->id, &hit) != 0
        && !(route->ignore_id != 0 && hit.object != 0 && route->ignore_id == hit.object->id)) {
        if (hit.surface == 7) {
            route->head = 0;
            route->mode = 2;
            return;
        }
        route->head = func_8004A694(&move, 3);
        route->count++;
        move->mode = 0;
        move->current = 0;
        func_80049384(&move->point, &hit);
        if (tank->flags & 8) {
            func_80049468(&move->point, route->width, &far, &near);
            d_near = func_800495D8(&route->from, &near);
            sum = d_near + func_800495D8(&route->from, &far);
            if (sum == 0) {
                sum = 2;
            }
            t = fixed_div(d_near, sum);
            move->x = fixed_mul(0x1000 - t, near.x) + fixed_mul(t, far.x);
            move->z = fixed_mul(0x1000 - t, near.z) + fixed_mul(t, far.z);
        } else {
            move->x = hit.position.x;
            move->z = hit.position.z;
            func_8004986C(&move->x, &route->from, route->width);
        }
    } else if (func_800495D8(&route->from, &route->goal) > route->width) {
        route->head = func_8004A694(&move, 3);
        route->count++;
        move->x = route->goal.x;
        move->z = route->goal.z;
        move->mode = 3;
        move->current = 0;
    } else {
        goto fail;
    }
    route->current = route->head;
    return;
fail:
    route->head = 0;
    move = 0;
}
