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


static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int fixed_div(int numerator, int denominator) {
    int negative;
    unsigned int n;
    int d;
    unsigned int m;
    int n_zeros;
    int d_zeros;
    register int excess asm("$6");
    int scale;
    unsigned int quotient;
    int result;

    negative = (numerator & 0x80000000) ^ (denominator & 0x80000000);
    n = abs(numerator);
    d = abs(denominator);
    __asm__ volatile("" : "+r"(d));
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        m = n << n_zeros;
        d_zeros = leading_zeros(d);
        n_zeros = d_zeros - n_zeros;
        if (n_zeros >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                quotient = m / (d >> scale);
            } else {
                quotient = m / (d << -scale);
            }
            quotient <<= n_zeros;
        } else {
            scale = -excess;
            quotient = m / (d >> scale);
        }
    } else {
        m = n << 12;
        quotient = m / denominator;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}


typedef struct { int x, y, z; } Vector;
typedef struct { char pad[536]; int flags; } Unit;
typedef struct { int pad[2]; Unit *unit; } Owner;
typedef struct {
    int pad[2];
    Vector pos;
    int kind;
    int scale_x;
    int scale_y;
    int timer;
    int speed;
    short angle;
    unsigned char size;
    unsigned char flags;
    unsigned char slot;
    char pad2d[3];
    Owner *owner;
    int emitter0;
    int emitter1;
} Effect;
typedef struct { char pad[0x114]; } Waypoint;
extern Waypoint D_800E3E68[];
Effect *func_800237D0(int, int);
void func_80052A60(Waypoint *, Effect *, int);
int func_8006C334(Effect *, int, Vector *, Vector *, int, int, int, int);

Effect *func_8002C584(Vector *pos, int kind, short angle, unsigned char size, unsigned char slot, Owner *owner, unsigned char attach) {
    Effect *e;
    int scale;
    Vector min;
    Vector max;
    Waypoint *wp;

    e = func_800237D0(12, 60);
    if (e == 0) {
        return 0;
    }
    e->pos.x = pos->x;
    e->pos.y = pos->y;
    e->pos.z = pos->z;
    e->scale_x = 16384;
    e->scale_y = 16384;
    e->flags = 1;
    e->kind = kind;
    e->size = size;
    e->angle = angle;
    {
        register int speed asm("$3") = 0x3E8000;
        e->speed = speed;
    }
    e->slot = slot;
    e->timer = 0;
    if (attach && (owner->unit->flags & 2)) {
        e->flags = 5;
        if (slot == 127) {
            wp = 0;
        } else {
            wp = &D_800E3E68[slot];
        }
        func_80052A60(wp, e, 0);
    }
    e->owner = owner;
    scale = (fixed_div(size, 50) + 4096) / 2;
    min.x = fixed_mul(scale, -0x10000);
    min.y = fixed_mul(scale, -0x10000);
    min.z = fixed_mul(scale, -0x10000);
    max.x = fixed_mul(scale, 0x10000);
    max.y = fixed_mul(scale, 0x10000);
    max.z = fixed_mul(scale, 0x10000);
    e->emitter0 = func_8006C334(e, 0, &min, &max, 0, fixed_mul(scale, 5120), 6144, 0x7FFFFFFF);
    e->emitter1 = func_8006C334(e, 1, &min, &max, 0, fixed_mul(scale, 5120), 4096, 0x7FFFFFFF);
    return e;
}
