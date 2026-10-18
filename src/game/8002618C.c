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
    int pad0;
    int count;
    char pad08[8];
    Pool *pool;
} List;

extern void func_800249A0(Rect *, Rect *, unsigned short, Entry *);
extern void func_8008AA48(void *, int, int);

Entry *func_8002618C(List *list, Shape *shape, Vector *pos, unsigned short flags, int param, unsigned char kind,
                     unsigned char sub) {
    Entry *e = &list->pool->entries[list->count++];
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
