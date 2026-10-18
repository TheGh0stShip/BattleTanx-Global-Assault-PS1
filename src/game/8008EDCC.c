extern void func_8008EC40(void);
extern void func_800999E8(void *, int, int, int, int, void *);
extern void func_8008E860(void);

typedef struct {
    char pad[44];
    int base;
} Body8008EDCC;

typedef struct {
    int flags;
    int arg;
    char pad8[8];
    Body8008EDCC body;
    char pad64[360];
    int cursor;
    int start;
} S8008EDCC;
extern S8008EDCC D_800EEC34;

void func_8008EDCC(int a0, int a1, int a2, int a3, int a4) {
    S8008EDCC *s;
    Body8008EDCC *body;

    func_8008EC40();
    body = &D_800EEC34.body;
    s = &D_800EEC34;
    s->start = a0;
    s->cursor = body->base + 8;
    s->arg = a4;
    func_800999E8(body, a0, a1, a2, a3, func_8008E860);
}
