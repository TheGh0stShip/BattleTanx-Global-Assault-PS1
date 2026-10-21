typedef struct {
    char pad0[8];
    short value;
} Gauge;

typedef struct {
    char pad0;
    unsigned char level;
    char pad2[6];
    Gauge *gauge;
} Widget;

typedef struct {
    int *current;
    int *maximum;
    int last_current;
    int last_maximum;
} Meter;

extern Gauge D_800AAF5C;
extern Gauge D_800AAF68;
extern signed char D_800A606C;
extern Meter D_800E4D4C[];
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
    int sign;
    int d;
    int n_zeros;
    int shifted;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;

    sign = numerator & 0x80000000;
    negative = sign ^ (denominator & 0x80000000);
    n = abs(numerator);
    d = abs(denominator);
    __asm__("" : : "r"(negative));
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        shifted = n << n_zeros;
        d_zeros = leading_zeros(d);
        n_zeros = d_zeros - n_zeros;
        if (n_zeros >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                quotient = (unsigned int)shifted / (d >> scale);
            } else {
                quotient = (unsigned int)shifted / (d << -scale);
            }
            quotient <<= n_zeros;
        } else {
            quotient = (unsigned int)shifted / (d >> -excess);
        }
    } else {
        shifted = n << 12;
        quotient = (unsigned int)shifted / d;
    }
    if (negative) {
        quotient = -quotient;
    }
    return quotient;
}


int func_80062CB0(void *unused, Widget *w) {
    Gauge *g = w->gauge;
    short index;
    int scale;
    Meter *m;
    int cur;
    int max;
    int ratio;
    int num;
    int den;

    index = 0;
    if (g != &D_800AAF5C) {
        index = g == &D_800AAF68;
    }
    scale = 0x40000;
    if (D_800A606C >= 2) {
        scale = 0x30000;
    }
    m = &D_800E4D4C[index];
    if (m->maximum == 0) {
        g->value = 0;
        return 0;
    }
    if (m->last_current != *m->current || m->last_maximum != *m->maximum) {
        cur = *m->current;
        m->last_current = cur;
        max = *m->maximum;
        m->last_maximum = max;
        den = m->last_current << 12;
        num = max << 12;
        if (den == 0) {
            den = 2;
        }
        ratio = fixed_div(num, den);
        g->value = fixed_to_int(fixed_mul(ratio, scale));
        if (ratio < 1365) {
            w->level = 1;
        } else if (ratio < 2730) {
            w->level = 2;
        } else {
            w->level = 3;
        }
    }
    return 0;
}
