typedef struct { int x, y, z; } Vector;
typedef struct { short pad[3]; unsigned short min; short pad2[3]; unsigned short max; } Bounds;
typedef struct { int pad[2]; Bounds *bounds; } Model;
typedef struct { short pad; unsigned short body; unsigned short part_a; unsigned short part_b; unsigned short part_c; unsigned short part_d; } Def;
typedef struct {
    short pad;
    short pad1;
    short pad2;
    short handle;
    int model;
    Model *body;
    int part_a;
    int part_b;
    int part_c;
    int part_d;
    int height;
    Vector pos;
    short timer;
    short pad3;
    short active;
    unsigned char flag;
    unsigned char state;
} Barrel;
Barrel *func_800237D0(int, int);
int func_80026300(void *, int);
int func_8002618C(void *, Model *, Vector *, int, int, int, int);
int func_800162F0(Barrel *, int, int, int, int, int, int, int, int, int, int, int);

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

void func_8002A914(Def *def, void *ctx, Vector *pos, unsigned short id) {
    Barrel *b;
    Bounds *bounds;

    b = func_800237D0(16, 56);
    if (b != 0) {
        b->body = (Model *)func_80026300(ctx, def->body);
        b->part_b = func_80026300(ctx, def->part_b);
        b->part_a = func_80026300(ctx, def->part_a);
        b->part_c = func_80026300(ctx, def->part_c);
        b->part_d = func_80026300(ctx, def->part_d);
        b->model = func_8002618C(ctx, b->body, pos, id, 0, 240, 2);
        b->handle = func_800162F0(b, (to_int(pos->x) << 14) >> 16, (to_int(pos->z) << 14) >> 16, 0, -10, 10, -10, 10, 0,
                                  128, 0, 2048);
        b->timer = 0;
        b->state = 0;
        bounds = b->body->bounds;
        b->height = (short)(bounds->max - bounds->min) << 14;
        b->active = 0;
        b->pos = *pos;
        b->flag = 0;
    }
}
