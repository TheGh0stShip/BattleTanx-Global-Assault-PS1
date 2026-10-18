typedef struct { int x, y, z; } Vector;
typedef struct { char pad[14]; unsigned char size; } ModelInfo;
typedef struct { int pad[2]; ModelInfo *info; } Model;
typedef struct {
    unsigned char pad;
    unsigned char b1;
    unsigned char b2;
    unsigned char team;
    unsigned short u4;
    unsigned short u6;
    int i8;
    short pad2;
    unsigned char alpha;
} Emitter;
typedef struct { char pad[16]; char *base; } Header;
typedef struct { Header *header; } Ctx;
typedef struct {
    short pad;
    unsigned short body;
    unsigned short part_a;
    unsigned short part_b;
    unsigned short part_c;
    unsigned short part_d;
    int pad2;
    int emitter;
    unsigned char team;
} Def;
typedef struct {
    int pad[2];
    Vector pos;
    short id;
    unsigned char hp;
    char pad1;
    int body;
    int part_a;
    int part_b;
    Model *part_c;
    int part_d;
    int model;
    int particle;
    unsigned char b52;
    unsigned char b53;
    unsigned char size;
    unsigned char team;
    short handle;
} Turret;
typedef struct { int pad; int mode; int pad2[2]; int count; char pad3[52 - 20]; unsigned char counts[8]; } Rules;
extern Rules D_800D2FE4;
Turret *func_800237D0(int, int);
int func_80026300(Ctx *, int);
int func_8002618C(Ctx *, int, Vector *, int, int, int, int);
int func_80024D80(Ctx *, Vector *, int, int, int, Turret *);
int func_80034CD4(Vector *, int, int, int, int, int, int, int, int, int, Turret *, int);

void func_8002E754(Def *def, Ctx *ctx, Vector *pos, unsigned short id) {
    Turret *t;
    int body;
    Emitter *e;
    int team;

    t = func_800237D0(23, 60);
    if (t != 0) {
        t->body = func_80026300(ctx, def->body);
        body = t->body;
        t->part_a = func_80026300(ctx, def->part_a);
        t->part_b = func_80026300(ctx, def->part_b);
        t->part_c = (Model *)func_80026300(ctx, def->part_c);
        t->part_d = func_80026300(ctx, def->part_d);
        t->b53 = 0;
        t->b52 = 0;
        t->pos = *pos;
        t->id = id;
        t->team = def->team;
        team = t->team;
        if (team < 3) {
            if (team != 0) {
                D_800D2FE4.count++;
            }
        }
        t->hp = 15;
        t->model = func_8002618C(ctx, body, pos, id, 2, 240, 1);
        t->handle = func_80024D80(ctx, pos, id, def->body, 2, t);
        if (t->part_c != 0) {
            t->size = t->part_c->info->size;
        } else {
            t->size = 0;
        }
        t->particle = 0;
        if (def->emitter != -1) {
            e = (Emitter *)(ctx->header->base + def->emitter);
            t->particle = func_80034CD4(pos, id, D_800D2FE4.counts[e->team], e->u4, e->u6, e->i8, e->b1, e->b2, 0, 0,
                                        t, e->alpha);
        }
    }
}
