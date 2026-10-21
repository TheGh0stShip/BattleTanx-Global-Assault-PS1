typedef struct {
    char pad[0xAC];
    int scale;
    int fB0;
    int hp_scale;
    int speed;
    int turn;
    int accel;
    int armor;
    char pad2[0xD0 - 0xC8];
} Vehicle;
typedef struct { char pad[0x98]; int divisor; int factor; } Owner;
typedef struct {
    char pad0[0x9C];
    int type;
    char pad1[0x1EC - 0xA0];
    int speed;
    int turn;
    int accel;
    int f1F8;
    int hp;
    int armor;
    char pad2[0x208 - 0x204];
    Owner *owner;
    int max_hp;
} Tank;
extern Vehicle D_800A4EF4[];

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
    register int d_zeros asm("$5");
    int excess;
    int scale;
    unsigned int quotient;
    unsigned int m;
    int result;

    sign = numerator & 0x80000000;
    negative = sign ^ (denominator & 0x80000000);
    n = abs(numerator);
    d = abs(denominator);
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
        quotient = m / d;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

static inline int to_int(int v)
{
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

void func_80039094(Tank *t, int *mods)
{
    int type;
    int scale;
    int num;
    int den;
    int k;

    type = t->type;
    scale = D_800A4EF4[type].scale;
    t->speed = 9830;
    t->turn = 1228;
    t->accel = 1228;
    t->f1F8 = 1228;
    t->hp = t->max_hp / 2;
    t->armor = 1228;
    num = fixed_mul(D_800A4EF4[type].speed, mods[0]);
    den = t->owner->divisor;
    if (den == 0) {
        den = 2;
    }
    t->speed = fixed_div(num, den);
    k = fixed_mul(scale, mods[1]);
    t->turn = fixed_mul(D_800A4EF4[type].turn, k);
    t->accel = fixed_mul(D_800A4EF4[type].accel, fixed_mul(scale, mods[2]));
    t->f1F8 = mods[3];
    t->hp = to_int(fixed_mul(D_800A4EF4[type].hp_scale, fixed_mul(mods[4], t->max_hp << 12)));
    k = fixed_mul(t->owner->factor, mods[5]);
    t->armor = fixed_mul(D_800A4EF4[type].armor, k);
}
