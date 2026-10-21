typedef struct { int x; int y; int z; } Vector;
typedef struct { short x; short y; short z; short pad; } SVector;
typedef struct { short m[3][3]; short pad; int t[3]; } Matrix;
typedef struct {
    char pad[8];
    Vector pos;
    char pad1[0x50 - 0x14];
    Matrix rot;
    char pad3[156 - 0x70];
} View;
typedef struct { unsigned char f0; unsigned char current; char pad[2]; View views[1]; } ViewSet;
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
typedef struct { short x; short y; unsigned short w; short h; char rest[0x5C - 8]; } DrawEnv;
typedef struct { DrawEnv draw[2]; char rest[0x128 - 0xB8]; } Screen;
typedef struct { char pad[13]; unsigned char r; unsigned char g; unsigned char b; } SkyColor;
typedef struct { char pad[0x1B4]; SkyColor sky; } Level;
extern ViewSet D_800D3034;
extern short D_800D5B88;
extern Level *D_800D2FE4;
extern Screen D_800DDB9C[];
extern int D_800A48AC;
extern int D_800A48B0;
extern int D_800A48B4;
typedef struct { Tag head[2]; Tag ot[4096]; } OrderTable;
extern OrderTable D_800D5B8C[];
extern void func_8008AB00(SVector *, SVector *);
extern void func_8008B844(Matrix *);
extern PolyF4 *func_80068EE8(int);

static inline void gte_ldv0(SVector *v)
{
    __asm__ volatile("lwc2 $0, 0(%0)\n\tlwc2 $1, 4(%0)" : : "r"(v));
}

static inline void gte_rtps(void)
{
    __asm__ volatile("nop\n\tnop\n\tcop2 0x0180001");
}

static inline void gte_stsxy(SVector *v)
{
    __asm__ volatile("swc2 $14, 0(%0)" : : "r"(v) : "memory");
}

static inline void set_svector(SVector *v, short x, short y, short z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

static inline void set_svector_i(SVector *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

static inline Screen *current_screen(void)
{
    return &D_800DDB9C[D_800A48B0];
}

static inline int round_int(int a, int b)
{
    int r;
    int v;

    v = a - b;
    if (v >= 0) {
        r = v + 2048;
        if (r >= 0) {
            return r >> 12;
        }
        return -(-r >> 12);
    }
    r = v - 2048;
    if (r >= 0) {
        return r >> 12;
    }
    return -((2048 - v) >> 12);
}

static inline void relative_pos(Vector *out, Vector *pos, View *ref)
{
    out->x = round_int(pos->x, ref->pos.x);
    out->y = round_int(pos->y, ref->pos.y);
    out->z = round_int(pos->z, ref->pos.z);
}

void func_8003E650(void)
{
    SVector dir;
    SVector sv;
    SVector sxy;
    Vector p;
    Vector rel;
    int y;
    SkyColor *level;
    PolyF4 *poly;
    DrawEnv *env;
    Tag *ot;

    set_svector(&dir, D_800D3034.views[D_800D3034.current].rot.m[2][0], 0, D_800D3034.views[D_800D3034.current].rot.m[2][2]);
    func_8008AB00(&dir, &dir);
    p.x = D_800D3034.views[D_800D3034.current].pos.x + dir.x * D_800D5B88;
    p.y = 0;
    p.z = D_800D3034.views[D_800D3034.current].pos.z + dir.z * D_800D5B88;
    func_8008B844(&D_800D3034.views[D_800D3034.current].rot);
    relative_pos(&rel, &p, &D_800D3034.views[D_800D3034.current]);
    set_svector_i(&sv, (short)rel.x, (short)rel.y, rel.z);
    gte_ldv0(&sv);
    gte_rtps();
    gte_stsxy(&sxy);
    y = sxy.y + 6;
    level = &D_800D2FE4->sky;
    poly = func_80068EE8(sizeof(PolyF4));
    if (poly == 0) {
        return;
    }
    poly->tag.len = 5;
    poly->code = 0x28;
    poly->r0 = level->r;
    poly->g0 = level->g;
    poly->b0 = level->b;
    env = &current_screen()->draw[D_800A48AC];
    poly->x0 = 0;
    poly->y0 = 0;
    poly->x1 = env->w;
    poly->y1 = 0;
    poly->x2 = 0;
    poly->y2 = y;
    poly->x3 = env->w;
    poly->y3 = y;
    ot = &D_800D5B8C[D_800A48B4].ot[4095];
    poly->tag.addr = ot->addr;
    ot->addr = (unsigned int)poly;
}
