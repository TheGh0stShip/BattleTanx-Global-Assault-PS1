
typedef struct { int x, y, z; } Vector;
typedef struct {
    unsigned char len;
    unsigned char flag;
    unsigned char count;
    unsigned char kind;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char code;
    Vector pos;
    short size;
    short angle;
    short w;
    short h;
    int tex;
} Sprite;
typedef struct {
    int first;
    char *current;
    int pad;
    int start;
    int remaining;
    int count;
} Pool;
typedef struct {
    char pad[8];
    Vector pos;
    int dx;
    int dz;
    char pad1C[42 - 28];
    unsigned char heat;
    char pad2B[46 - 43];
    short lit;
} Flame;
extern Pool D_800AD9EC;
extern int D_800ADA04;
unsigned int func_80086C84(void);

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

static inline int fixed_div(unsigned int numerator, int denom) {
    register int denominator asm("$5") = denom;
    int negative;
    register int n asm("$3");
    int sign;
    register int d asm("$7");
    register int n_zeros asm("$4");
    int d_zeros;
    register int excess asm("$6");
    int scale;
    unsigned int quotient;
    register int divisor asm("$2");
    int result;

    sign = numerator & 0x80000000;
    negative = sign ^ (denominator & 0x80000000);
    d = abs(denominator);
    __asm__("" : : "r"(negative));
    n = numerator;
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        n <<= n_zeros;
        d_zeros = leading_zeros(d);
        n_zeros = d_zeros - n_zeros;
        if (n_zeros >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                divisor = d >> scale;
            } else {
                divisor = d << -scale;
            }
            quotient = (unsigned int)n / divisor;
            quotient <<= n_zeros;
        } else {
            divisor = d >> -excess;
            quotient = (unsigned int)n / divisor;
        }
    } else {
        n <<= 12;
        quotient = (unsigned int)n / denominator;
    }
    result = quotient;
    if (negative) {
        return -result;
    }
    return result;
}

static inline int to_int(int v) {
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

static inline int round_int(int value) {
    int result;

    if (value >= 0) {
        result = value + 2048 >= 0 ? (value + 2048) >> 12 : -(-(value + 2048) >> 12);
    } else {
        result = value - 2048 >= 0 ? (value - 2048) >> 12 : -(-(value - 2048) >> 12);
    }
    return result;
}

static inline Sprite *alloc_packet(int size) {
    Pool *pool = &D_800AD9EC;
    register Sprite *p asm("$4");
    int rem;
    int left;

    p = 0;
    rem = pool->remaining;
    left = rem - size;
    if (left > 0) {
        p = (Sprite *)pool->current;
        pool->remaining = left;
        {
            register int c asm("$2") = pool->count + 1;
            pool->current += size;
            pool->count = c;
        }
        p->len = size / 4;
        p->count = 0;
    }
    return p;
}

static inline void init_sprite(Sprite *p, Vector *pos, int r, int g, int b) {
    p->pos = *pos;
    p->r = r;
    p->g = g;
    p->b = b;
    p->kind = 9;
    p->code = 44;
    p->flag = 0;
    p->size = 0;
    p->angle = 0;
}

static inline void glow(Vector *pos, int scale, int size) {
    Sprite *p;

    p = alloc_packet(32);
    if (p != 0) {
        init_sprite(p, pos, 192, 128, 64);
        p->tex = D_800ADA04 + 252;
        p->flag = 0;
        p->angle = func_80086C84() >> 16;
        p->w = fixed_mul(scale, size);
        p->h = fixed_mul(scale, size);
        p->code |= 2;
        p->size = 32;
    }
}

static inline void streak(Vector *head, Vector *tail, int scale, unsigned char flag) {
    Sprite *p;
    Sprite *q;

    p = alloc_packet(32);
    if (p != 0) {
        init_sprite(p, head, 64, 64, 64);
        {
            register int f asm("$3") = flag;
            p->tex = D_800ADA04 + 276;
            p->flag = f;
        }
        p->w = fixed_mul(scale, 36);
        p->h = fixed_mul(scale, 36);
        p->code |= 2;
        p->angle = 0;
        p->size = 32;
        q = alloc_packet(28);
        if (q != 0) {
            q->pos = *tail;
            q->w = fixed_mul(scale, 24);
            q->h = fixed_mul(scale, 24);
            q->code = 44;
            q->angle = 0;
            p->len += q->len;
            p->count++;
            q->code |= 2;
            q->angle = 0;
        }
    }
}

void func_80038584(Flame *f) {
    Vector pts[2];
    int scale;
    int len;

    scale = (fixed_div(f->heat, 30) + 4096) / 2;
    pts[0].x = round_int(f->pos.x);
    pts[0].y = round_int(f->pos.y);
    pts[0].z = round_int(f->pos.z);
    len = scale * 3;
    pts[1].x = pts[0].x - fixed_mul(len, f->dx) / 4096;
    pts[1].y = pts[0].y;
    pts[1].z = pts[0].z - fixed_mul(len, f->dz) / 4096;
    glow(&pts[0], scale, 80);
    glow(&pts[0], scale, 56);
    if (f->lit != 0) {
        streak(&pts[0], &pts[1], scale, 32);
        streak(&pts[0], &pts[1], scale, 16);
    }
}
