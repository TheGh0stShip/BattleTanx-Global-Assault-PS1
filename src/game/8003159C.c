typedef struct { int x, y, z; } Vector;
typedef struct { short pad[2]; short x0; unsigned short y0; short z0; short pad2; short x1; unsigned short y1; short z1; } Bounds;
typedef struct { int pad[2]; Bounds *bounds; } Model;
typedef struct {
    unsigned char pad;
    unsigned char team;
    unsigned short body;
    unsigned short part_a;
    unsigned char speed;
    unsigned char pad2;
    unsigned short part_b;
    unsigned short part_c;
    unsigned short part_d;
    unsigned short part_e;
} Def;
typedef struct {
    short pad[3];
    short handle;
    Vector pos;
    unsigned short id;
    unsigned char team;
    char pad1;
    short w0;
    short w1;
    Model *body;
    int part_a;
    int part_b;
    int part_c;
    int part_d;
    int part_e;
    int z52;
    int speed;
    int z60;
} Gate;
extern unsigned int D_800D2FE8;
extern unsigned char D_800D5A98[];
Gate *func_800237D0(int, int);
int func_80026300(void *, int);
short func_800162F0(Gate *, int, int, int, int, int, int, int, int, int, int, int);

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

static inline short quarter(int v) {
    return (to_int(v) << 14) >> 16;
}

void func_8003159C(Def *def, void *ctx, Vector *pos, unsigned short id) {
    Gate *g;
    Model *body;
    int speed;

    if (D_800D2FE8 == 4 || D_800D2FE8 == 10) {
        g = func_800237D0(30, 64);
        if (g != 0) {
            g->body = (Model *)func_80026300(ctx, def->body);
            body = g->body;
            g->part_a = func_80026300(ctx, def->part_a);
            g->part_b = func_80026300(ctx, def->part_b);
            g->part_c = func_80026300(ctx, def->part_c);
            g->part_d = func_80026300(ctx, def->part_d);
            g->part_e = func_80026300(ctx, def->part_e);
            g->pos = *pos;
            g->id = id;
            g->team = def->team;
            g->handle = func_800162F0(g, quarter(pos->x), quarter(pos->z), 0, body->bounds->x0, body->bounds->x1,
                                      body->bounds->z0, body->bounds->z1, (short)(body->bounds->y0 + quarter(pos->y)),
                                      (short)(body->bounds->y1 + quarter(pos->y)), id, 0x40000);
            g->z52 = 0;
            g->z60 = 0;
            speed = def->speed;
            g->w0 = g->w1 = 100;
            g->speed = speed << 12;
            D_800D5A98[g->team]++;
        }
    }
}
