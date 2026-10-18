extern int func_800A2CB8(void *, int);
extern void func_800A2DC8(void *);
extern int func_80090184(char *);

typedef struct Entry {
    int type;
    int a;
    int b;
    int c;
    int d;
    int e;
} Entry;

typedef struct Ctx {
    char pad0[0x74];
    void *callback;
    int pad78;
    void *next_callback;
    int *out0;
    int *out1;
} Ctx;

typedef struct StreamState {
    Ctx *current;
    Entry list[3];
    int result[2];
} StreamState;

extern StreamState D_800EF124;
extern int func_800995A8(Ctx *, Entry *, void *);
extern void func_800996C4(Ctx *, int, int, int, int);
extern int func_8009940C(Ctx *, int, int, int, void *);

int func_80099738(Ctx *c, char *name, int flag, int *out0, int *out1, void *callback) {
    int len;
    if (func_800A2CB8(c, 0) == 0) {
        func_800A2DC8(c);
    }
    D_800EF124.list[0].type = 0;
    if (flag != 0) {
        D_800EF124.list[0].a = 8;
    } else {
        D_800EF124.list[0].a = 7;
    }
    D_800EF124.list[0].b = (int)name;
    len = func_80090184(name) + 1;
    D_800EF124.list[0].c = len;
    D_800EF124.list[0].d = len;
    D_800EF124.list[1].type = 1;
    D_800EF124.list[1].a = 9;
    D_800EF124.list[1].b = (int)D_800EF124.result;
    D_800EF124.list[1].c = 8;
    D_800EF124.list[1].d = 8;
    D_800EF124.list[1].e = 1;
    D_800EF124.list[2].type = 2;
    c->next_callback = callback;
    c->out0 = out0;
    c->out1 = out1;
    return func_800995A8(c, D_800EF124.list, func_800996C4);
}
