typedef struct {
    int x, y, z;
} Vector;

typedef struct {
    char pad[8];
    Vector pos;
    int vx;
    int vy;
    int vz;
    int scale;
    short a;
    short b;
    short age;
    unsigned short spin;
    int owner;
} Debris;

extern Debris *func_800237D0(int kind, int size);
extern unsigned int func_80086C84(void);
extern int func_8008AD60(int angle);
extern int func_8008ACC0(int angle);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

typedef struct {
    short x, y, z, pad;
} SVecUnused;

void func_800735C8(Vector *pos, unsigned short heading, int a, int b, int owner) {
    Debris *d;
    int angle;
    SVecUnused spare;

    angle = heading >> 4;
    d = func_800237D0(7, 48);
    if (d != 0) {
        angle += (unsigned short)(((int)(func_80086C84() >> 16) * 65 >> 16) - 32);
        d->pos = *pos;
        d->vx = fixed_mul(func_8008AD60(angle), 0xA0000);
        d->vz = fixed_mul(func_8008ACC0(angle), 0xA0000);
        d->vy = 0;
        d->a = a;
        d->b = b;
        d->scale = 0x10000;
        d->age = 0;
        d->spin = func_80086C84() >> 16;
        d->owner = owner;
    }
}
