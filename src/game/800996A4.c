extern int func_800A2DC8(void *);
extern void func_80098D50(void *, int, int);
extern int D_800EF170[2];

typedef struct Ctx {
    char pad0[0x74];
    void *callback;
    int pad78;
    void *next_callback;
    int *out0;
    int *out1;
} Ctx;

int func_800996A4(void *c) {
    return func_800A2DC8(c);
}

void func_800996C4(Ctx *c, int a1, int a2, int a3, int arg) {
    int x = 0;
    int y = x;
    if (arg != 0) {
        x = D_800EF170[0];
        y = D_800EF170[1];
    }
    if (c->out0 != 0) {
        *c->out0 = x;
    }
    if (c->out1 != 0) {
        *c->out1 = y;
    }
    c->callback = c->next_callback;
    c->next_callback = 0;
    func_80098D50(c, 2, arg);
}
