extern int func_800A2CB8(void *, int);
extern void func_800A2DC8(void *);
extern int func_800A2C10(void *, int, int, int, void *);
extern void func_80098D50(void *, int, int);
extern void func_800991E8(void);
extern void *D_800EF124;

typedef struct Entry {
    int type;
    int a;
    int b;
    int c;
    int d;
    int e;
} Entry;

typedef struct Ctx {
    char pad0[0x4C];
    int mode;
    Entry *list;
    int unk54;
    unsigned char unk58;
    char pad59[3];
    int *src;
    int srcval;
    int a2;
    int a3;
    int a4;
    int pad70;
    void *callback;
    void *next_callback;
} Ctx;

extern int func_80099340(Ctx *, int *, int, int, int, int, void *);
void func_800994B8(Ctx *c, int a1, int a2, int a3, int arg);

int func_8009940C(Ctx *c, int b, int a2, int a3, void *callback) {
    if (func_800A2CB8(c, 0) == 0) {
        func_800A2DC8(c);
    }
    D_800EF124 = c;
    c->unk54 = 0;
    c->unk58 = b;
    c->src = 0;
    c->a2 = a2;
    c->a3 = a3;
    c->a4 = a3;
    c->callback = callback;
    c->mode = 1;
    return func_800A2C10(c, 4, 0, 0, func_800991E8);
}

void func_800994B8(Ctx *c, int a1, int a2, int a3, int arg) {
    int done = 1;
    if (arg != 0) {
        Entry *p = c->list;
        Entry *e = p + 1;
        int type;
        c->list = e;
        type = e->type;
        if (type != 2) {
            if (type == 1) {
                done = func_80099340(c, &e->a, e->b, e->c, e->d, e->e, func_800994B8) == 0;
            } else if (type == 0) {
                if (func_8009940C(c, e->a, e->b, e->d, func_800994B8) != 0) {
                    done = 0;
                }
            }
        }
    }
    if (done) {
        c->callback = c->next_callback;
        c->next_callback = 0;
        c->list = 0;
        func_80098D50(c, 2, arg);
    }
}
