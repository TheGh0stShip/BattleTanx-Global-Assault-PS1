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

static inline int fixed_div(int numerator, int denominator) {
    int negative;
    int n;
    int sign;
    int d;
    int n_zeros;
    int shifted;
    int d_zeros;
    int excess;
    int difference;
    int scale;
    unsigned int quotient;
    int result;

    sign = numerator & 0x80000000;
    negative = sign ^ (denominator & 0x80000000);
    n = abs(numerator);
    d = abs(denominator);
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        shifted = n << n_zeros;
        d_zeros = leading_zeros(d);
        difference = d_zeros - n_zeros;
        if (difference >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                quotient = (unsigned int)shifted / (d >> scale);
            } else {
                quotient = (unsigned int)shifted / (d << -scale);
            }
            quotient <<= difference;
        } else {
            quotient = (unsigned int)shifted / (d >> -excess);
        }
    } else {
        shifted = n << 12;
        quotient = (unsigned int)shifted / d;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

static inline int fixed_div_pinned(int numerator, int denominator) {
    int negative;
    int n;
    int sign;
    int d;
    register int n_zeros asm("$6");
    int shifted;
    int d_zeros;
    int excess;
    register int difference asm("$5");
    int scale;
    unsigned int quotient;
    int result;

    sign = numerator & 0x80000000;
    negative = sign ^ (denominator & 0x80000000);
    n = abs(numerator);
    d = abs(denominator);
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        shifted = n << n_zeros;
        d_zeros = leading_zeros(d);
        difference = d_zeros - n_zeros;
        if (difference >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                quotient = (unsigned int)shifted / (d >> scale);
            } else {
                quotient = (unsigned int)shifted / (d << -scale);
            }
            quotient <<= difference;
        } else {
            quotient = (unsigned int)shifted / (d >> -excess);
        }
    } else {
        shifted = n << 12;
        quotient = (unsigned int)shifted / d;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

int func_8002B8EC(int x, int width) {
    int span;

    if (x < -width) {
        span = width - 128;
        width = -x - width;
        if (span == 0) {
            span = 2;
        }
        return fixed_div(width, span);
    }
    if (width < x) {
        span = 127 - width;
        x -= width;
        if (span == 0) {
            span = 2;
        }
        return fixed_div_pinned(x, span);
    }
    return 0;
}
