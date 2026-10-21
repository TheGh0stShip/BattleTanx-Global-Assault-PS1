
typedef struct {
    int x;
    int y;
    int z;
} Vector;

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
    n = numerator;
    if (n < 0) {
        n = -n;
    }
    d = abs(denominator);
    __asm__("" : : "r"(negative), "r"(denominator));
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
    n_zeros = quotient;
    if (negative) {
        n_zeros = -n_zeros;
    }
    return n_zeros;
}

typedef struct {
    short x;
    short y;
    short z;
    short pad;
} SVector;

typedef struct {
    short m[3][3];
    short pad;
    int t[3];
} Matrix;

typedef struct {
    short id;
    short pad2;
    short type;
} Source;

typedef struct Particle {
    struct Particle *next;
    int pad4;
    int count;
    char padC[39 - 12];
    unsigned char anim;
    unsigned char frame;
    unsigned char timer;
} Particle;

typedef struct Effect {
    short id;
    char pad2[5];
    unsigned char kind;
    Source *src;
    Particle *particles;
    Vector pos;
    int alpha;
    int life;
    int fade;
    int scale;
    short dir[3];
    short angle[3];
    struct Effect *prev;
    struct Effect *next;
} Effect;

typedef struct {
    int pad;
    void (*fn)(Source *src, Effect *e, int what, int arg, void *out);
    int pad2;
} Handler;

typedef struct {
    void (*init)(Effect *e, Particle *p, SVector *v);
    void (*update)(Particle *p, Vector *delta, int dt);
    int pad8;
    int fade_time;
    char pad10[36 - 16];
} EffectKind;

typedef struct {
    short cmd;
    unsigned char arg;
    unsigned char value;
} AnimStep;

extern Effect *D_800EAC14;
extern Effect *D_800EAC18;
extern Particle *D_800EAC10;
extern int D_800DE30C;
extern signed char D_800A606C;
extern EffectKind D_800ADF64[];
extern AnimStep *D_800ADF48[];
extern Vector D_800AE138;
extern int func_8006A1EC(int a, Vector *pos);
extern unsigned int func_80086C84(void);

static inline void free_chain(Particle **list, Particle **pool) {
    Particle *first = *list;
    Particle *last = first;

    while (last->next != 0) {
        last = last->next;
    }
    *list = 0;
    last->next = *pool;
    *pool = first;
}

static inline void link_particle(Particle **list, Particle *p) {
    p->next = *list;
    *list = p;
}

void func_8006C67C(Effect *e, Vector *pos) {
    SVector sv;
    unsigned short step;
    int old;
    int count;
    int t;
    int d;
    Effect *victim;
    Particle *p;
    Particle *last;

    if (D_800A606C == 1 && func_8006A1EC(0, pos) == 0) {
        return;
    }
    old = e->scale;
    if (e->fade > D_800DE30C) {
        e->scale = old + fixed_mul(D_800DE30C, e->life);
    } else {
        e->scale = old + fixed_mul(e->fade, e->life);
    }
    count = (e->scale >> 12) - (old >> 12);
    if (count <= 0) {
        return;
    }
    d = e->scale - old;
    if (d == 0) {
        d = 2;
    }
    step = fixed_div(4096, d);
    {
        int frac = ((old + 4096) & ~4095) - old;
        t = fixed_mul((short)step, frac) - 4096;
    }
    for (; count > 0; count--, t += step) {
        if (D_800EAC10 == 0) {
            victim = D_800EAC14;
            if (victim != 0 && victim != e && victim->particles != 0) {
                free_chain(&victim->particles, &D_800EAC10);
                victim->fade = 0;
                if (victim->prev == 0) {
                    D_800EAC14 = victim->next;
                } else {
                    victim->prev->next = victim->next;
                }
                if (victim->next == 0) {
                    D_800EAC18 = victim->prev;
                } else {
                    victim->next->prev = victim->prev;
                }
                victim->next = 0;
                victim->prev = D_800EAC18;
                if (D_800EAC18 != 0) {
                    D_800EAC18->next = victim;
                    D_800EAC18 = victim;
                } else {
                    D_800EAC14 = victim;
                    D_800EAC18 = victim;
                }
            }
        }
        if (D_800EAC10 == 0) {
            continue;
        }
        if (count == 1) {
            t = 0;
        }
        p = D_800EAC10;
        D_800EAC10 = p->next;
        link_particle(&e->particles, p);
        d = pos->x - e->pos.x;
        sv.x = fixed_mul((short)t, d) >> 12;
        sv.y = fixed_mul((short)t, pos->y - e->pos.y) >> 12;
        sv.z = fixed_mul((short)t, pos->z - e->pos.z) >> 12;
        sv.x += ((int)((func_80086C84() >> 16) * (e->dir[0] * 2 + 1)) >> 16) - e->dir[0];
        sv.y += ((int)((func_80086C84() >> 16) * (e->dir[1] * 2 + 1)) >> 16) - e->dir[1];
        sv.z += ((int)((func_80086C84() >> 16) * (e->dir[2] * 2 + 1)) >> 16) - e->dir[2];
        D_800ADF64[e->kind].init(e, p, &sv);
        if (p->anim != 255) {
            p->frame = 0;
            p->timer = D_800ADF48[p->anim]->value;
        }
        D_800ADF64[e->kind].update(p, &D_800AE138, -(short)t);
    }
}
