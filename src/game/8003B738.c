typedef struct { short x; short y; short z; short pad; } SVector;
typedef struct { unsigned addr : 24; unsigned len : 8; } Tag;
typedef struct { unsigned char r; unsigned char g; unsigned char b; unsigned char h; } Cell;
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
extern unsigned char *D_800DDDF0;
extern Cell *D_800DDDF4;
extern unsigned short D_800A489C;
extern unsigned short D_800A48A0;
extern unsigned short D_800A48A4;
extern struct { int v; } D_800A48B4;
typedef struct { Tag head[2]; Tag ot[4096]; } OrderTable;
extern OrderTable D_800D5B8C[];
extern int func_8003BD84(void);
extern void func_8008BDF0(int, int, int *);
extern PolyG4 *func_80068EE8(int);

static inline void gte_ldv3c(SVector *v)
{
    __asm__ volatile("lwc2 $0, 0(%0)\n\tlwc2 $1, 4(%0)\n\tlwc2 $2, 8(%0)\n\tlwc2 $3, 12(%0)\n\tlwc2 $4, 16(%0)\n\tlwc2 $5, 20(%0)"
                     : : "r"(v));
}

static inline void gte_ldxy3c(SVector *v)
{
    __asm__ volatile("lwc2 $0, 0(%0)\n\tlwc2 $4, 0(%0)\n\tlwc2 $2, 8(%0)" : : "r"(v));
}

static inline void gte_rtpt(void)
{
    __asm__ volatile("nop\n\tnop\n\tcop2 0x0280030");
}

static inline void gte_stsxy01(int *a, int *b)
{
    __asm__ volatile("swc2 $12, 0(%0)\n\tswc2 $13, 0(%1)" : : "r"(a), "r"(b) : "memory");
}

static inline void gte_stsz12(int *z)
{
    __asm__ volatile("swc2 $17, 0(%0)\n\tswc2 $18, 4(%0)" : : "r"(z) : "memory");
}

void func_8003B738(short x, short z, short count)
{
    SVector v[2];
    int depth[2];
    int color[2];
    int pad[2];
    int shade[2];
    int far;
    Cell *cell;
    Cell *p;
    PolyG4 *poly;
    Tag *ot;
    short i;
    int k;

    far = func_8003BD84();
    D_800DDDF4 = (Cell *)(D_800DDDF0 + 4);
    v[0].x = v[1].x = (x << 2) - D_800A489C;
    v[0].y = v[1].y = -D_800A48A0;
    v[0].z = (z << 2) - D_800A48A4;
    v[1].z = v[0].z + 1024;
    cell = D_800DDDF4 + ((((z >> 7) + 64) & 0x7E) << 7) + (((x >> 7) + 64) & 0x7E);
    gte_ldv3c(v);
    gte_rtpt();
    color[0] = (cell[129].h << 16) + (cell[128].h << 8) + cell[1].h;
    color[1] = (cell[385].h << 16) + (cell[384].h << 8) + cell[257].h;
    gte_stsz12(depth);
    if (far < depth[0]) {
        func_8008BDF0(color[0], depth[0], &shade[0]);
    } else {
        shade[0] = color[0];
    }
    if (far < depth[0]) {
        func_8008BDF0(color[1], depth[1], &shade[1]);
    } else {
        shade[1] = color[1];
    }
    k = 257;
    for (i = 0; i < count;) {
        poly = func_80068EE8(sizeof(PolyG4));
        if (poly == 0) {
            return;
        }
        gte_stsxy01(&poly->xy0, &poly->xy2);
        poly->rgb0 = shade[0];
        poly->rgb2 = shade[1];
        v[0].x += 1024;
        v[1].x += 1024;
        gte_ldxy3c(v);
        gte_rtpt();
        k += 2;
        color[0] = (cell[k - 128].h << 16) + (cell[k - 129].h << 8) + cell[k - 256].h;
        color[1] = (cell[k + 128].h << 16) + (cell[k + 127].h << 8) + cell[k].h;
        gte_stsxy01(&poly->xy1, &poly->xy3);
        gte_stsz12(depth);
        if (far < depth[0]) {
            func_8008BDF0(color[0], depth[0], &shade[0]);
        } else {
            shade[0] = color[0];
        }
        if (far < depth[0]) {
            func_8008BDF0(color[1], depth[1], &shade[1]);
        } else {
            shade[1] = color[1];
        }
        i++;
        poly->rgb1 = shade[0];
        poly->rgb3 = shade[1];
        poly->tag.len = 8;
        ((unsigned char *)&poly->rgb0)[3] = 0x38;
        ot = &D_800D5B8C[D_800A48B4.v].ot[4095];
        poly->tag.addr = ot->addr;
        ot->addr = (unsigned int)poly;
    }
}
