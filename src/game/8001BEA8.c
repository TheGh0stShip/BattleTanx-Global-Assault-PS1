typedef struct Body {
    char pad00[0x2C];
    int height;
    char pad30[0x38 - 0x30];
    unsigned short pitch;
    unsigned short roll;
    char pad3C[0x60 - 0x3C];
    void *segment;
} Body;
extern int D_800DE30C;
short func_80047B28(unsigned short, unsigned short, unsigned short *);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int imul(int a, int b) {
    return a * b;
}

static inline int to_int(int v) {
    if (v >= 0) {
        v >>= 12;
    } else {
        v = -(-v >> 12);
    }
    return v;
}

static inline int to_int2(int v) {
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

static inline void decay_angle(unsigned short *a) {
    if (*a > 0x8000) {
        *a += 60;
    } else if (*a > 60) {
        *a -= 60;
    } else {
        *a = 0;
    }
}

void func_8001BEA8(Body *body, int height, unsigned short dir, unsigned short slope) {
    unsigned short delta;

    if (body->segment != 0) {
        body->pitch = 0;
        decay_angle(&body->roll);
        body->roll += to_int(imul(body->height - height, 0x2D8000));
        body->height = height;
        return;
    }
    if (body->roll != 0) {
        if (body->roll > 0x8000) {
            body->roll += to_int(fixed_mul(D_800DE30C, 0x2D8000));
            if ((short)body->roll >= 0) {
                body->roll = 0;
            }
        } else {
            body->roll -= to_int2(fixed_mul(D_800DE30C, 0x2D8000));
            if (body->roll > 0x8000) {
                body->roll = 0;
            }
        }
    }
    if (func_80047B28(dir, slope, &delta) < 0) {
        body->roll -= delta;
    } else {
        body->roll += delta;
    }
    if (body->roll > 0x8000) {
        if (body->roll <= 0xFB04) {
            body->roll = 0xFB05;
        }
    } else if (body->roll > 1820) {
        body->roll = 1820;
    }
    decay_angle(&body->pitch);
    body->pitch += to_int(fixed_mul(body->height - height, 0x2D8000));
    body->height = height;
}
