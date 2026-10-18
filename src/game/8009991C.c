extern int func_800A2CB8(void *, int);
extern void func_800A2DC8(void *);
extern void func_80098D50(void *, int, int);
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

extern int D_800EF170[2];
extern int func_8009940C(Ctx *, int, int, int, void *);

int func_8009991C(Ctx *c, int x, int y, int z, void *callback) {
    if (func_800A2CB8(c, 0) == 0) {
        func_800A2DC8(c);
    }
    D_800EF170[0] = x;
    D_800EF170[1] = y;
    D_800EF170[2] = z;
    return func_8009940C(c, 11, (int)D_800EF170, 12, callback);
}

void func_800999A4(Ctx *c, int a1, int a2, int value, int arg) {
    if (c->out0 != 0) {
        *c->out0 = value;
    }
    c->callback = c->next_callback;
    c->next_callback = 0;
    func_80098D50(c, 2, arg);
}
