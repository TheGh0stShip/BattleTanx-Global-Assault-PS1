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

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int round_fixed(int x) {
    return x >= 0 ? (x + 2048 >= 0 ? (x + 2048) >> 12 : -(-(x + 2048) >> 12))
                  : (x - 2048 >= 0 ? (x - 2048) >> 12 : -(-(x - 2048) >> 12));
}

void func_80056160(Image *img, short x, short y, int scale_x, int scale_y, unsigned char *color) {
    POLY_FT4 *poly;
    unsigned short w;
    unsigned short h;
    unsigned char t;
    unsigned char t2;
    unsigned long *ot;

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
    if (img->u + w > 255 || img->v + h > 255) {
        poly->u0 = img->u;
        poly->v0 = img->v;
        poly->u1 = img->u + (w - 1);
        poly->v1 = img->v;
        poly->u2 = img->u;
        poly->v2 = img->v + (h - 1);
        poly->u3 = img->u + (w - 1);
        poly->v3 = img->v + (h - 1);
    } else {
        poly->u0 = img->u;
        poly->v0 = img->v;
        poly->u1 = img->u + w;
        poly->v1 = img->v;
        poly->u2 = img->u;
        poly->v2 = img->v + h;
        poly->u3 = img->u + w;
        poly->v3 = img->v + h;
    }
    if (D_800DDC58 == 512) {
        w = round_fixed(fixed_mul(scale_x, fixed_mul(6553, w << 12)));
    } else {
        w = round_fixed(fixed_mul(scale_x, w << 12));
    }
    h = round_fixed(fixed_mul(scale_y, h << 12));
    if (scale_x < 0) {
        t = poly->u0;
        t2 = poly->u2;
        poly->u0 = poly->u1;
        poly->u2 = poly->u3;
        poly->u1 = t;
        poly->u3 = t2;
        w = -w;
    }
    if (scale_y < 0) {
        t = poly->v0;
        t2 = poly->v1;
        poly->v0 = poly->v2;
        poly->v1 = poly->v3;
        poly->v2 = t;
        poly->v3 = t2;
        h = -h;
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
