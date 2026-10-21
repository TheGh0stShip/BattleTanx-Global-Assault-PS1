typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    short x;
    short y;
    short z;
    short pad;
} SVector;

typedef struct {
    short m[3][3];
    short pad;
    int t[3];
} Matrix;

typedef struct {
    unsigned short id;
    short pad2;
    short type;
} Source;

typedef struct Effect {
    unsigned short id;
    char pad2[5];
    unsigned char kind;
    Source *src;
    int state;
    Vector pos;
    int param;
    int life;
    int extra;
    int scale;
    short dir[3];
    short angle[3];
    struct Effect *prev;
    struct Effect *next;
} Effect;

typedef struct {
    int pad;
    void (*fn)(Source *src, Effect *e, int what, int arg, void *out);
    int pad2;
} Handler;

extern Effect *D_800EAC14;
extern Effect *D_800EAC18;
extern int D_800EAC1C;
extern signed char D_800A606C;
extern Handler D_800D32F4[];
extern Effect *func_800237D0(int tag, int size);
extern void func_80093FF4(Matrix *m, SVector *v, Vector *out);

Effect *func_8006C334(Source *src, int kind, Vector *a, Vector *b, int unused, int param, int life,
                      int extra) {
    Effect *e;
    Vector pos[2];
    Matrix mat[1];
    int pad[2];
    SVector angle;

    e = func_800237D0(73, 64);
    if (e != 0) {
        e->next = 0;
        e->prev = D_800EAC18;
        if (D_800EAC18 != 0) {
            D_800EAC18->next = e;
            D_800EAC18 = e;
        } else {
            D_800EAC14 = e;
            D_800EAC18 = e;
        }
        e->src = src;
        if (src != 0) {
            e->id = src->id;
        }
        if (a != 0 && b != 0) {
            e->pos.x = (a->x + b->x) / 2;
            e->pos.y = (a->y + b->y) / 2;
            e->pos.z = (a->z + b->z) / 2;
            e->dir[0] = ((b->x - a->x) / 2) >> 12;
            e->dir[1] = ((b->y - a->y) / 2) >> 12;
            e->dir[2] = ((b->z - a->z) / 2) >> 12;
            e->angle[0] = e->pos.x >> 12;
            e->angle[1] = e->pos.y >> 12;
            e->angle[2] = e->pos.z >> 12;
        } else {
            e->pos.x = 0;
            e->angle[0] = 0;
            e->pos.y = 0;
            e->angle[1] = 0;
            e->pos.z = 0;
            e->angle[2] = 0;
            e->dir[0] = 0;
            e->dir[1] = 0;
            e->dir[2] = 0;
        }
        if (e->src != 0) {
            if (e->src->type == 4) {
                if (D_800D32F4[e->src->type].fn != 0) {
                    D_800D32F4[e->src->type].fn(e->src, e, 1, 0, mat);
                }
                angle.x = e->angle[0];
                angle.y = e->angle[1];
                angle.z = e->angle[2];
                func_80093FF4(mat, &angle, &e->pos);
                e->pos.x = (e->pos.x << 12) + mat->t[0];
                e->pos.y = (e->pos.y << 12) + mat->t[1];
                e->pos.z = (e->pos.z << 12) + mat->t[2];
            } else {
                if (D_800D32F4[e->src->type].fn != 0 && e->src->type != -1) {
                    D_800D32F4[e->src->type].fn(e->src, e, 7, 0, pos);
                }
                e->pos = pos[0];
            }
        }
        e->kind = kind;
        e->param = param;
        if (D_800A606C == 1 && D_800EAC1C == 0) {
            e->life = life;
        } else {
            e->life = life / 2;
        }
        e->extra = extra;
        e->state = 0;
        e->scale = 4095;
    }
    return e;
}
