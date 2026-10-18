extern void func_8008EC40(void);
extern void func_80099AC0(void *, int, int, int, int, void *);
extern void func_8008E860(void);

typedef struct {
    char pad[44];
    int base;
} Body8008EE60;

typedef struct {
    int flags;
    int arg;
    char pad8[8];
    Body8008EE60 body;
    char pad64[360];
    int cursor;
    int start;
} S8008EE60;
extern S8008EE60 D_800EEC34;

void func_8008EE60(int a0, int a1, int a2, int a3, int a4) {
    S8008EE60 *s;
    Body8008EE60 *body;

    func_8008EC40();
    body = &D_800EEC34.body;
    s = &D_800EEC34;
    s->start = a0;
    s->cursor = body->base + 8;
    s->arg = a4;
    func_80099AC0(body, a0, a1, a2, a3, func_8008E860);
}
