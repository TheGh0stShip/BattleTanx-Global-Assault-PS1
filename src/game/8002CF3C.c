typedef struct { int x, y, z; } Vector;
typedef struct { unsigned int flags; int link; int pad[3]; short bonus; short pad1; int pad2[2]; short owner; short pad3[3]; } Cell;
typedef struct { short pad; unsigned short body; unsigned short part_a; unsigned short part_b; } Def;
typedef struct {
    int pad[2];
    int model;
    int body;
    int part_b;
    int part_a;
    int zero;
    Vector pos;
    unsigned short handle;
    unsigned short id;
    short pad2;
    unsigned char active;
} Inst;
extern Cell D_800C62B0[];
Inst *func_800237D0(int, int);
int func_80026300(void *, int);
int func_8002618C(void *, int, Vector *, int, int, int, int);
int func_80024D80(void *, Vector *, int, int, int, Inst *);

static inline short cell_total(Cell *cell) {
    return cell->owner + cell->bonus;
}

void func_8002CF3C(Def *def, void *ctx, Vector *pos, unsigned short id) {
    Inst *inst;
    Cell *cell;

    inst = func_800237D0(28, 48);
    if (inst != 0) {
        inst->body = func_80026300(ctx, def->body);
        inst->part_a = func_80026300(ctx, def->part_a);
        inst->part_b = func_80026300(ctx, def->part_b);
        inst->model = func_8002618C(ctx, inst->body, pos, id, 2, 240, 1);
        inst->handle = func_80024D80(ctx, pos, id, def->body, 0x8000, inst);
        cell = &D_800C62B0[inst->handle];
        cell->owner = cell_total(cell) + 20;
        inst->id = id;
        inst->pos = *pos;
        inst->zero = 0;
        inst->active = 1;
    }
}
