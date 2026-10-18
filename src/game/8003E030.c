typedef struct { char pad[8]; unsigned short w; unsigned short h; } Img;
typedef struct {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    unsigned short *clut;
    int size;
    int f20;
    Img *img;
} Conv;
extern unsigned short *func_80068F34(int);
extern void func_80068F9C(unsigned short *);
extern void func_8003CA54(Conv *);
extern int D_800DE0B0;
extern void func_8008BC74(int *, int, int, int, int, int, int);

void func_8003E030(void)
{
    Conv c;
    Conv *p;
    unsigned short *clut;
    int i;

    p = &c;

    p->f0 = 0;
    p->f14 = 1;
    p->f4 = 0;
    p->f8 = 0;
    p->fC = 0;
    p->f10 = 0;
    p->size = 32;
    p->clut = clut = func_80068F34(32);
    clut[0] = 0;
    for (i = 1; i < 16; i++) {
        clut[i] = 0xC210;
    }
    func_8003CA54(p);
    func_8008BC74(&D_800DE0B0, p->img->w, p->img->h, p->img->w, p->img->h, p->f8, 0);
    func_80068F9C(p->clut);
}
