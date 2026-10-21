typedef struct {
    unsigned int tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    unsigned short uv0;
    unsigned short clut;
    unsigned char r1, g1, b1, p1;
    short x1, y1;
    unsigned short uv1;
    unsigned short tpage;
    unsigned char r2, g2, b2, p2;
    short x2, y2;
    unsigned short uv2;
    unsigned short pad2;
    unsigned char r3, g3, b3, p3;
    short x3, y3;
    unsigned short uv3;
    unsigned short pad3;
} PolyGT4;

typedef struct {
    unsigned int hdr[2];
    unsigned int ot[4096];
} OtBuffer;

extern int D_800A48B4;
extern OtBuffer D_800D5B8C[];

static inline unsigned int *current_ot(void)
{
    return D_800D5B8C[D_800A48B4].ot;
}
extern PolyGT4 *func_80068EE8(int size);


static inline void add_prim(PolyGT4 *q)
{
    unsigned int *ot = &current_ot()[4094];

    q->tag = (q->tag & 0xFF000000) | (*ot & 0xFFFFFF);
    *ot = (*ot & 0xFF000000) | ((unsigned int)q & 0xFFFFFF);
}

static inline void set_quad(PolyGT4 *q, unsigned int *xy, unsigned short *uv,
                            unsigned int *rgb, int a, int b, int c, int d,
                            unsigned short clut, unsigned short tpage)
{
    q->uv0 = uv[a];
    *(unsigned int *)&q->r0 = rgb[a];
    *(unsigned int *)&q->x0 = xy[a];
    q->uv1 = uv[b];
    *(unsigned int *)&q->r1 = rgb[b];
    *(unsigned int *)&q->x1 = xy[b];
    q->uv2 = uv[c];
    *(unsigned int *)&q->r2 = rgb[c];
    *(unsigned int *)&q->x2 = xy[c];
    q->uv3 = uv[d];
    *(unsigned int *)&q->r3 = rgb[d];
    *(unsigned int *)&q->x3 = xy[d];
    ((unsigned char *)&q->tag)[3] = 12;
    q->code = 0x3C;
    q->clut = clut;
    q->tpage = tpage;
}

void func_8003AA1C(PolyGT4 *p)
{
    unsigned int xy[9];
    unsigned short uv[9];
    unsigned int rgb[9];
    unsigned int h0, h1, h2, h3;
    unsigned int q0;
    unsigned short clut, tpage;
    PolyGT4 *q;

    clut = p->clut;
    tpage = p->tpage;

    xy[0] = *(unsigned int *)&p->x0;
    xy[2] = *(unsigned int *)&p->x1;
    xy[6] = *(unsigned int *)&p->x2;
    xy[8] = *(unsigned int *)&p->x3;
    xy[1] = ((xy[0] & 0xFFFEFFFE) >> 1) + ((xy[2] & 0xFFFEFFFE) >> 1);
    xy[3] = ((xy[0] & 0xFFFEFFFE) >> 1) + ((xy[6] & 0xFFFEFFFE) >> 1);
    xy[4] = ((xy[0] & 0xFFFEFFFE) >> 1) + ((xy[8] & 0xFFFEFFFE) >> 1);
    xy[5] = ((xy[2] & 0xFFFEFFFE) >> 1) + ((xy[8] & 0xFFFEFFFE) >> 1);
    xy[7] = ((xy[6] & 0xFFFEFFFE) >> 1) + ((xy[8] & 0xFFFEFFFE) >> 1);

    uv[0] = p->uv0;
    uv[2] = p->uv1;
    uv[6] = p->uv2;
    uv[8] = p->uv3;
    uv[1] = ((uv[0] & 0xFEFE) >> 1) + ((uv[2] & 0xFEFE) >> 1);
    uv[3] = ((uv[0] & 0xFEFE) >> 1) + ((uv[6] & 0xFEFE) >> 1);
    uv[4] = ((uv[0] & 0xFEFE) >> 1) + ((uv[8] & 0xFEFE) >> 1);
    uv[5] = ((uv[2] & 0xFEFE) >> 1) + ((uv[8] & 0xFEFE) >> 1);
    uv[7] = ((uv[6] & 0xFEFE) >> 1) + ((uv[8] & 0xFEFE) >> 1);

    rgb[0] = *(unsigned int *)&p->r0;
    rgb[2] = *(unsigned int *)&p->r1;
    rgb[6] = *(unsigned int *)&p->r2;
    rgb[8] = *(unsigned int *)&p->r3;
    rgb[1] = ((rgb[0] & 0xFEFEFEFE) >> 1) + ((rgb[2] & 0xFEFEFEFE) >> 1);
    rgb[3] = ((rgb[0] & 0xFEFEFEFE) >> 1) + ((rgb[6] & 0xFEFEFEFE) >> 1);
    rgb[4] = ((rgb[0] & 0xFCFCFCFC) >> 2) + ((rgb[2] & 0xFCFCFCFC) >> 2)
           + ((rgb[6] & 0xFCFCFCFC) >> 2) + ((rgb[8] & 0xFCFCFCFC) >> 2);
    rgb[5] = ((rgb[2] & 0xFEFEFEFE) >> 1) + ((rgb[8] & 0xFEFEFEFE) >> 1);
    rgb[7] = ((rgb[6] & 0xFEFEFEFE) >> 1) + ((rgb[8] & 0xFEFEFEFE) >> 1);

    set_quad(p, xy, uv, rgb, 0, 1, 3, 4, clut, tpage);

    q = func_80068EE8(sizeof(PolyGT4));
    if (q == 0)
        return;
    set_quad(q, xy, uv, rgb, 1, 2, 4, 5, clut, tpage);
    add_prim(q);

    q = func_80068EE8(sizeof(PolyGT4));
    if (q == 0)
        return;
    set_quad(q, xy, uv, rgb, 3, 4, 6, 7, clut, tpage);
    add_prim(q);

    q = func_80068EE8(sizeof(PolyGT4));
    if (q == 0)
        return;
    set_quad(q, xy, uv, rgb, 4, 5, 7, 8, clut, tpage);
    add_prim(q);
}
