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
    register int den asm("$5") = denominator;
    int negative;
    unsigned int n;
    int d;
    unsigned int m;
    int n_zeros;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;
    int result;

    d = abs(denominator);
    negative = (numerator & 0x80000000) ^ (denominator & 0x80000000);
    n = abs(numerator);
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
            quotient = m / (d >> -excess);
        }
    } else {
        m = n << 12;
        quotient = m / den;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

unsigned short func_8002B7A0(int x) {
    if (x <= 0x19EFFF) {
        return 10922;
    }
    return fixed_mul(5462, fixed_div(0x1F4000 - x, 0x55000)) + 16384;
}
