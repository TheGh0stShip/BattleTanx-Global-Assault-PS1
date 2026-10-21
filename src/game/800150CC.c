typedef struct SVec3 {
    short x;
    short y;
    short z;
} SVec3;
typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;
typedef struct Matrix Matrix;
typedef struct View {
    short fov;
    char pad02[6];
    Vector pos;
    char pad14[0x24 - 0x14];
    short scale_x;
    short scale_y;
    SVec3 rot;
    char pad2E[0x90 - 0x2E];
    SVec3 angle;
    SVec3 offset;
} View;
void func_80015318(View *, short, Matrix *, SVec3 *, Vector *);
short func_80015458(View *, Vector *, Vector *);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

int abs(int);

static inline int imul(int a, int b) {
    return a * b;
}

static inline int to_int1(int v) {
    return v < 0 ? -(-v >> 12) : (unsigned int)v >> 12;
}

void func_800150CC(View *view, Vector *target, Matrix *m) {
    Vector res;
    SVec3 rel;
    Vector probe;
    short x;
    short y;
    int d = (short)((x = view->scale_x) - (y = view->scale_y));
    int ad = abs(d);
    short t;
    short s;
    int v;
    int k;
    int px;
    int py;
    int pz;
    int f;
    int step;
    register unsigned short old asm("$3");
    int grown;

    if (ad < 9) {
        step = 4;
    } else if (ad < 17) {
        step = 2;
    } else {
        goto grow;
    }
    view->scale_x = y + d / step;
grow:
    old = view->scale_x;
    grown = old;
    __asm__("" : "=r"(grown) : "0"(grown));
    grown = (short)(grown + 204);
    view->scale_x = grown;
    view->scale_y = old;
    if (grown > 4096) {
        view->scale_x = 4096;
    }
    func_80015318(view, view->scale_x, m, &rel, &res);
    px = target->x;
    py = res.y;
    pz = target->z;
    probe.x = px;
    probe.y = py;
    probe.z = pz;
    t = func_80015458(view, &probe, &res);
    if (t < 4096) {
        v = imul(t, 3993);
        t = (unsigned int)v >> 12;
        if (v < 0) {
            t = -(-v >> 12);
        }
    }
    s = to_int1(view->scale_x * t);
    view->scale_x = s;
    func_80015318(view, s, m, &view->rot, &view->pos);
    f = fixed_mul(view->scale_x, (view->angle.z << 16) / 36000);
    view->fov = f;
    k = (view->offset.z << 16) / 36000;
    view->fov = f + fixed_mul(4096 - view->scale_x, k);
}
