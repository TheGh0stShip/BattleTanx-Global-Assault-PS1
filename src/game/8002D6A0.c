typedef struct { short pad; unsigned short body; unsigned short part_a; unsigned short part_b; } Def;
typedef struct { int pad[2]; int model; int part_a; int part_b; short handle; unsigned short id; unsigned char flag; } Inst;
Inst *func_800237D0(int, int);
int func_80026300(void *, int);
int func_8002618C(void *, int, int, int, int, int, int);
int func_80024C38(void *, int, int, int, int, Inst *);

void func_8002D6A0(Def *def, void *ctx, int pos, unsigned short id) {
    Inst *inst;
    int body;

    inst = func_800237D0(15, 28);
    if (inst != 0) {
        body = func_80026300(ctx, def->body);
        inst->model = func_8002618C(ctx, body, pos, id, 0, 240, 1);
        inst->handle = func_80024C38(ctx, pos, id, body, 1024, inst);
        inst->part_a = func_80026300(ctx, def->part_a);
        inst->part_b = func_80026300(ctx, def->part_b);
        inst->id = id;
        inst->flag = 0;
    }
}
