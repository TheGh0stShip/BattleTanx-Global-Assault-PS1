typedef struct { short pad[7]; short f0E; } Frame;
typedef struct { int f0; int f4; Frame *frame; } Res;
typedef struct { unsigned short f0; unsigned short a; unsigned short b; unsigned short c; } Spec;
typedef struct {
    int f0;
    int f4;
    int f8;
    short fC;
    short fE;
    int f10;
    int f14;
    int f18;
    int f1C;
    int ra;
    Res *rb;
    int rc;
    int f2C;
    int f30;
    unsigned short id;
} Effect;
extern Effect *func_800237D0(int, int);
extern int func_80026300(int, int);
extern short func_80024D80(int, int, int, int, int, Effect *);
extern int func_8002618C(int, int, int, int, int, int, int);

void func_80035DB8(Spec *spec, int owner, int pos, unsigned short id)
{
    Effect *e;

    e = func_800237D0(29, 56);
    if (e != 0) {
        e->ra = func_80026300(owner, spec->a);
        e->rb = (Res *)func_80026300(owner, spec->b);
        e->rc = func_80026300(owner, spec->c);
        e->f2C = 60;
        e->f10 = 0;
        e->f14 = 3;
        e->id = id;
        e->fC = func_80024D80(owner, pos, id, spec->b, 2, e);
        e->f1C = func_8002618C(owner, e->ra, pos, id, 2, 240, 1);
        e->f18 = -1000;
        e->f8 = e->rb->frame->f0E << 14;
        e->f30 = 0;
    }
}
