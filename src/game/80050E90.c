typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    char pad0[0x14];
    unsigned int state;
    char pad18[0x4C - 0x18];
    char *anchor;
} Owner;
typedef struct {
    char pad0[8];
    Vector position;
    char pad14[0x17C - 0x14];
    unsigned int state;
    char pad180[0x208 - 0x180];
    Owner *owner;
} Tank;
extern int func_80047658(Tank *);
extern int func_800495D8(Vector *, Vector *);

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


extern int abs(int);

static inline int abs_max(int a, int b) {
    int r = abs(a);

    b = abs(b);
    if (r < b) {
        r = b;
    }
    return r;
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
    int sign;
    int d;
    int n_zeros;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;

    sign = numerator & 0x80000000;
    negative = sign ^ (denominator & 0x80000000);
    __asm__("" : : "r"(negative));
    n = abs(numerator);
    d = denominator;

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
    if (negative) {
        quotient = -quotient;
    }
    return quotient;
}

int func_80050E90(Tank *tank, unsigned int target) {
    int result = 0;
    int ok;
    Vector *point;
    int v;
    register int weight asm("$9");

    __asm__("");
    ok = 0;
    if (func_80047658(tank) != 0) {
        switch (tank->state) {
        case 6:
        case 9:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
            ok = 1;
            break;
        default:
            ok = 0;
            break;
        }
    }
    if (ok != 0) {
        if (tank->state == target) {
            result = 4096;
        } else {
            Owner *o = tank->owner;

            point = 0;
            switch (o->state) {
            case 4:
                point = (Vector *)(o->anchor + 12);
                break;
            case 5:
                point = (Vector *)(o->anchor + 32);
                break;
            case 3:
            case 6:
                point = (Vector *)(o->anchor + 8);
                break;
            }
            v = 4096;
            if (point != 0) {
            {
                int num = 0x8000000 - func_800495D8(&tank->position, point);
                int den = 0x8000000;
                int negative;
                int n;
                int d;
                register int n_zeros asm("$5");
                int d_zeros;
                int excess;
                int scale;

                if (den == 0) {
                    den = 2;
                }
                negative = (num & 0x80000000) ^ (den & 0x80000000);
                __asm__("" : : "r"(negative));
                n = abs(num);
                d = abs(den);
                n_zeros = leading_zeros(n);
                excess = n_zeros - 12;
                if (excess < 0) {
                    n <<= n_zeros;
                    d_zeros = leading_zeros(d);
                    n_zeros = d_zeros - n_zeros;
                    if (n_zeros >= 0) {
                        scale = 12 - d_zeros;
                        if (scale >= 0) {
                            v = (unsigned int)n / (d >> scale);
                        } else {
                            v = (unsigned int)n / (d << -scale);
                        }
                        v <<= n_zeros;
                    } else {
                        v = (unsigned int)n / (d >> -excess);
                    }
                } else {
                    n <<= 12;
                    v = (unsigned int)n / d;
                }
                if (negative) {
                    v = -v;
                }

            }
            }
            weight = 409;
            switch (tank->state) {
            case 18:
            case 19:
            case 20:
            case 21:
                weight = 3686;
                break;
            }
            result = fixed_mul(v, weight);
        }
    }
    return result;
}
