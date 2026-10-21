typedef struct { int x; int y; int z; } Vector;
typedef struct { short f0; short f2; short type; } Hittable;
typedef struct { Hittable *obj; int f4; Vector pos; int pad[5]; } HitResult;
typedef struct { int w[7]; } Reply;
typedef struct { Vector pos; unsigned short kind; int a; int b; int c; int f1C; int f20; int f24; } HitInfo;
typedef struct { int f0; void (*handler)(Hittable *, void *, int, HitInfo *, Reply *); int f8; } HitClass;
typedef struct {
    int f0;
    int f4;
    Vector pos;
    int vx;
    int vz;
    int ax;
    int az;
    unsigned short kind;
    short arm_time;
    short life;
    unsigned char a;
    unsigned char c;
    short big;
    short armed;
    int mask;
    int b;
} Shot;
extern int D_800DE30C;
extern short D_800C628C;
extern Reply D_800BE7B0;
extern HitClass D_800D32F4[];
extern unsigned short func_80019D80(Vector *, Vector *, int, int, int, HitResult *);
extern void func_8006FDB0(int, Vector *, int, int);
extern void func_80053790(int, int, int);
extern int func_800248CC(short, short);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int to_int(int v)
{
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

static inline void impact(Shot *s, Vector *p)
{
    if (s->big == 1) {
        func_8006FDB0(8, p, 0, 0);
    } else {
        func_8006FDB0(4, p, 0, 0);
    }
    func_80053790(45, p->x, p->z);
}

void func_80037B3C(Shot *s, int *done)
{
    Vector next;
    HitResult hit;
    HitInfo info;
    Reply reply;
    int scale;
    Hittable *obj;
    Shot *self;

    self = s;
    if (--s->life <= 0) {
        *done = 1;
        return;
    }
    if (s->life <= s->arm_time - 1) {
        s->armed = 1;
    }
    scale = D_800DE30C;
    next.x = s->pos.x + fixed_mul(scale, s->vx);
    next.z = s->pos.z + fixed_mul(scale, s->vz);
    next.y = s->pos.y;
    s->vx += fixed_mul(scale, s->ax);
    s->vz += fixed_mul(scale, s->az);
    D_800C628C = 1;
    if (func_80019D80(&s->pos, &next, 0x64940B, 0, s->mask, &hit)) {
        if (hit.obj != 0) {
            reply = D_800BE7B0;
            info.pos = hit.pos;
            info.kind = s->kind;
            info.a = s->a;
            info.b = s->b;
            info.c = s->c;
            info.f20 = 0;
            obj = hit.obj;
            if (D_800D32F4[obj->type].handler != 0 && obj->type != -1) {
                D_800D32F4[obj->type].handler(hit.obj, s, 0, &info, &reply);
            }
        }
        impact(self, &hit.pos);
        *done = 1;
        return;
    }
    s->pos.x = next.x;
    s->pos.z = next.z;
    if (func_800248CC(to_int(next.x) >> 2, to_int(next.z) >> 2) == 0) {
        *done = 1;
    }
}
