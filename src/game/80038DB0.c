typedef struct { int x; int y; int z; } Vector;
typedef struct { int a; int b; } Pair;
typedef struct {
    int f0;
    int f4;
    Vector pos;
    Pair p1;
    Pair p2;
    short f24;
    short f26;
    short f28;
    unsigned char f2A;
    unsigned char f2B;
    short kind;
    short f2E;
    int f30;
    int f34;
} Spark;
extern Spark *func_800237D0(int, int);
extern void func_8006C334(void *, int, Vector *, Vector *, int, int, int, int);
extern unsigned int func_80086C84(void);

void func_80038DB0(Vector *pos, Pair *p1, Pair *p2, short f24, unsigned char f2A, unsigned int kind, int f30, unsigned char f2B, int f34)
{
    Spark *s;
    Vector lo;
    Vector hi;

    s = func_800237D0(39, 60);
    if (s == 0) {
        return;
    }
    s->f2B = f2B;
    s->kind = kind;
    s->pos.x = pos->x;
    s->pos.y = pos->y;
    s->pos.z = pos->z;
    s->p1.a = p1->a;
    s->p1.b = p1->b;
    s->p2.a = p2->a;
    s->p2.b = p2->b;
    s->f2A = f2A;
    s->f24 = f24;
    s->f26 = 201;
    s->f28 = 201;
    s->f34 = f34;
    s->f30 = f30;
    s->f2E = 0;
    func_8006C334(0, 1, &s->pos, &s->pos, 0, 2816, 8192, 4096);
    switch (kind) {
    case 0:
        break;
    case 1:
        s->pos.x += (func_80086C84() >> 16) - 32768;
        s->pos.y += (func_80086C84() >> 16) - 32768;
        s->pos.z += (func_80086C84() >> 16) - 32768;
        break;
    case 2:
        lo.x = -65536;
        lo.y = -65536;
        lo.z = -65536;
        hi.x = 65536;
        hi.y = 65536;
        hi.z = 65536;
        func_8006C334(s, 0, &lo, &hi, 0, 5120, 6144, 0x7FFFFFFF);
        func_8006C334(s, 1, &lo, &hi, 0, 5120, 4096, 0x7FFFFFFF);
        break;
    }
}
