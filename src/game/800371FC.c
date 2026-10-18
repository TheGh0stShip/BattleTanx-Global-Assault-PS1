typedef struct { int x; int y; int z; } Vector;
typedef struct { unsigned short f0; unsigned short res; } Spec;
typedef struct {
    int f0;
    int f4;
    Vector pos;
    short id;
    short f16;
    int res;
    int f1C;
    int f20;
    int vy;
    short f28;
    short f2A;
    short f2C;
} Debris;
extern Debris *func_800237D0(int, int);
extern int func_80026300(int, int);
extern unsigned int func_80086C84(void);

void func_800371FC(Spec *spec, int owner, Vector *pos, short id)
{
    Debris *d;

    d = func_800237D0(50, 48);
    if (d != 0) {
        d->res = func_80026300(owner, spec->res);
        d->vy = -((func_80086C84() % 819 + 3686) * 40960);
        d->f1C = 0;
        d->id = id;
        d->pos = *pos;
        d->pos.y = 0x258000;
        d->f2C = 30;
        d->f20 = 0;
        d->f28 = func_80086C84() % 182 + 182;
        d->f2A = func_80086C84() % 182 + 182;
    }
}
