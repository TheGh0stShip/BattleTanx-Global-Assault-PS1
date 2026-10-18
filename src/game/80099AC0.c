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
extern void func_800999A4(Ctx *, int, int, int, int);
extern int func_8009940C(Ctx *, int, int, int, void *);

int func_80099AC0(Ctx *c, int key, int src, int size, int *out, void *callback) {
    int *r;

    if (func_800A2CB8(c, 0) == 0) {
        func_800A2DC8(c);
    }
    r = D_800EF124.result;
    r[0] = key;
    r[1] = size;
    D_800EF124.list[0].type = 0;
    D_800EF124.list[0].a = 13;
    D_800EF124.list[0].b = (int)r;
    D_800EF124.list[0].c = 8;
    D_800EF124.list[0].d = 8;
    D_800EF124.list[1].type = 0;
    D_800EF124.list[1].a = 14;
    D_800EF124.list[1].b = src;
    D_800EF124.list[1].c = size;
    D_800EF124.list[1].d = size;
    D_800EF124.list[2].type = 2;
    c->next_callback = callback;
    c->out0 = out;
    return func_800995A8(c, D_800EF124.list, func_800999A4);
}
