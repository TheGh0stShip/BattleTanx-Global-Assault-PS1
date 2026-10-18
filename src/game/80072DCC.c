typedef struct {
    int pad0;
    int pad4;
    int a;
    int b;
    int x, y, z;
    int vx, vy, vz;
} Shell;

extern int D_800DE30C;
extern void func_8006F224(int handle, Shell *s);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_80072DCC(Shell *s, int *done) {
    int dt = D_800DE30C;

    s->x += fixed_mul(dt, s->vx);
    s->y += fixed_mul(dt, s->vy) + fixed_mul(fixed_mul(dt, dt), -2048);
    s->z += fixed_mul(dt, s->vz);
    s->vy += fixed_mul(dt, -4096);
    if (s->y < 0) {
        func_8006F224(s->a, s);
        func_8006F224(s->b, s);
        *done = 1;
    } else {
        *done = 0;
    }
}
