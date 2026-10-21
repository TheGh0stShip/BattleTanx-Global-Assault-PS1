typedef struct { int x, y, z; } Vector;
typedef struct {
    unsigned char type;
    unsigned char b1;
    unsigned char count;
    unsigned char b3;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char flags;
} CmdHeader;
typedef struct {
    CmdHeader h;
    Vector pos;
    short u;
    short v;
    short w;
    short h2;
    int texture;
} CmdSprite;
typedef struct {
    CmdHeader h;
    Vector pos;
    short u;
    short v;
    short w;
    short h2;
    unsigned char r2;
    unsigned char g2;
    unsigned char b2;
    unsigned char pad;
    int extra[2];
} CmdQuad;
typedef struct {
    char pad0[4];
    char *ptr;
    char pad8[8];
    int remaining;
    int count;
    int texture;
} CmdPool;
typedef struct {
    char pad0[8];
    Vector pos;
    int dx;
    int dz;
    char pad1C[0x2A - 0x1C];
    unsigned char size;
    char pad2B[0x2E - 0x2B];
    short glow;
} Flare;
extern CmdPool D_800AD9EC;
extern int D_800ADA04;

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

static inline int fixed_round(int value) {
    int result;

    if (value >= 0) {
        result = value + 2048 >= 0 ? (value + 2048) >> 12 : -(-(value + 2048) >> 12);
    } else {
        result = value - 2048 >= 0 ? (value - 2048) >> 12 : -(-(value - 2048) >> 12);
    }
    return result;
}

static inline void *cmd_alloc(CmdPool *pool, int size, unsigned char type) {
    register CmdHeader *cmd asm("$4");
    int rem;
    int left;

    cmd = 0;
    rem = pool->remaining;
    left = rem - size;
    if (left > 0) {
        cmd = (CmdHeader *)pool->ptr;
        pool->remaining = left;
        {
            register int c asm("$2") = pool->count + 1;
            pool->ptr += size;
            pool->count = c;
        }
        cmd->type = type;
        cmd->count = 0;
    }
    return cmd;
}

static inline void *tail_alloc(CmdPool *pool, int size, unsigned char type) {
    register CmdHeader *cmd asm("$4");
    int rem;
    int left;

    cmd = 0;
    rem = pool->remaining;
    left = rem - size;
    if (left > 0) {
        cmd = (CmdHeader *)pool->ptr;
        pool->remaining = left;
        {
            register int c asm("$3") = pool->count + 1;
            pool->ptr += size;
            pool->count = c;
        }
        cmd->type = type;
        cmd->count = 0;
    }
    return cmd;
}

static inline void *sprite_alloc(CmdPool *pool, int size, int type) {
    register CmdHeader *cmd asm("$4");
    int rem;
    int left;

    cmd = 0;
    rem = pool->remaining;
    left = rem - size;
    if (left > 0) {
        cmd = (CmdHeader *)pool->ptr;
        pool->remaining = left;
        {
            register int c asm("$2") = pool->count + 1;
            pool->ptr += size;
            pool->count = c;
        }
        cmd->type = size / 4;
        cmd->count = 0;
    }
    return cmd;
}

