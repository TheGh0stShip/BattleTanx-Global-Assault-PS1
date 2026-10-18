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

typedef struct {
    char pad[0x1C];
    int scale;
} Emitter;

extern unsigned int func_80086C84(void);

void func_8006F298(Emitter *em, Particle *p, SVec *pos) {
    int t;

    p->pos = *pos;
    p->v16 = 0;
    p->v18 = 0;
    p->v1A = 0;
    p->angle = func_80086C84() >> 16;
    p->spin = ((int)(func_80086C84() >> 16) * 129 >> 16) - 64;
    t = em->scale * 6;
    p->a = t;
    p->b = t;
    p->speed = ((int)(func_80086C84() >> 16) * 33 >> 16 | 0x40) * em->scale / 4096;
    p->gravity = -10;
    p->r = 96;
    p->g = 96;
    p->b2 = 96;
    p->active = 1;
    p->kind = 2;
}
