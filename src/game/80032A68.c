typedef struct { int x, y, z; } Vector;
typedef struct { int x, z; } Point2;
typedef struct {
    int pad[2];
    int kind;
    int active;
    int resource;
    void *base;
    void *home;
    int link;
    Vector pos;
    int pad2;
    unsigned char id_a;
    unsigned char id_b;
    unsigned short flags;
} Marker;
typedef struct { short pad; unsigned short body; } Def;
extern unsigned int D_800D2FE8;
extern int D_800D5AA0;
int func_80026300(void *, int);
Marker *func_800237D0(int, int);
int func_8001EA3C(Point2 *);

static inline void spawn(Def *def, void *ctx, Vector *pos, int kind) {
    int res;
    Marker *m;
    Point2 p;

    res = func_80026300(ctx, def->body);
    m = func_800237D0(8, 52);
    if (m != 0) {
        m->pos = *pos;
        p.x = m->pos.x;
        p.z = m->pos.z;
        m->pos.y = func_8001EA3C(&p) + 0x32000;
        m->flags = 0xFFFF;
        m->id_a = m->id_b = 127;
        m->active = 1;
        m->kind = kind;
        m->home = 0;
        m->base = 0;
        m->resource = res;
        m->link = 0;
    }
}

void func_80032A68(Def *def, void *ctx, Vector *where) {
    Vector *pos = where;
    switch (D_800D2FE8) {
    case 2:
        D_800D5AA0 = func_80026300(ctx, def->body);
        break;
    case 7:
    case 13:
        spawn(def, ctx, pos, 2);
        break;
    case 3:
    case 14:
        spawn(def, ctx, pos, 1);
        break;
    }
}
