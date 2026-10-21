typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    char pad0[4];
    short x0;
    short y0;
    short z0;
    short pad0A;
    short x1;
    short y1;
    short z1;
} Box;

typedef struct {
    char pad0[8];
    Box *box;
    char padC[0xC - 0xC];
} Shape;

typedef struct {
    short x0;
    short z0;
    short x1;
    short z1;
} Rect;

typedef struct {
    char pad0[0x20];
    Vector pos;
    int x0;
    int z0;
    int x1;
    int z1;
    Shape *shape;
    int param;
    unsigned char kind;
    unsigned char sub;
    char pad46[2];
} Entry;

typedef struct {
    char pad0[0x20];
    Entry *entries;
} Pool;

typedef struct {
    char pad0[0x1C];
    int base;
} Header;

typedef struct {
    Header *header;
    int count;
    char pad08[8];
    Pool *pool;
    Shape *shapes;
} Context;

typedef struct {
    unsigned char type;
    unsigned char b1;
    unsigned short ref;
    unsigned short ref2;
    unsigned short h6;
    int i8;
    char pad0C[2];
    unsigned char b14;
} Placement;

typedef struct {
    unsigned char type;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    unsigned char b4;
} PlacementB;

typedef struct {
    unsigned char type;
    unsigned char b1;
    short x0;
    short h4;
    short z0;
    short x1;
    short h10;
    short z1;
} Area;

typedef struct {
    int x;
    int z;
} Point;

typedef struct {
    Point pos;
    Point dir;
    int range;
} Spawn;

typedef struct {
    char pad0[0x14];
    short x0;
    short z0;
    short x1;
    short z1;
    char pad1C[0x150 - 0x1C];
    Spawn spawns[1];
} Screen;

typedef struct {
    Screen *screen;
    char pad4[0x34 - 4];
    unsigned char teams[5];
} Globals;

extern Globals D_800D2FE4;
extern void func_800249A0(Rect *, Rect *, unsigned short, Entry *);
extern void func_8008AA48(void *, int, int);
extern int func_8008AD60(int);
extern int func_8008ACC0(int);
extern void func_80024D80(Context *, Vector *, unsigned short, unsigned short, int, int);
extern void func_80024F08(Context *, Vector *, unsigned short, unsigned short, int, int);
extern void func_80024C38(Context *, Vector *, unsigned short, Shape *, int, int);
extern void func_80024720(Placement *, Vector *, unsigned short);
extern void func_8002D6A0(Placement *, Context *, Vector *, unsigned short);
extern void func_8002A914(Placement *, Context *, Vector *, unsigned short);
extern void func_80029BF0(Vector *, int, int, int, int);
extern void func_80028720(int, Vector *, unsigned short, int, int);
extern void func_800263F0(Placement *, Context *, Vector *, unsigned short);
extern void func_80037380(Placement *, Context *, Vector *, unsigned short);
extern void func_80034CD4(Vector *, unsigned short, int, int, int, int, int, int, int, int, int, int);
extern void func_80033DFC(Placement *, Context *, Vector *, unsigned short);
extern void func_80033B28(Placement *, Context *, Vector *, unsigned short);
extern void func_8002E568(Placement *, Context *, Vector *, unsigned short);
extern void func_8002CF3C(Placement *, Context *, Vector *, unsigned short);
extern void func_80032A68(Placement *, Context *, Vector *, unsigned short);
extern void func_80034E60(Placement *, Context *, Vector *, unsigned short);
extern void func_80030DA4(Placement *, Context *, Vector *, unsigned short);
extern void func_80035DB8(Placement *, Context *, Vector *, unsigned short);
extern void func_800371FC(Placement *, Context *, Vector *, unsigned short);
extern void func_8002E754(Placement *, Context *, Vector *, unsigned short);
extern void func_8003159C(Placement *, Context *, Vector *, unsigned short);
extern void func_80034250(Placement *, Context *, Vector *, unsigned short);
extern void func_80027F38(Vector *, int, int);
extern void func_800162F0(int, int, int, int, int, int, int, int, int, int, int, int);
extern void func_80034258(int, int, int, int, int, int, int, int, int, int, int);
extern void func_800247DC(Placement *);
extern void func_800248A0(Placement *);

static inline Entry *make_entry(Context *ctx, Shape *shape, Vector *pos, int flags, int param,
                                unsigned char kind, unsigned char sub) {
    Entry *e = &ctx->pool->entries[ctx->count++];
    Rect in;
    Rect out;

    e->pos.x = pos->x;
    e->pos.y = pos->y;
    e->pos.z = pos->z;
    e->shape = shape;
    if (shape != 0) {
        in.x1 = e->shape->box->x1;
        in.x0 = e->shape->box->x0;
        in.z1 = e->shape->box->z1;
        in.z0 = e->shape->box->z0;
        func_800249A0(&in, &out, flags, e);
        e->x1 = (out.x1 << 14) + pos->x;
        e->x0 = (out.x0 << 14) + pos->x;
        e->z1 = (out.z1 << 14) + pos->z;
        e->z0 = (out.z0 << 14) + pos->z;
        e->sub = sub;
        e->param = param;
        e->kind = kind;
    } else {
        func_8008AA48(e, 0, sizeof(Entry));
    }
    return e;
}

static inline Shape *shape_get(Context *ctx, unsigned short ref) {
    Header *h = ctx->header;

    if (ref == 0xFFFF) {
        return 0;
    }
    return &ctx->shapes[h->base + ref];
}

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

static inline short to_map(int value) {
    return fixed_to_int(value) << 14 >> 16;
}

