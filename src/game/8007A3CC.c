typedef struct Cycler {
    int value;
    int step;
    unsigned char *out;
    unsigned char base;
    unsigned char range;
    unsigned char reverse;
    unsigned char pad;
} Cycler;

extern int D_800C60D0;

static inline void Cycler_Step(Cycler *c) {
    int step = c->step;
    int v = c->value;
    int range;
    unsigned char base = c->base;
    unsigned char *out = c->out;
    unsigned char range8 = c->range;
    unsigned char reverse = c->reverse;

    if (step == 0) {
        return;
    }
    if (reverse) {
        v -= step;
    } else {
        v += step;
    }
    range = (signed char)range8;
    if (v * range < 0) {
        v += range << 12;
    }
    v %= range << 12;
    c->value = v;
    *out = base + (v >> 12);
}

void func_8007A3CC(Cycler *list) {
    int i = 0;

    if (D_800C60D0 == 7) {
        return;
    }
    for (; i < 5; i++) {
        if (list[i].out != 0) {
            Cycler_Step(&list[i]);
        }
    }
}
