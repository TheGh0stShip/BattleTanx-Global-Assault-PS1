typedef struct {
    char pad0[0x2C];
    unsigned short heading;
    char pad1[0x3C - 0x2E];
    int num;
    int den;
    char pad2[0x218 - 0x44];
    unsigned int status;
    char pad3[4];
    int vx;
    char pad4[4];
    int vz;
} Tank;
extern unsigned int func_80086C84(void);
extern int func_8008ACC0(int);
extern int func_8008AD60(int);

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
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

void func_8003FE80(Tank *t, int force)
{
    unsigned short heading;
    int den;
    int num;
    int push;
    int amount;
    int angle;

    if (t->status & 0x800) {
        heading = t->heading;
    } else {
        heading = t->heading + 0x8000;
    }
    den = t->den;
    num = t->num;
    if (den == 0) {
        den = 2;
    }
    push = fixed_mul(force, fixed_div(num, den));
    amount = fixed_mul(((func_80086C84() >> 16) * 3277 >> 16) + 1638, push);
    angle = heading >> 4;
    t->vx += fixed_mul(func_8008ACC0(angle), amount);
    t->vz -= fixed_mul(func_8008AD60(angle), amount);
}
