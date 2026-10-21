typedef struct { short x; short y; short z; short pad; } SVector;
typedef struct { unsigned addr : 24; unsigned len : 8; } Tag;
typedef struct {
    Tag tag;
    int rgb0;
    int xy0;
    unsigned short uv0, clut;
    int rgb1;
    int xy1;
    unsigned short uv1, tpage;
    int rgb2;
    int xy2;
    unsigned short uv2, pad2;
    int rgb3;
    int xy3;
    unsigned short uv3, pad3;
} PolyGT4;
typedef struct {
    Tag tag;
    int rgb0;
    int xy0;
    int rgb1;
    int xy1;
    int rgb2;
    int xy2;
    int rgb3;
    int xy3;
} PolyG4;
typedef struct { unsigned short tpage; unsigned short clut; unsigned short uv; unsigned short pad; } Tile;
typedef struct { Tag head[2]; Tag ot[4096]; } OrderTable;

typedef struct { unsigned short width; unsigned short pad; unsigned int cells[1]; } Flb;
extern Flb *D_800DDDF0;
extern unsigned int *D_800DDDF4;
extern Tile D_800DDDF8[];
extern unsigned short D_800A489C;
extern unsigned short D_800A48A0;
extern unsigned short D_800A48A4;
extern struct { int v; } D_800A48B4;
extern OrderTable D_800D5B8C[];
extern unsigned int func_8003BD84(void);
extern void *func_80068EE8(int);
extern void func_8008BCD4(int, int, int *, int *);
extern void func_8003AA1C(PolyGT4 *);

static inline int conv_a(unsigned int c)
{
    return ((c & 0x7C) << 19) | ((c & 0x3E) << 11) | ((c & 0x1F) << 3);
}

static inline int conv_b(unsigned int c)
{
    return ((c & 0x7C00) >> 7) | ((c & 0x3E0) << 6) | ((c & 0x1F) << 19);
}

