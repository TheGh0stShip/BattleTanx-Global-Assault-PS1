typedef struct Bytes8 {
    unsigned char b[8];
} Bytes8;

typedef struct Source {
    char pad[0x1C];
    int size;
} Source;

typedef struct Sprite {
    int pad0;
    int scale_x;
    int scale_y;
    Bytes8 color;
    short angle;
    short rx;
    short ry;
    short rz;
    char pad1C[2];
    signed char spin;
    unsigned char visible;
    short radius;
    short drift;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char mode;
} Sprite;

extern unsigned int func_80086C84(void);

static inline int rand_span(int lo, int span) {
    return lo + ((int)(func_80086C84() >> 16) * span >> 16);
}

static inline int scale_fixed(int a, int b) {
    return a * b / 4096;
}

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_8006FA18(Source *src, Sprite *sprite, Bytes8 *color) {
    int scale;
    int spin;

    sprite->color = *color;
    sprite->rx = 0;
    sprite->ry = fixed_mul(src->size, 10240) >> 8;
    sprite->rz = 0;
    sprite->angle = func_80086C84() >> 16;
    spin = ((int)(func_80086C84() >> 16) * 129 >> 16) - 64;
    sprite->spin = spin;
    sprite->spin = ((signed char)spin << 12) / src->size;
    scale = src->size * 18;
    sprite->scale_x = scale;
    sprite->scale_y = scale;
    sprite->radius = scale_fixed(rand_span(48, 1), src->size);
    sprite->drift = scale_fixed((func_80086C84() >> 30) + 1, src->size);
    sprite->r = 64;
    sprite->g = 8;
    sprite->visible = 2;
    sprite->b = 64;
    sprite->mode = 1;
}
