typedef struct List {
    int kind;
    int count;
    int items[1];
} List;

typedef struct Def {
    int type;
    List *list;
    int extra;
} Def;

typedef struct Inst {
    int type;
    List *list;
    int extra;
    List own;
} Inst;

extern Def *D_800D2E14[];

void func_8007A344(Inst *inst, int id) {
    Def *def = D_800D2E14[id];
    List *src;
    List *dst;
    int count;
    int i;

    i = 0;
    if (id == 107) {
        inst->type = 0;
        return;
    }
    src = def->list;
    count = src->count;
    dst = &inst->own;
    for (; i < count; i++) {
        dst->items[i] = src->items[i];
    }
    dst->count = count;
    dst->kind = 0;
    inst->type = def->type;
    inst->list = dst;
    inst->extra = def->extra;
}
