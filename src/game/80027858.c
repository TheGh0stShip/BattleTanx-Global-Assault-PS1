typedef struct {
    char pad0[0x18];
    unsigned char owner;
    char pad19[0x40 - 0x19];
} Node;

typedef struct {
    char pad0[0x114];
} Waypoint;

typedef struct {
    int x;
    int z;
    int radius_sq;
    int a;
    int b;
    int damage;
} Blast;

typedef struct {
    char pad0[8];
    int pos[3];
    unsigned short angle;
    signed char health;
    unsigned char state;
    char pad18[0x30 - 0x18];
    int effect;
    char pad34[0x3A - 0x34];
    short link;
} Crate;

extern int D_800D5A80;
extern Node *D_800D3258;
extern Waypoint D_800E3E68[];
extern int func_8008AE30(int, int);
extern void func_80035878(int, int *, int, int, int);
extern void func_8002688C(Crate *);
extern void func_800531D4(Waypoint *, int);
int abs(int);

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

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

static inline int fixed_div(int numerator, int denominator) {
    int negative;
    int n;
    int d;
    int n_zeros;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;
    int result;

    negative = (numerator & 0x80000000) ^ (denominator & 0x80000000);
    n = abs(numerator);
    d = abs(denominator);
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        quotient = n << n_zeros;
        d_zeros = leading_zeros(d);
        n_zeros = d_zeros - n_zeros;
        if (n_zeros >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                quotient = quotient / (d >> scale);
            } else {
                quotient = quotient / (d << -scale);
            }
            quotient <<= n_zeros;
        } else {
            quotient = quotient / (d >> -excess);
        }
    } else {
        quotient = n << 12;
        quotient = quotient / d;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

static inline Waypoint *waypoint_get(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_80027858(Crate *c, int unused, Blast *b) {
    int angle;
    int dx;
    int dz;
    int dist;
    int range;

    angle = (func_8008AE30(c->pos[0] - b->x, c->pos[2] - b->z) & 0xFFF) << 4;
    dx = fixed_to_int(c->pos[0] - b->x);
    dz = fixed_to_int(c->pos[2] - b->z);
    dist = dx * dx + dz * dz;
    if (dist > D_800D5A80) {
        return;
    }
    switch (c->state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 5:
        if (b->damage != 250) {
            if (c->health < b->damage) {
                c->health = 0;
            } else {
                c->health -= b->damage;
            }
        } else {
            range = D_800D5A80;
            if (dist < fixed_mul(819, range)) {
                func_8002688C(c);
            } else if (dist < fixed_mul(1638, range)) {
                func_80035878(c->effect, c->pos, c->angle, angle, 0);
                func_8002688C(c);
            } else if (dist < fixed_mul(2457, range)) {
                func_80035878(c->effect, c->pos, c->angle, angle, 0);
                if (c->link != -1) {
                    func_800531D4(waypoint_get(((Node *)((char *)D_800D3258 + (c->link << 6)))->owner), 9);
                }
                c->state = 5;
                c->health = -1;
            } else if (dist < fixed_mul(3276, range)) {
                if (c->health < b->damage) {
                    c->health = 0;
                } else {
                    c->health -= b->damage;
                }
            } else {
                int n = (range - dist) * 5;

                if (range == 0) {
                    range = 2;
                }
                c->health -= fixed_mul(15, fixed_div(n, range));
            }
        }
        break;
    case 6:
        if (b->damage == 250) {
            range = D_800D5A80;
            if (dist < fixed_mul(819, range)) {
                func_8002688C(c);
            } else if (dist < fixed_mul(1638, range)) {
                func_8002688C(c);
            } else if (dist < fixed_mul(2457, range)) {
            } else if (dist < fixed_mul(3276, range)) {
            }
        }
        break;
    }
}