void func_8003AF64(short x, short z, int unused, short count)
{
    SVector v[2];
    unsigned int sz[2][2];
    unsigned short uv[8];
    int col[2][2];
    int out[4];
    short done[2];
    short clip[2];
    int flag[2];
    unsigned int *cell;
    unsigned short width;
    unsigned int far;
    unsigned short rot;
    unsigned short base;
    unsigned int c;
    Tile *tile;
    PolyGT4 *poly;
    PolyG4 *poly2;
    Tag *ot;
    short i;
    int j;

    cell = 0;
    D_800DDDF4 = D_800DDDF0->cells;
    width = D_800DDDF0->width;
    switch (width) {
    case 64:
        cell = D_800DDDF4 + ((((z >> 7) + 128) & 0xFF) << 6) + (((x >> 7) + 32) & 0x3F);
        break;
    case 128:
        cell = D_800DDDF4 + ((((z >> 7) + 64) & 0x7F) << 7) + (((x >> 7) + 64) & 0x7F);
        break;
    case 256:
        cell = D_800DDDF4 + ((((z >> 7) + 32) & 0x3F) << 7) + (((x >> 7) + 128) & 0xFF);
        break;
    }
    far = func_8003BD84();
    ((SVector *)sz)->x = v[0].x = v[1].x = (x << 2) - D_800A489C;
    ((SVector *)sz)->y = v[0].y = v[1].y = -D_800A48A0;
    ((SVector *)sz)->z = v[0].z = (z << 2) - D_800A48A4;
    v[1].z = v[0].z + 512;
    __asm__ volatile("lwc2 $0, 0(%0)\n\tlwc2 $1, 4(%0)\n\tlwc2 $2, 8(%0)\n\tlwc2 $3, 12(%0)\n\tlwc2 $4, 16(%0)\n\tlwc2 $5, 20(%0)" : : "r"(v));
    __asm__ volatile("nop\n\tnop\n\tcop2 0x0280030");
    col[1][0] = conv_a(cell[0]);
    col[1][1] = conv_a(cell[width]);
    __asm__ volatile("swc2 $17, 0(%0)\n\tswc2 $18, 4(%0)" : : "r"(sz[1]) : "memory");
    done[1] = 0;
    __asm__ volatile("cfc2 $12, $31\n\tnop\n\tsw $12, 0(%0)" : : "r"(&flag[1]) : "$12", "memory");
    if (sz[1][0] >= far || sz[1][1] >= far) {
        clip[1] = 1;
    } else {
        clip[1] = 0;
    }
    for (i = 0; i <= count; i++) {
        poly = func_80068EE8(sizeof(PolyGT4));
        if (poly == 0) {
            return;
        }
        done[i & 1] = 0;
        clip[i & 1] = 0;
        __asm__ volatile("swc2 $12, 0(%0)\n\tswc2 $13, 0(%1)" : : "r"(&poly->xy0), "r"(&poly->xy2) : "memory");
        c = *cell;
        tile = &D_800DDDF8[(c >> 18) & 0x3F];
        poly->tpage = tile->tpage | 0x20;
        rot = (c >> 16) & 3;
        poly->clut = tile->clut;
        base = tile->uv;
        if (!((c >> 15) & 1)) {
            uv[0] = base + 63;
            uv[3] = base + 16191;
            uv[1] = base;
            uv[2] = base + 16128;
        } else {
            uv[1] = base + 63;
            uv[2] = base + 16191;
            uv[0] = base;
            uv[3] = base + 16128;
        }
        uv[4] = uv[0];
        uv[5] = uv[1];
        uv[6] = uv[2];
        uv[7] = uv[3];
        poly->uv0 = uv[rot];
        poly->uv1 = uv[rot + 1];
        poly->uv3 = uv[rot + 2];
        poly->uv2 = uv[rot + 3];
        cell++;
        v[0].x += 512;
        v[1].x += 512;
        __asm__ volatile("lwc2 $0, 0(%0)\n\tlwc2 $4, 0(%0)\n\tlwc2 $2, 8(%0)" : : "r"(v));
        __asm__ volatile("nop\n\tnop\n\tcop2 0x0280030");
        {
            int *cp = col[i & 1];
            cp[0] = conv_b(cell[0]);
            cp[1] = conv_b(cell[width]);
        }
        __asm__ volatile("swc2 $17, 0(%0)\n\tswc2 $18, 4(%0)" : : "r"(sz[i & 1]) : "memory");
        __asm__ volatile("swc2 $12, 0(%0)\n\tswc2 $13, 0(%1)" : : "r"(&poly->xy1), "r"(&poly->xy3) : "memory");
        __asm__ volatile("cfc2 $12, $31\n\tnop\n\tsw $12, 0(%0)" : : "r"(&flag[i & 1]) : "$12", "memory");
        if (!(sz[i & 1][0] < far && sz[i & 1][1] < far)) {
            clip[i & 1] = 1;
        }
        ot = &D_800D5B8C[D_800A48B4.v].ot[4094];
        poly->tag.addr = ot->addr;
        ot->addr = (unsigned int)poly;
        if (clip[0] || clip[1]) {
            poly2 = func_80068EE8(sizeof(PolyG4));
            if (poly2 == 0) {
                return;
            }
            j = (i ^ 1) & 1;
            if (!done[j]) {
                func_8008BCD4((*(col + j))[0], sz[j][0], &out[0], &out[2]);
                func_8008BCD4((*(col + j))[1], sz[j][1], &out[1], &out[3]);
                done[j] = 1;
            }
            poly->rgb0 = out[0];
            poly->rgb2 = out[1];
            poly2->rgb0 = out[2];
            poly2->rgb2 = out[3];
            func_8008BCD4((*(col + (i & 1)))[0], sz[i & 1][0], &out[0], &out[2]);
            func_8008BCD4((*(col + (i & 1)))[1], sz[i & 1][1], &out[1], &out[3]);
            done[i & 1] = 1;
            poly->rgb1 = out[0];
            poly->rgb3 = out[1];
            poly2->rgb1 = out[2];
            poly2->rgb3 = out[3];
            poly2->xy0 = poly->xy0;
            poly2->xy1 = poly->xy1;
            poly2->xy2 = poly->xy2;
            poly2->xy3 = poly->xy3;
            poly2->tag.len = 8;
            ((unsigned char *)&poly2->rgb0)[3] = 0x38;
            ot = &D_800D5B8C[D_800A48B4.v].ot[4094];
            poly2->tag.addr = ot->addr;
            ot->addr = (unsigned int)poly2;
            poly->tag.len = 12;
            ((unsigned char *)&poly->rgb0)[3] = 0x3E;
        } else {
            poly->rgb0 = col[(i ^ 1) & 1][0];
            poly->rgb2 = col[(i ^ 1) & 1][1];
            poly->rgb1 = col[i & 1][0];
            poly->rgb3 = col[i & 1][1];
            poly->tag.len = 12;
            ((unsigned char *)&poly->rgb0)[3] = 0x3C;
        }
        if ((flag[0] | flag[1]) < 0) {
            func_8003AA1C(poly);
        }
    }
}
