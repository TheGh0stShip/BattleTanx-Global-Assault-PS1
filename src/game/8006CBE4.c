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
} Emitter;

extern unsigned int func_80086C84(void);

static inline int rand_span(int lo, int span) {
    return lo + ((int)(func_80086C84() >> 16) * span >> 16);
}

void func_8006CBE4(Emitter *em, Particle *p, SVec *pos) {
    p->pos = *pos;
    p->v16 = 0;
    p->v18 = fixed_mul(em->scale, 0x5000) >> 8;
    p->v1A = 0;
    p->angle = func_80086C84() >> 16;
    p->spin = ((int)(func_80086C84() >> 16) * 129 >> 16) - 64;
    p->spin = (p->spin << 12) / em->scale;
    p->a = em->scale * 48;
    p->b = rand_span(0, 0) + p->a;
    p->speed = rand_span(48, 1) * em->scale / 4096;
    p->gravity = rand_span(1, 4) * em->scale / 4096;
    p->r = 32;
    p->g = 32;
    p->b2 = 32;
    p->active = 2;
    p->kind = 1;
}
