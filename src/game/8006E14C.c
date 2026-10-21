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
    short id;
    short pad2;
    short type;
} Source;

typedef struct Particle {
    struct Particle *next;
    int pad4;
    int count;
} Particle;

typedef struct Effect {
    short id;
    char pad2[5];
    unsigned char kind;
    Source *src;
    Particle *particles;
    Vector pos;
    int alpha;
    int life;
    int fade;
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

typedef struct {
    int pad0;
    void (*update)(Particle *p, Vector *delta, int dt);
    int pad8;
    int fade_time;
    char pad10[36 - 16];
} EffectKind;

extern Effect *D_800EAC14;
extern Effect *D_800EAC18;
extern Particle *D_800EAC10;
extern int D_800DE30C;
extern EffectKind D_800ADF64[];
extern Handler D_800D32F4[];
extern void func_80093FF4(Matrix *m, SVector *v, Vector *out);
extern void func_8006C67C(Effect *e, Vector *pos);

void func_8006E14C(Effect *e, int *dead) {
    Vector tmp[2];
    Vector pos;
    Handler *h;
    Handler *table;
    Particle **link;
    Particle *p;
    register Particle *next asm("$17");

    if (e->src != 0 && e->src->id == e->id) {
        if (e->src->type == 4) {
            Matrix mat;
            int pad[2];
            SVector angle;

            if (D_800D32F4[e->src->type].fn != 0) {
                D_800D32F4[e->src->type].fn(e->src, e, 1, 0, &mat);
            }
            angle.x = e->angle[0];
            angle.y = e->angle[1];
            angle.z = e->angle[2];
            func_80093FF4(&mat, &angle, &pos);
            pos.x = (pos.x << 12) + mat.t[0];
            pos.y = (pos.y << 12) + mat.t[1];
            pos.z = (pos.z << 12) + mat.t[2];
        } else {
            if (D_800D32F4[e->src->type].fn != 0 && e->src->type != -1) {
                D_800D32F4[e->src->type].fn(e->src, e, 7, 0, tmp);
            }
            pos = tmp[0];
        }
    } else {
        pos = e->pos;
    }
    {
        Vector delta;

    delta.x = pos.x - e->pos.x;
    delta.y = pos.y - e->pos.y;
    delta.z = pos.z - e->pos.z;
    link = &e->particles;
    p = e->particles;
    while (p != 0) {
        next = p->next;
        if (p->count > 0) {
            D_800ADF64[e->kind].update(p, &delta, D_800DE30C);
            link = &(*link)->next;
        } else {
            *link = next;
            p->next = D_800EAC10;
            D_800EAC10 = p;
        }
        p = next;
    }
    }
    if (e->fade > 0) {
        if (e->fade < D_800ADF64[e->kind].fade_time) {
            e->alpha -= D_800DE30C * e->alpha / e->fade;
            if (e->alpha < 256) {
                e->alpha = 256;
            }
        }
        if (e->src == 0 || e->src->id == e->id) {
            func_8006C67C(e, &pos);
            e->fade -= D_800DE30C;
        } else {
            e->fade = 0;
        }
        *dead = 0;
    } else if (e->particles == 0) {
        if (e->prev == 0) {
            D_800EAC14 = e->next;
        } else {
            e->prev->next = e->next;
        }
        if (e->next == 0) {
            D_800EAC18 = e->prev;
        } else {
            e->next->prev = e->prev;
        }
        *dead = 1;
    }
    e->pos = pos;
}
