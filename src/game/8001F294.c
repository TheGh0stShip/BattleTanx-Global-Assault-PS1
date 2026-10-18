typedef struct Body {
    char pad00[0x14];
    int friction;
    char pad18[0x1C - 0x18];
    int speed;
} Body;
extern int D_800DE30C;

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
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

unsigned short func_8001F294(Body *body) {
    int result = to_int(imul(body->speed, 20));
    int speed;
    int decel;

    if ((speed = body->speed) != 0) {
        decel = fixed_mul(D_800DE30C, body->friction);
        if (decel > 0) {
            if (speed > 0) {
                body->speed = speed - decel;
                if (body->speed < 0) {
                    body->speed = 0;
                }
            } else {
                body->speed = speed + decel;
                if (body->speed > 0) {
                    body->speed = 0;
                }
            }
        }
    }
    return result;
}