void func_80025094(Placement *p_, Context *ctx, Vector *pos, int angle_) {
    Placement *p = p_;
    int angle = angle_;
    Shape *shape;

    switch (p->type) {
    case 0:
        make_entry(ctx, shape_get(ctx, p->ref), pos, angle, 0, 240, 1);
        break;
    case 22: {
        Placement *q = p;

        make_entry(ctx, shape_get(ctx, q->ref), pos, angle, 1, 240, 1);
        func_80024D80(ctx, pos, angle, q->ref, 128, 0);
        break;
    }
    case 11: {
        Placement *q = p;

        make_entry(ctx, shape_get(ctx, q->ref), pos, angle, 1, 240, 1);
        func_80024D80(ctx, pos, angle, q->ref, 64, 0);
        break;
    }
    case 1:
    case 14:
        shape = shape_get(ctx, p->ref);
        make_entry(ctx, shape, pos, angle, 2, 240, 1);
        func_80024C38(ctx, pos, angle, shape, p->type == 14 ? 16384 : 1, 0);
        break;
    case 6:
        func_80024720(p, pos, angle);
        break;
    case 5:
        func_8002D6A0(p, ctx, pos, angle);
        break;
    case 4:
        func_8002A914(p, ctx, pos, angle);
        break;
    case 7:
        func_80029BF0(pos, p->b1, 0, 0, ((PlacementB *)p)->b2);
        break;
    case 12:
        if (p->ref2 != 0xFFFF) {
            make_entry(ctx, shape_get(ctx, p->ref2), pos, angle, 0, 240, 1);
        }
        func_80028720(p->b1, pos, angle, D_800D2FE4.teams[((PlacementB *)p)->b2], 0);
        break;
    case 3:
        func_800263F0(p, ctx, pos, angle);
        break;
    case 8:
        func_80037380(p, ctx, pos, angle);
        break;
    case 13:
        func_80034CD4(pos, angle, D_800D2FE4.teams[((PlacementB *)p)->b3], p->ref2, p->h6, p->i8, p->b1,
                      ((PlacementB *)p)->b2, 0, 0, 0, p->b14);
        break;
    case 17: {
        Point at;
        Point dir;
        int range;
        int a = (unsigned)(angle & 0xFFFF) >> 4;

        at.x = pos->x;
        at.z = pos->z;
        dir.x = func_8008AD60(a);
        dir.z = func_8008ACC0(a);
        D_800D2FE4.screen->spawns[p->b1].pos = at;
        D_800D2FE4.screen->spawns[p->b1].dir = dir;
        range = (p->ref * 640 / 720) << 14;
        D_800D2FE4.screen->spawns[p->b1].range = range;
        break;
    }
    case 31:
        func_80033DFC(p, ctx, pos, angle);
        break;
    case 35:
        func_80033B28(p, ctx, pos, angle);
        break;
    case 10:
        func_8002E568(p, ctx, pos, angle);
        break;
    case 24:
        func_8002CF3C(p, ctx, pos, angle);
        break;
    case 20:
        func_80032A68(p, ctx, pos, angle);
        break;
    case 15:
        func_80034E60(p, ctx, pos, angle);
        break;
    case 26:
        func_80030DA4(p, ctx, pos, angle);
        break;
    case 28:
        func_80035DB8(p, ctx, pos, angle);
        break;
    case 29:
        func_800371FC(p, ctx, pos, angle);
        break;
    case 21:
        func_8002E754(p, ctx, pos, angle);
        break;
    case 32:
        func_8003159C(p, ctx, pos, angle);
        break;
    case 27:
        func_80027F38(pos, 0, 127);
        break;
    case 16:
        func_80034250(p, ctx, pos, angle);
        break;
    case 30: {
        Area *r = (Area *)p;
        int x0 = (r->x0 << 6) / 72;
        int z0 = (r->z0 << 6) / 72;
        int x1 = (r->x1 << 6) / 72;
        int z1 = (r->z1 << 6) / 72;

        switch (r->b1) {
        case 0:
            D_800D2FE4.screen->x0 = to_map(pos->x) + x0;
            D_800D2FE4.screen->x1 = to_map(pos->x) + x1;
            D_800D2FE4.screen->z0 = to_map(pos->z) + z0;
            D_800D2FE4.screen->z1 = to_map(pos->z) + z1;
            break;
        case 1:
            func_800162F0(0, to_map(pos->x), to_map(pos->z), to_map(pos->y), (short)x0, (short)x1, (short)z0,
                          (short)z1, r->h4, r->h10, angle & 0xFFFF, 0x01000000);
            break;
        case 2:
            func_800162F0(0, to_map(pos->x), to_map(pos->z), to_map(pos->y), (short)x0, (short)x1, (short)z0,
                          (short)z1, r->h4, r->h10, angle & 0xFFFF, 0x80000);
            break;
        case 3:
        case 4:
            func_80034258(pos->x, pos->y, pos->z, (short)x0, (short)x1, r->h4, r->h10, (short)z0, (short)z1,
                          angle & 0xFFFF, r->b1 == 4);
            break;
        }
        break;
    }
    case 37:
        func_800247DC(p);
    case 38:
        func_800248A0(p);
        break;
    case 43:
        make_entry(ctx, shape_get(ctx, p->ref), pos, angle, 0, 240, 0);
        if (((PlacementB *)p)->b4 == 0) {
            func_80024F08(ctx, pos, angle, p->ref, 16384, 0);
        } else {
            func_80024F08(ctx, pos, angle, p->ref, 1, 0);
        }
        break;
    case 42:
        func_80024D80(ctx, pos, angle, p->ref, 1, 0);
        break;
    }
}
