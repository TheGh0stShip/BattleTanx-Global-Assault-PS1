typedef struct { int x; int y; int z; } Vector;

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
        quotient = (unsigned int)shifted / d;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

typedef struct {
    short kind;
    unsigned char unk2;
    unsigned char length;
} Segment;

typedef struct {
    int unk0;
    int duration;
    int remaining;
    short pos[3];
    short unk12;
    short angle;
    short unk16;
    short rate;
    short unk1A;
    short unk1C;
    signed char spin;
    char unk1F;
    short phase;
    short speed;
    unsigned char color[3];
    unsigned char script;
    unsigned char step;
    unsigned char countdown;
} Particle;

extern Segment *D_800ADF48[];

void func_8006D818(Particle *p, Vector *move, int dt) {
    int duration;
    int remaining;
    int fade;
    int before;
    int elapsed;
    int count;

    p->pos[0] -= move->x >> 12;
    p->pos[1] -= move->y >> 12;
    p->pos[2] -= move->z >> 12;
    p->pos[1] += (p->rate * dt) / 65536;
    p->angle += (p->spin * dt) / 4096;
    duration = p->duration;
    remaining = p->remaining;
    if (duration == 0) {
        duration = 2;
    }
    fade = fixed_div(remaining, duration);
    p->color[0] = fixed_mul(fade, 64);
    p->color[1] = fixed_mul(fade, 8);
    p->color[2] = fixed_mul(fade, 64);
    p->phase += fixed_mul(dt, p->speed);
    before = p->remaining;
    p->remaining = before - dt;
    if (p->script != 255) {
        count = p->countdown;
        elapsed = (before >> 12) - (p->remaining >> 12);
        if (elapsed < count) {
            p->countdown = count - elapsed;
        } else {
            p->step++;
            if (D_800ADF48[p->script][p->step].kind == 1) {
                p->step = D_800ADF48[p->script][p->step].length;
            }
            p->countdown = D_800ADF48[p->script][p->step].length;
        }
    }
}
