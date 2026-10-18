typedef struct { int x, y, z; } Vector;
typedef struct { int x, z; } Point2;
typedef struct Marker Marker;
typedef struct { int pad[2]; Marker *marker; Vector pos; unsigned char id; } Base;
struct Marker {
    int pad[2];
    int arg2;
    int zero0;
    int arg1;
    Base *base;
    Base *home;
    int zero1;
    Vector pos;
    int pad2;
    unsigned char id_a;
    unsigned char id_b;
    unsigned short flags;
};
Marker *func_800237D0(int, int);
int func_8001EA3C(Point2 *);

void func_800334F8(Base *base, int arg1, int arg2) {
    Marker *m;
    Point2 p;

    m = func_800237D0(8, 52);
    if (m != 0) {
        m->arg2 = arg2;
        m->zero0 = 0;
        m->arg1 = arg1;
        m->id_a = m->id_b = base->id;
        m->base = base;
        m->home = base;
        m->zero1 = 0;
        base->marker = m;
        m->pos = base->pos;
        p.x = m->pos.x;
        p.z = m->pos.z;
        m->pos.y = func_8001EA3C(&p) + 0x64000;
        m->flags = 0xFFFF;
    }
}
