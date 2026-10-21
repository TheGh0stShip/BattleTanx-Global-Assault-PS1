
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
    int shifted;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;
    register int divisor asm("$2");
    int result;

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
                divisor = d >> scale;
            } else {
                divisor = d << -scale;
            }
            quotient = (unsigned int)shifted / divisor;
            quotient <<= n_zeros;
        } else {
            divisor = d >> -excess;
            quotient = (unsigned int)shifted / divisor;
        }
    } else {
        shifted = n << 12;
        quotient = (unsigned int)shifted / d;
    }
    result = quotient;
    if (negative) {
        return -result;
    }
    return result;
}

typedef struct {
    short x;
    short y;
    short z;
} SVector;

static inline int scale_down(int f, int c) {
    int m = f * c;

    if (m >= 0) {
        return (unsigned int)m >> 12;
    }
    return -(-m >> 12);
}

void func_80071360(SVector *v_arg, SVector *n_arg) {
    register SVector *v asm("$11") = v_arg;
    register SVector *n asm("$12") = n_arg;
    int vx, vy, vz;
    int nx, ny, nz;
    int dot;
    int len;
    short f;

    vx = v->x;
    nx = n->x;
    vy = v->y;
    ny = n->y;
    vz = v->z;
    nz = n->z;
    {
        int a = fixed_mul(nx, vx);
        int b = fixed_mul(ny, vy);
        int c;

        a = a + b;
        c = fixed_mul(nz, vz);
        dot = a + c;
    }
    {
        int a = fixed_mul(nx, nx);
        int b = fixed_mul(ny, ny);
        int c;

        a = a + b;
        c = fixed_mul(nz, nz);
        len = a + c;
    }
    f = fixed_div(dot, len ? len : 2);
    v->x -= scale_down(f, n->x);
    f = fixed_div(dot, len ? len : 2);
    v->y -= scale_down(f, n->y);
    f = fixed_div(dot, len ? len : 2);
    v->z -= scale_down(f, n->z);
}
