typedef struct { int x, y, z; } Vector;
typedef struct { int pad[2]; Vector pos; Vector vel; int state; int start_time; } Debris;
extern int D_800DE30C;
extern int D_800D2FE0;
unsigned int func_80086C84(void);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_8003475C(Debris *d, int *done) {
    Vector old;
    Vector nv;
    int vy;
    int state;

    old = d->pos;
    switch (d->state) {
    case 0:
        d->pos.x += fixed_mul(D_800DE30C, d->vel.x);
        d->pos.y += fixed_mul(D_800DE30C, d->vel.y);
        d->pos.z += fixed_mul(D_800DE30C, d->vel.z);
        d->vel.y -= 409;
        if (D_800D2FE0 - d->start_time >= 5) {
            d->state = 1;
        }
        break;
    case 1:
        nv.x = fixed_mul(3481, d->vel.x) + (func_80086C84() & 0x7FF) - 1024;
        nv.z = fixed_mul(3481, d->vel.z) + (func_80086C84() & 0x7FF) - 1024;
        vy = d->vel.y;
        if (vy > 0) {
            nv.y = fixed_mul(3481, vy) - 409;
        } else {
            nv.y = vy - 409;
        }
        if (nv.y < -16384) {
            nv.y = -16384;
        }
        d->pos.x += fixed_mul(D_800DE30C, (nv.x + d->vel.x) / 2);
        d->pos.y += fixed_mul(D_800DE30C, (nv.y + d->vel.y) / 2);
        d->pos.z += fixed_mul(D_800DE30C, (nv.z + d->vel.z) / 2);
        if (d->pos.y < 0) {
            *done = 1;
        } else {
            d->vel = nv;
        }
        break;
    }
}
