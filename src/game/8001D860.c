int func_8008ABF0(int);
int func_80053354(int);

static inline int sat_square(int x, int out) {
    __asm__ volatile(".set\tnoreorder\n\tmult %1, %1\n\tmflo $2\n\tmfhi $3\n\tblez $3, 1f\n\tli $2, -4096\n\tand $2, $3, $2\n\tbnez $2, 2f\n\tlui %0, 0x7fff\n"
                     "1:\tbgez $3, 3f\n\tnegu $2, $3\n\tli $3, -4096\n\tand $2, $2, $3\n\tbeqz $2, 3f\n\tlui %0, 0x7fff\n"
                     "2:\tj 4f\n\tori %0, %0, 0xffff\n"
                     "3:\tsrl %0, %0, 12\n\tsll $3, $3, 20\n\tor %0, %0, $3\n4:\n\t.set\treorder"
                     : "+r"(out)
                     : "r"(x)
                     : "$2", "$3", "memory");
    return out;
}

static inline int sat_square_lo(int x) {
    register int out asm("$2");

    __asm__ volatile(".set\tnoreorder\n\tmult %1, %1\n\tmflo $2\n\tmfhi $3\n\tblez $3, 1f\n\tli $2, -4096\n\tand $2, $3, $2\n\tbnez $2, 2f\n\tlui %0, 0x7fff\n"
                     "1:\tbgez $3, 3f\n\tnegu $2, $3\n\tli $3, -4096\n\tand $2, $2, $3\n\tbeqz $2, 3f\n\tlui %0, 0x7fff\n"
                     "2:\tj 4f\n\tori %0, %0, 0xffff\n"
                     "3:\tsrl %0, %0, 12\n\tsll $3, $3, 20\n\tor %0, %0, $3\n4:\n\t.set\treorder"
                     : "=r"(out)
                     : "r"(x)
                     : "$3", "memory");
    return out;
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
    {
        register int t asm("$4");

        t = denominator;
        if (denominator < 0) {
            t = -t;
        }
        d = t;
    }
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


static inline int safe_div(int num, int den) {
    register int q asm("$5");

    q = den;
    if (q == 0) {
        q = 2;
    }
    return fixed_div(num, q);
}

unsigned short func_8001D860(int dy, int x) {
    int negative;
    int y;
    int a;
    int b;
    int hyp;
    register int angle asm("$4");
    int result;

    y = dy;
    if (y == 0) {
        return 0;
    }
    negative = 0;
    if (y < 0) {
        negative = 1;
        y = -y;
    }
    a = sat_square(y, dy);
    b = sat_square_lo(x);
    hyp = func_8008ABF0(a + b);
    angle = (func_80053354(safe_div(y, hyp)) << 3) & 0x7FF8;
    result = angle;
    if ((unsigned short)negative) {
        result = -angle;
    }
    return result;
}
