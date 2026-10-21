typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;
typedef struct ProbeHit {
    int unk00;
    int unk04;
    Vector pos;
    char pad14[0x24 - 0x14];
} ProbeHit;
typedef struct Owner {
    char pad00[4];
    short kind;
} Owner;
typedef struct View {
    char pad00[0x48];
    Owner *owner;
} View;
extern short D_800C628C;
unsigned short func_80019D80(Vector *, Vector *, int, int, int, ProbeHit *);
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


int abs(int);

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
    __asm__("" : : "r"(negative));
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
            if (scale < 0) {
                quotient = quotient / (d << -scale);
            } else {
                quotient = quotient / (d >> scale);
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

static inline int fixed_div_pos(int numerator, int denominator) {
    int negative;
    int n;
    int d;
    register int n_zeros asm("$5");
    register int d_zeros asm("$6");
    int excess;
    int scale;
    unsigned int quotient;
    int result;
    int divisor;

    negative = (numerator & 0x80000000) ^ (denominator & 0x80000000);
    __asm__("" : : "r"(negative));
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
                divisor = d >> scale;
            } else {
                divisor = d << -scale;
            }
            quotient = quotient / divisor;
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


static inline int safe_div(int n, int d) {
    if (d == 0) {
        d = 2;
    }
    return fixed_div(n, d);
}

static inline int safe_div_pos(int n, int d) {
    if (d == 0) {
        d = 2;
    }
    return fixed_div_pos(n, d);
}

short func_80015458(View *view, Vector *from, Vector *to) {
    ProbeHit hit;
    Vector a;
    Vector b;
    int t;
    int mask;
    int dx;
    int x;
    int z;

    if (view->owner != 0 && view->owner->kind != 4 && view->owner->kind != 3) {
        return 4096;
    }
    t = 4096;
    x = from->x;
    z = from->z;
    a.x = x;
    a.y = 0xA0000;
    a.z = z;
    {
        int x2 = to->x;
        int z2 = to->z;

        b.y = 0xA0000;
        b.x = x2;
        b.z = z2;
    }
    mask = 0xA04403;
    if (view->owner->kind == 3) {
        mask = 0x804403;
    }
    D_800C628C = 1;
    __asm__("" : : "r"(&hit));
    __asm__("" : : "r"(&a));
    if (func_80019D80(&a, &b, mask, 23, 0, &hit)) {
        dx = to->x - from->x;
        if (dx < 0) {
            dx = from->x - to->x;
        }
        if ((to->z - from->z >= 0 ? to->z - from->z : from->z - to->z) < dx) {
            t = safe_div_pos(hit.pos.x - from->x, to->x - from->x);
        } else {
            t = safe_div_pos(hit.pos.z - from->z, to->z - from->z);
        }
        if ((short)t < 0) {
            t = 0;
        } else if ((short)t > 4096) {
            t = 4096;
        }
    }
    return t;
}
