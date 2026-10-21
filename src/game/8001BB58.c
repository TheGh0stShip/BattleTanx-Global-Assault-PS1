typedef struct Dir {
    char pad00[8];
    int x;
    int z;
} Dir;
typedef struct Mover {
    int dx;
    int dz;
    int speed;
    int length;
    char pad10[0x60 - 0x10];
    Dir *dir;
} Mover;
extern int D_800DE30C;
unsigned short func_8001B130(Mover *, int *);
void func_80053BB0(int, int, int, int);

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

static inline int safe_div(int num, int den) {
    if (den == 0) {
        den = 2;
    }
    return fixed_div(num, den);
}

void func_8001BB58(Mover *m, int *pos) {
    int dot;
    int step;

    if (m->dir != 0 && (m->dx != m->dir->x || m->dz != m->dir->z)) {
        dot = fixed_mul(m->dir->x, m->dx) + fixed_mul(m->dir->z, m->dz);
        if (dot < 0) {
            dot = -dot;
            m->speed = fixed_mul(dot, m->speed);
            m->dx = -m->dir->x;
            m->dz = -m->dir->z;
        } else {
            m->speed = fixed_mul(dot, m->speed);
            m->dx = m->dir->x;
            m->dz = m->dir->z;
        }
    }
    step = fixed_mul(D_800DE30C, m->speed);
    pos[0] += fixed_mul(step, m->dx);
    pos[1] += fixed_mul(step, m->dz);
    if (m->dir != 0 && func_8001B130(m, pos)) {
        func_80053BB0(19, pos[0], pos[1], safe_div(m->speed, m->length));
        m->speed = fixed_mul(-1, m->speed);
        if (m->speed < 0) {
            dot = -m->dx;
            m->dx = dot;
            m->dz = -m->dz;
            m->speed = -m->speed;
        }
    }
}
