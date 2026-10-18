typedef struct {
    int x, y, z;
} Vector;

typedef struct {
    int pad0;
    int pad4;
    int a;
    int b;
    Vector pos;
    Vector vel;
} Shell;

extern Shell *func_800237D0(int kind, int size);
extern unsigned int func_80086C84(void);
extern int func_8006C334(Shell *s, int kind, int a, int b, int c, int size, int d, int seed);

void func_80072C50(int unused, Vector *pos, Vector *vel, int scale) {
    Shell *s;
    int seed;

    s = func_800237D0(69, 40);
    if (s != 0) {
        s->pos = *pos;
        if (vel == 0) {
            s->vel.x = (func_80086C84() >> 16) - 32768;
            s->vel.y = (func_80086C84() >> 16) + 16384;
            s->vel.z = (func_80086C84() >> 16) - 32768;
            s->vel.x *= 2;
            s->vel.y *= 2;
            s->vel.z *= 2;
        } else {
            s->vel = *vel;
        }
        seed = (func_80086C84() >> 16) + 0x30000;
        s->a = func_8006C334(s, 0, 0, 0, 0, scale * 13 * 256 / 4096, 3072, seed);
        s->b = func_8006C334(s, 3, 0, 0, 0, 4096, 2048, seed);
    }
}
