typedef struct {
    int pad0;
    short pad4;
    unsigned short angle;
    int pad8;
    int total;
    int remaining;
    char pad14[0x30 - 0x14];
    unsigned short intensity;
    short speed;
    unsigned char base_r, base_g, base_b;
    unsigned char r, g, b;
    unsigned char sound;
} Glow;

extern int D_800DE30C;
extern void func_80023EA0(int value);
extern void func_80024284(void);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_80071C7C(Glow *g, int *done) {
    int v;
    Glow *self = g;

    if (g->remaining > 0) {
        g->angle += fixed_mul(D_800DE30C, g->speed);
        if (g->sound) {
            v = fixed_mul(0x1B58000, (short)g->angle);
            if (v >= 0) {
                v >>= 12;
            } else {
                v = -(-v >> 12);
            }
            func_80023EA0(v);
        }
        self->intensity -= (short)self->intensity * D_800DE30C / self->remaining;
        if ((short)self->intensity < 0) {
            self->intensity = 0;
        }
        self->r = self->base_r * self->remaining / self->total;
        self->g = self->base_g * self->remaining / self->total;
        self->b = self->base_b * self->remaining / self->total;
        self->remaining -= D_800DE30C;
        *done = 0;
    } else {
        if (g->sound) {
            func_80024284();
        }
        *done = 1;
    }
}
