typedef struct { unsigned addr : 24; unsigned len : 8; } Tag;
typedef struct {
    Tag tag;
    unsigned char r0;
    unsigned char g0;
    unsigned char b0;
    unsigned char code;
    short x0;
    short y0;
    short x1;
    short y1;
    short x2;
    short y2;
    short x3;
    short y3;
} PolyF4;
typedef struct { char data[0x5C]; } DrawEnv;
typedef struct { short x; short y; short w; short h; char rest[0x14 - 8]; } DispEnv;
typedef struct { DrawEnv draw[2]; DispEnv disp; int ot; char pad[0x128 - 0xD0]; } Screen;
extern Screen D_800DDB9C[];
extern int D_800A48B0;
extern int D_800A48B4;
extern Tag D_800D5B8C[][4098];
extern PolyF4 *func_80068EE8(int);

static inline Screen *current_screen(void)
{
    return &D_800DDB9C[D_800A48B0];
}

static inline int half(int v)
{
    return (short)v / 2;
}

static inline int last(int v)
{
    return v - 1;
}

void func_8003EC24(void)
{
    PolyF4 *p;
    DispEnv *disp;
    Tag *ot;

    p = func_80068EE8(sizeof(PolyF4));
    if (p != 0) {
        p->tag.len = 5;
        p->code = 0x28;
        p->r0 = 60;
        p->g0 = 60;
        p->b0 = 60;
        disp = &current_screen()->disp;
        p->x0 = 0;
        p->y0 = half(disp->h) - 1;
        p->x1 = last(disp->w);
        p->y1 = half(disp->h) - 1;
        p->x2 = 0;
        p->y2 = half(disp->h);
        p->x3 = last(disp->w);
        p->y3 = half(disp->h);
        ot = &D_800D5B8C[D_800A48B4][0];
        p->tag.addr = ot->addr;
        ot->addr = (unsigned int)p;
    }
}