static inline void glow_pair_hot(Vector *pos, Vector *tail, int scale) {
    CmdQuad *q;
    CmdSprite *s;

    q = cmd_alloc(&D_800AD9EC, 40, 10);
    if (q == 0) {
        return;
    }
    {
        int c = 128;

        q->pos = *pos;
        __asm__("");
        q->h.r = c;
        q->h.g = 40;
        q->h.b = 0;
        q->r2 = c;
    }
    q->g2 = 40;
    q->b2 = 0;
    q->h.b3 = 8;
    q->h.flags = 56;
    q->u = 0;
    q->h.b1 = 0;
    q->v = 0;
    q->h.b1 = 32;
    q->w = fixed_mul(scale, 12);
    q->h2 = fixed_mul(scale, 12);
    q->v = 0;
    q->u = 32;
    q->h.flags |= 2;
    s = tail_alloc(&D_800AD9EC, 32, 8);
    if (s == 0) {
        return;
    }
    s->pos = *tail;
    ((CmdQuad *)s)->h.r = 16;
    ((CmdQuad *)s)->h.g = 0;
    ((CmdQuad *)s)->h.b = 0;
    ((CmdQuad *)s)->r2 = 16;
    ((CmdQuad *)s)->g2 = 0;
    ((CmdQuad *)s)->b2 = 0;
    s->w = fixed_mul(scale, 12);
    s->h2 = fixed_mul(scale, 12);
    s->h.flags = 56;
    s->v = 0;
    ((unsigned char *)q)[0] += ((unsigned char *)s)[0];
    ((unsigned char *)q)[2]++;
    s->v = 0;
    s->h.flags |= 2;
}

static inline void glow_pair_cool(Vector *pos, Vector *tail, int scale) {
    CmdQuad *q;
    CmdSprite *s;

    q = cmd_alloc(&D_800AD9EC, 40, 10);
    if (q == 0) {
        return;
    }
    {
        int c = 128;

        q->pos = *pos;
        __asm__("");
        q->h.r = c;
        q->h.g = 40;
        q->h.b = 0;
        q->r2 = c;
    }
    q->g2 = 40;
    q->b2 = 0;
    q->h.b3 = 8;
    q->h.flags = 56;
    q->u = 0;
    q->h.b1 = 0;
    q->v = 0;
    q->h.b1 = 16;
    q->w = fixed_mul(scale, 12);
    q->h2 = fixed_mul(scale, 12);
    q->v = 0;
    q->u = 32;
    q->h.flags |= 2;
    s = tail_alloc(&D_800AD9EC, 32, 8);
    if (s == 0) {
        return;
    }
    s->pos = *tail;
    ((CmdQuad *)s)->h.r = 16;
    __asm__("");
    ((CmdQuad *)s)->h.g = 0;
    ((CmdQuad *)s)->h.b = 0;
    ((CmdQuad *)s)->r2 = 16;
    ((CmdQuad *)s)->g2 = 0;
    ((CmdQuad *)s)->b2 = 0;
    s->w = fixed_mul(scale, 12);
    s->h2 = fixed_mul(scale, 12);
    s->h.flags = 56;
    s->v = 0;
    ((unsigned char *)q)[0] += ((unsigned char *)s)[0];
    ((unsigned char *)q)[2]++;
    s->v = 0;
    s->h.flags |= 2;
}

void func_80037E64(Flare *flare)
{
    register Flare *f asm("$8") = flare;
    Vector pts[2];
    CmdSprite *s;
    int scale;
    int scale2;

    scale = (fixed_div(f->size, 2) + 4096) / 2;
    pts[0].x = fixed_round(f->pos.x);
    pts[0].y = fixed_round(f->pos.y);
    pts[0].z = fixed_round(f->pos.z);
    pts[1].x = pts[0].x - fixed_mul(scale * 2, f->dx) / 4096;
    pts[1].y = pts[0].y;
    pts[1].z = pts[0].z - fixed_mul(scale * 2, f->dz) / 4096;
    s = sprite_alloc(&D_800AD9EC, 32, 8);
    if (s != 0) {
        s->pos = pts[0];
        s->h.r = 192;
        s->h.g = 128;
        s->h.b = 64;
        s->h.b3 = 9;
        s->h.flags = 44;
        s->h.b1 = 0;
        s->texture = D_800ADA04 + 252;
        s->u = 0;
        s->v = 0;
        s->h.b1 = 0;
        s->v = 512;
        s->w = fixed_mul(scale, 20);
        s->h2 = fixed_mul(scale, 20);
        s->u = 32;
        s->h.flags |= 2;
    }
    if (f->glow == 0) {
        return;
    }
    glow_pair_hot(&pts[0], &pts[1], scale);
    glow_pair_cool(&pts[0], &pts[1], scale);
}
