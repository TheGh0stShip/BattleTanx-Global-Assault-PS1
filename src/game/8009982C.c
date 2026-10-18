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

extern int D_800EF170[2];
extern int func_8009940C(Ctx *, int, int, int, void *);

int func_8009982C(Ctx *c, int x, int y, void *callback) {
    if (func_800A2CB8(c, 0) == 0) {
        func_800A2DC8(c);
    }
    D_800EF170[0] = x;
    D_800EF170[1] = y;
    return func_8009940C(c, 9, (int)D_800EF170, 8, callback);
}
