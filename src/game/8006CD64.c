typedef struct {
    short x, y, z, pad;
} SVec;

typedef struct {
    int pad0;
    int a;
    int b;
    SVec pos;
    unsigned short angle;
    short v16;
    short v18;
    short v1A;
    short v1C;
    signed char spin;
    char active;
    short speed;
    short gravity;
    unsigned char r, g, b2;
    char kind;
} Particle;

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

typedef struct {
    char pad[0x1C];
    int scale;
    char pad20[0xC];
    short spread_x;
    short spread_y;
    short spread_z;
} Emitter;

extern unsigned int func_80086C84(void);

static inline int rand_span(int lo, int span) {
    return lo + ((int)(func_80086C84() >> 16) * span >> 16);
}

void func_8006CD64(Emitter *em, Particle *p, SVec *pos) {
    p->pos = *pos;
    p->v16 = (unsigned short)(((int)(func_80086C84() >> 16) * (em->spread_x * 2 + 1) >> 16) - em->spread_x) >> 8;
    p->v18 = (unsigned short)(((int)(func_80086C84() >> 16) * (em->spread_y * 2 + 1) >> 16) - em->spread_y) >> 8;
    p->v1A = (unsigned short)(((int)(func_80086C84() >> 16) * (em->spread_z * 2 + 1) >> 16) - em->spread_z) >> 8;
    p->angle = func_80086C84() >> 16;
    p->a = 4096;
    p->b = 4096;
    p->speed = (((int)(func_80086C84() >> 16) * 9 >> 16) + 24) * em->scale / 4096;
    p->gravity = -(em->scale * 12) / 4096;
    p->r = 64;
    p->g = 32;
    p->b2 = 128;
    p->active = 1;
    p->kind = 4;
}
