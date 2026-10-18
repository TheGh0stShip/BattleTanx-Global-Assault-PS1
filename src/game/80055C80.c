typedef struct {
    unsigned long tag;
    unsigned char r0;
    unsigned char g0;
    unsigned char b0;
    unsigned char code;
    short x0;
    short y0;
    unsigned char u0;
    unsigned char v0;
    unsigned short clut;
    short x1;
    short y1;
    unsigned char u1;
    unsigned char v1;
    unsigned short tpage;
    short x2;
    short y2;
    unsigned char u2;
    unsigned char v2;
    unsigned short pad1;
    short x3;
    short y3;
    unsigned char u3;
    unsigned char v3;
    unsigned short pad2;
} POLY_FT4;
typedef struct {
    unsigned short tpage;
    unsigned short clut;
    unsigned char u;
    unsigned char v;
    unsigned char w;
    unsigned char h;
} Image;
typedef struct {
    unsigned addr : 24;
    unsigned len : 8;
} P_TAG;
typedef struct {
    unsigned long ot[0x4008 / 4];
} OrderingTable;
extern OrderingTable D_800D5B8C[];
extern int D_800A48B4;
extern short D_800DDC58;
extern void *func_80068EE8(int);

static inline int to_int(int x) {
    return x >= 0 ? x >> 12 : -(-x >> 12);
}

static inline int round_fixed(int x) {
    return x >= 0 ? (x + 2048 >= 0 ? (x + 2048) >> 12 : -(-(x + 2048) >> 12))
                  : (x - 2048 >= 0 ? (x - 2048) >> 12 : -(-(x - 2048) >> 12));
}

static inline void set_uvwh(POLY_FT4 *p, Image *img, short w, short h) {
    p->u0 = img->u;
    p->v0 = img->v;
    p->u1 = img->u + w;
    p->v1 = img->v;
    p->u2 = img->u;
    p->v2 = img->v + h;
    p->u3 = img->u + w;
    p->v3 = img->v + h;
}

void func_80055C80(Image *img, short x, short y, unsigned char *color) {
    POLY_FT4 *poly;
    int w;
    int h;
    unsigned long *ot;
    int ratio = 6553;

    poly = func_80068EE8(sizeof(POLY_FT4));
    if (poly == 0) {
        return;
    }
    w = img->w;
    h = img->h;
    ((unsigned char *)poly)[3] = 9;
    poly->code = 0x2C;
    poly->clut = img->clut;
    poly->tpage = img->tpage;
    poly->r0 = color[0];
    poly->g0 = color[1];
    poly->b0 = color[2];
    if (color[3] < 255) {
        poly->code |= 2;
    }
    set_uvwh(poly, img, w, h);
    if (D_800DDC58 == 512) {
        w = round_fixed((unsigned short)w * ratio);
    }
    poly->x0 = x;
    poly->y0 = y;
    poly->x1 = x + w;
    poly->y1 = y;
    poly->x2 = x;
    poly->y2 = y + h;
    poly->x3 = x + w;
    poly->y3 = y + h;
    ot = D_800D5B8C[D_800A48B4].ot;
    ((P_TAG *)poly)->addr = ((P_TAG *)ot)->addr;
    ((P_TAG *)ot)->addr = (unsigned long)poly;
}
