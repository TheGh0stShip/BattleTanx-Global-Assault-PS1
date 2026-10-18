typedef struct { int x, y, z; } Vector;
typedef struct { short pad; unsigned short body; unsigned short part_a; unsigned short part_b; unsigned char solid; } Def;
typedef struct {
    int pad[2];
    int model;
    int part_a;
    int part_b;
    Vector pos;
    int timer;
    short handle;
    unsigned short id;
    unsigned char flag;
    unsigned char solid;
} Inst;
Inst *func_800237D0(int, int);
int func_80026300(void *, int);
int func_8002618C(void *, int, Vector *, int, int, int, int);
int func_80024D80(void *, Vector *, int, int, int, Inst *);

void func_8002E568(Def *def, void *ctx, Vector *pos, unsigned short id) {
    Inst *inst;
    int body;

    inst = func_800237D0(26, 44);
    if (inst != 0) {
        body = func_80026300(ctx, def->body);
        inst->part_a = func_80026300(ctx, def->part_a);
        inst->part_b = func_80026300(ctx, def->part_b);
        inst->solid = def->solid;
        inst->model = func_8002618C(ctx, body, pos, id, 0, 240, 1);
        inst->handle = func_80024D80(ctx, pos, id, def->body, inst->solid ? 0x100002 : 0x100000, inst);
        inst->timer = 50;
        inst->id = id;
        inst->flag = 0;
        inst->pos = *pos;
    }
}
