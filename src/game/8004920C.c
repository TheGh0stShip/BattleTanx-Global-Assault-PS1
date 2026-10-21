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



static inline int fixed_div(int numerator, int den) {
    register int denominator asm("$5") = den;
    int negative;
    int n;
    int sign;
    int d;
    int shifted;
    int n_zeros;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;
    int result;

    sign = numerator & 0x80000000;
    negative = sign ^ (denominator & 0x80000000);
    n = abs(numerator);
    d = denominator;
    if (d < 0) {
        d = -d;
    }
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
        quotient = (unsigned int)shifted / denominator;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

static inline int max_int(int a, int b) {
    if (a < b) {
        a = b;
    }
    return a;
}

static inline int min_int(int a, int b) {
    if (b < a) {
        a = b;
    }
    return a;
}

int func_8004920C(int dx, int dz) {
    int major;
    int minor;

    dz = abs(dz);
    dx = abs(dx);
    major = max_int(dz, dx);
    minor = min_int(dz, dx);
    return major + fixed_div(fixed_mul(minor, 3 << 12), 8 << 12);
}
