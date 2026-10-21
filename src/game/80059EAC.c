extern unsigned int D_800E47F8;
extern int D_800E47F4;
extern unsigned int func_800914AC(int);
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

static inline int fixed_div(int numerator, int den) {
    register int denominator asm("$5") = den;
    int negative;
    int n;
    int d;
    int n_zeros;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;
    unsigned int dv;
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
                dv = d >> scale;
            } else {
                dv = d << -scale;
            }
            quotient = quotient / dv;
            quotient <<= n_zeros;
        } else {
            quotient = quotient / (d >> -excess);
        }
    } else {
        quotient = n << 12;
        quotient = quotient / denominator;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

void func_80059EAC(void) {
    unsigned int now = func_800914AC(0xF2000001);
    unsigned int prev = D_800E47F8;

    if (now < prev) {
        unsigned int base = prev - 0xFFFF;

        D_800E47F4 = fixed_div((now - base) << 12, 0x22B8E1);
    } else {
        D_800E47F4 = fixed_div((now - prev) << 12, 0x22B8E1);
    }
    D_800E47F8 = now;
}
