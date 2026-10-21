typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;

typedef struct SVec {
    short x;
    short y;
    short z;
    short pad;
} SVec;

typedef struct Angle {
    unsigned short x;
    short pad;
} Angle;

typedef struct Tank {
    int pad0[2];
    Vec pos;
    char pad14[0x214 - 0x14];
    int shake;
} Tank;

typedef struct Owner {
    int pad0[2];
    Tank *tank;
} Owner;

extern int func_8008AE30(int, int);
extern int func_8008AD60(int);
extern int func_8008ACC0(int);
extern void func_800718A4(int, Vec *, SVec *, int, int);

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

static inline int fixed_div(int numerator, int denom) {
    register int denominator asm("$5") = denom;
    int negative;
    int n;
    int sign;
    int d;
    int n_zeros;
    int d_zeros;
    register int excess asm("$6");
    int scale;
    unsigned int quotient;
    int result;

    negative = (sign = numerator & 0x80000000) ^ (denominator & 0x80000000);
    n = abs(numerator);
    __asm__("" : "=r"(negative) : "0"(negative));
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
            scale = -excess;
            quotient = (unsigned int)n / (d >> scale);
        }
    } else {
        n <<= 12;
        quotient = (unsigned int)n / denominator;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

static inline void copy_heading(unsigned short *dst, unsigned short *src) {
    if (dst != 0) {
        *dst = *src;
    }
}

int func_80074254(Owner *owner, Vec *target, int dist, unsigned short *heading) {
    Tank *tank;
    int dx;
    int dz;
    int yaw;
    unsigned int pitch;
    int sin_p;
    int cos_p;
    int sin_y;
    int cos_y;
    Vec pos;
    SVec dir;
    unsigned short angle;
    unsigned short *ap;

    tank = owner->tank;
    if (tank == 0) {
        return 0;
    }
    dx = target->x - tank->pos.x;
    dz = target->z - tank->pos.z;
    yaw = func_8008AE30(dx, dz) & 0xFFF;
    ap = &angle;
    *ap = yaw << 4;
    dx = fixed_mul(func_8008AD60(yaw), dx);
    pitch = func_8008AE30(target->y - tank->pos.y, dx + fixed_mul(func_8008ACC0(yaw), dz)) & 0xFFF;
    if (dist < 50) {
        if (dist >= 6) {
            int n = dist - 5;
            __asm__("" : "+r"(n));
            fixed_mul(26624, fixed_div(n, 45));
        }
    }
    copy_heading(heading, &angle);
    pitch >>= 4;
    sin_p = func_8008AD60(pitch);
    cos_p = func_8008ACC0(pitch);
    sin_y = func_8008AD60(angle >> 4);
    cos_y = func_8008ACC0(angle >> 4);
    pos = *target;
    dir.x = fixed_mul(cos_p, sin_y);
    dir.z = fixed_mul(cos_p, cos_y);
    dir.y = sin_p;
    func_800718A4(4, &pos, &dir, fixed_div(tank->shake, 100), 0);
    func_800718A4(5, &pos, &dir, fixed_div(tank->shake, 100), 0);
    return 0;
}
