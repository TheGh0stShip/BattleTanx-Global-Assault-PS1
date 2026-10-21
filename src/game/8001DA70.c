typedef struct { int x, z; } Pos2;
typedef struct Cell {
    unsigned int flags;
    char pad04[4];
    unsigned short next[4];
    short x;
    short z;
    short y;
    short min_x;
    short max_x;
    short min_z;
    short max_z;
    short min_y;
    short max_y;
    short radius;
    unsigned short angle;
    char pad26[0x28 - 0x26];
} Cell;
extern Cell D_800C62B0[];
extern void func_800167D0(Pos2 *, unsigned short, Pos2 *);

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
    unsigned int dv;
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
                dv = d >> scale;
            } else {
                dv = d << -scale;
            }
            quotient = (unsigned int)n / dv;
            quotient <<= n_zeros;
        } else {
            dv = d >> -excess;
            quotient = (unsigned int)n / dv;
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

static inline int safe_div(int num, int den) {
    if (den == 0) {
        den = 2;
    }
    return fixed_div(num, den);
}

static inline int cell_top(Cell *c) {
    if (abs(c->min_y) > abs(c->max_y)) {
        return (short)(c->min_y + c->y) << 14;
    }
    return (short)(c->max_y + c->y) << 14;
}

int func_8001DA70(unsigned short id, Pos2 *p)
{
    Cell *c = &D_800C62B0[id];
    Pos2 rel;
    Pos2 out;
    int top;
    unsigned short w;
    unsigned short d;
    unsigned short q;
    short x0;
    short x1;
    short z0;
    short z1;
    unsigned short side;

    rel.x = p->x - (c->x << 14);
    rel.z = p->z - (c->z << 14);
    func_800167D0(&rel, c->angle, &out);
    top = cell_top(c);
    w = c->max_x - c->min_x;
    d = c->max_z - c->min_z;
    if (d > w) {
        w = d;
    }
    q = w >> 2;
    z0 = c->min_z + q;
    z1 = c->max_z - q;
    x0 = c->min_x + q;
    x1 = c->max_x - q;
    side = 0;
    if (out.x < x0 << 14) {
        side = 1;
    } else if (out.x > x1 << 14) {
        side = 2;
    }
    if (out.z < z0 << 14) {
        side |= 4;
    } else if (out.z > z1 << 14) {
        side |= 8;
    }
    switch (side) {
    case 5:
        if (out.x - (c->min_x << 14) < out.z - (c->min_z << 14)) {
            side = 1;
        } else {
            side = 4;
        }
        break;
    case 10:
        if ((c->max_x << 14) - out.x < (c->max_z << 14) - out.z) {
            side = 2;
        } else {
            side = 8;
        }
        break;
    case 9:
        if (out.x - (c->min_x << 14) < (c->max_z << 14) - out.z) {
            side = 1;
        } else {
            side = 8;
        }
        break;
    case 6:
        if ((c->max_x << 14) - out.x < out.z - (c->min_z << 14)) {
            side = 2;
        } else {
            side = 4;
        }
        break;
    }
    switch (side) {
    case 0:
        return top;
    case 1:
        if (x0 == c->min_x) {
            return top;
        }
        return fixed_mul(safe_div(out.x - (c->min_x << 14), (short)(x0 - c->min_x) << 14), top);
    case 2:
        if (c->max_x == x1) {
            return top;
        }
        return fixed_mul(safe_div((c->max_x << 14) - out.x, (short)(c->max_x - x1) << 14), top);
    case 4:
        if (z0 == c->min_z) {
            return top;
        }
        return fixed_mul(safe_div(out.z - (c->min_z << 14), (short)(z0 - c->min_z) << 14), top);
    case 8:
        if (c->max_z == z1) {
            return top;
        }
        return fixed_mul(safe_div((c->max_z << 14) - out.z, (short)(c->max_z - z1) << 14), top);
    }
    return 0;
}
