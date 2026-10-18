extern int func_800A2CB8(void *, int);
extern void func_800A2DC8(void *);
extern int func_800A2A98(void *, int, int, int, int, int, void *);
extern void func_800991E8(void);
extern void *D_800EF124;

typedef struct Ctx {
    char pad0[0x4C];
    int mode;
    int pad50;
    int unk54;
    int pad58;
    int *src;
    int srcval;
    int a2;
    int a3;
    int a4;
    int pad70;
    int a6;
} Ctx;

int func_80099340(Ctx *c, int *src, int a2, int a3, int a4, int a5, int a6) {
    if (func_800A2CB8(c, 0) == 0) {
        func_800A2DC8(c);
    }
    D_800EF124 = c;
    c->unk54 = 0;
    c->src = src;
    if (src != 0) {
        c->srcval = *src;
    } else {
        c->srcval = 0;
    }
    c->a2 = a2;
    c->a3 = a3;
    c->a4 = a4;
    c->a6 = a6;
    c->mode = 4;
    return func_800A2A98(c, 0, 0, 0, 0, a5, func_800991E8);
}
