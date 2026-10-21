typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    short x;
    short y;
    short z;
    unsigned short angle;
    int offset;
} Placement;

typedef struct {
    unsigned short count;
    unsigned short start;
    char pad4[0x10];
    short x0;
    char pad16[2];
    short z0;
    short x1;
    char pad1C[2];
    short z1;
} Bounds;

typedef struct {
    char *base;
    Bounds *bounds;
    Placement *placements;
    int count;
    char *objects;
    char *extra;
    int count2;
    int first;
} Header;

typedef struct {
    Header *header;
    int pad4;
    int items;
    int count2;
    void *level;
    void *extra;
    Header data;
} Context;

typedef struct {
    int *data;
} File;

typedef struct {
    int pad0;
    char pad4[8];
    short x0;
    short z0;
    short x1;
    short z1;
    char pad14[8];
    int items;
    char *item_base;
    char pad24[0x1B4 - 0x24];
    unsigned char flag;
} Level;

extern int D_800A4B10;
extern int D_800A48DC;
extern Level *D_800D2FE4;
extern void func_8008AC90(void *, int);
extern Level *func_80068DA4(int);
extern void func_8002493C(void);
extern void func_8003DC44(int, char *);
extern void func_800159B0(void);
extern void func_80025094(char *, Context *, Vector *, int);

int func_8002429C(File *file, Context *ctx) {
    int *raw;
    Header *h;
    int size;
    register Level *level asm("$17");
    char *items;
    char *extra;
    int i;
    int n;
    register Header *h2 asm("$21");
    register Bounds *b asm("$20");
    register Header *hdr asm("$18");
    Vector v;
    Vector *pv;

    func_8008AC90(ctx, 24);
    ctx->header = &ctx->data;
    func_8008AC90(ctx->header, 32);
    raw = file->data;
    h = ctx->header;
    h->base = (char *)raw + raw[0];
    h->bounds = (Bounds *)((char *)raw + raw[1]);
    h->placements = (Placement *)((char *)raw + raw[2]);
    h->objects = (char *)raw + raw[3];
    h->extra = (char *)raw + raw[4];
    h->count = (unsigned int)(raw[3] - raw[2]) / 12;
    h->first = 0;
    h->count2 = D_800A4B10;
    {
        Header *hh = ctx->header;
        int a;
        int c;
        int t;

        ctx->items = a = hh->bounds->count;
        ctx->count2 = c = hh->count2;
        t = a * 72;
        size = c * 12 + t + 584;
    }
    if (D_800A48DC == 0) {
        D_800D2FE4 = func_80068DA4(size);
    }
    level = D_800D2FE4;
    func_8008AC90(level, size);
    level->flag = 0;
    func_8002493C();
    n = ctx->items;
    level->pad0 = 0;
    level->items = 0;
    level->x0 = (ctx->header->bounds->x0 << 6) / 72;
    level->x1 = (ctx->header->bounds->x1 << 6) / 72;
    level->z0 = (ctx->header->bounds->z0 << 6) / 72;
    level->z1 = (ctx->header->bounds->z1 << 6) / 72;
    items = (char *)(((int)level + 463) & ~7);
    extra = (char *)(((int)items + n * 72 + 7) & ~7);
    if (level->x1 == level->x0) {
        level->x0 = -12000;
        level->z0 = -12000;
        level->x1 = 12000;
        level->z1 = 12000;
    }
    level->items = ctx->items;
    level->item_base = items;
    hdr = ctx->header;
    for (i = 0; i < hdr->count2; i++) {
        func_8003DC44(i, extra + (i + hdr->first) * 12);
    }
    ctx->level = level;
    ctx->extra = extra;
    func_800159B0();
    pv = &v;
    h2 = ctx->header;
    b = h2->bounds;
    for (i = b->start; i < b->start + b->count; i++) {
        Placement *p = &h2->placements[i];
        int x = p->x << 14;
        int y = p->y << 14;
        int z = p->z << 14;

        v.x = x;
        pv->y = y;
        pv->z = z;
        func_80025094(h2->objects + p->offset, ctx, pv, p->angle);
    }
    return size;
}
