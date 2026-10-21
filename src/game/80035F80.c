typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    volatile unsigned char type;
    volatile unsigned char b1;
    volatile unsigned char b2;
    volatile unsigned char b3;
    volatile unsigned char r;
    volatile unsigned char g;
    volatile unsigned char b;
    volatile unsigned char flags;
} CmdHeader;
typedef struct {
    CmdHeader h;
    Vector position;
    short u;
    short v;
    short w;
    short h2;
    int texture;
} CmdSprite;
typedef struct {
    CmdHeader h;
    Vector position;
    short u;
    short v;
    short w;
    short h2;
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
    Vector position;
    Vector direction;
    int length;
    char pad24[8];
    int size;
} Beam;
extern CmdPool D_800AD9EC;
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

static inline int fixed_div(int numerator, int denom) {
    register int denominator asm("$6") = denom;
    int negative;
    int n;
    int sign;
    register int d asm("$8");
    int n_zeros;
    int d_zeros;
    register int excess asm("$7");
    int scale;
    unsigned int quotient;
    register int divisor asm("$2");
    int result;

    sign = numerator & 0x80000000;
    d = abs(denominator);
    negative = sign ^ (denominator & 0x80000000);
    __asm__("" : : "r"(negative));
    n = abs(numerator);
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

static inline void *cmd_alloc(CmdPool *pool, int size, int type) {
    CmdHeader *cmd = 0;
    register int rem asm("$2");
    register int left asm("$3");

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
        cmd->type = size >> 2;
        cmd->b2 = 0;
    }
    return cmd;
}

void func_80035F80(Beam *beam) {
    Vector ends[2];
    int scale;
    CmdSprite *sprite;
    CmdSprite *glow;
    CmdQuad *quad;

    scale = (fixed_div(beam->size, 50) + 4096) / 2;
    ends[0].x = fixed_round(beam->position.x);
    ends[0].y = fixed_round(beam->position.y);
    ends[0].z = fixed_round(beam->position.z);
    ends[1].x = fixed_round(beam->position.x + fixed_mul(beam->length, beam->direction.x));
    ends[1].y = fixed_round(beam->position.y + fixed_mul(beam->length, beam->direction.y));
    ends[1].z = fixed_round(beam->position.z + fixed_mul(beam->length, beam->direction.z));

    sprite = cmd_alloc(&D_800AD9EC, 32, 8);
    if (sprite != 0) {
        sprite->position = ends[0];
        sprite->h.r = 0;
        sprite->h.g = 32;
        sprite->h.b = 128;
        sprite->h.b3 = 9;
        sprite->h.flags = 44;
        sprite->h.b1 = 0;
        sprite->u = 0;
        sprite->v = 0;
        sprite->texture = D_800ADA04 + 252;
        sprite->h.b1 = 0;
        sprite->v = func_80086C84() >> 16;
        sprite->w = fixed_mul(scale, 24);
        sprite->h2 = fixed_mul(scale, 24);
        sprite->u = 32;
        sprite->h.flags |= 2;
    }
    sprite = cmd_alloc(&D_800AD9EC, 32, 8);
    if (sprite != 0) {
        sprite->position = ends[1];
        sprite->h.r = 0;
        sprite->h.g = 32;
        sprite->h.b = 128;
        sprite->h.b3 = 9;
        sprite->h.flags = 44;
        sprite->h.b1 = 0;
        sprite->u = 0;
        sprite->v = 0;
        sprite->texture = D_800ADA04 + 252;
        sprite->h.b1 = 0;
        sprite->v = func_80086C84() >> 16;
        sprite->w = fixed_mul(scale, 24);
        sprite->h2 = fixed_mul(scale, 24);
        sprite->u = 32;
        sprite->h.flags |= 2;
    }
    glow = cmd_alloc(&D_800AD9EC, 32, 8);
    if (glow != 0) {
        int g = 32;
        __asm__("" : "=r"(g) : "0"(g));
        glow->position = ends[0];
        glow->h.r = 0;
        __asm__ volatile("");
        glow->h.b = 128;
        glow->h.b3 = 9;
        glow->h.flags = 44;
        glow->h.g = g;
        glow->h.b1 = 0;
        glow->u = 0;
        glow->v = 0;
        glow->texture = D_800ADA04 + 216;
        glow->h.b1 = g;
        glow->w = fixed_mul(scale, 24);
        glow->h2 = fixed_mul(scale, 24);
        glow->v = 0;
        glow->u = 32;
        glow->h.flags |= 2;
    }
    quad = cmd_alloc(&D_800AD9EC, 28, 7);
    if (quad != 0) {
        quad->position = ends[1];
        quad->h.r = 0;
        quad->h.g = 32;
        quad->h.b = 128;
        quad->w = fixed_mul(scale, 24);
        quad->h2 = fixed_mul(scale, 24);
        quad->h.flags = 44;
        quad->v = 0;
        ((unsigned char *)glow)[0] += ((unsigned char *)quad)[0];
        ((unsigned char *)glow)[2]++;
        quad->v = 0;
        quad->h.flags |= 2;
    }
    glow = cmd_alloc(&D_800AD9EC, 32, 8);
    if (glow != 0) {
        glow->position = ends[0];
        glow->h.r = 0;
        glow->h.g = 32;
        glow->h.b = 128;
        glow->h.b3 = 9;
        glow->h.flags = 44;
        glow->h.b1 = 0;
        glow->u = 0;
        glow->v = 0;
        glow->texture = D_800ADA04 + 216;
        glow->h.b1 = 16;
        glow->w = fixed_mul(scale, 24);
        glow->h2 = fixed_mul(scale, 24);
        glow->v = 0;
        glow->u = 32;
        glow->h.flags |= 2;
    }
    quad = cmd_alloc(&D_800AD9EC, 28, 7);
    if (quad != 0) {
        quad->position = ends[1];
        quad->h.r = 0;
        quad->h.g = 32;
        quad->h.b = 128;
        quad->w = fixed_mul(scale, 24);
        quad->h2 = fixed_mul(scale, 24);
        quad->h.flags = 44;
        quad->v = 0;
        ((unsigned char *)glow)[0] += ((unsigned char *)quad)[0];
        ((unsigned char *)glow)[2]++;
        quad->v = 0;
        quad->h.flags |= 2;
    }
}
