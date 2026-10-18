extern int func_800A2CB8(void *, int);
extern void func_800A2DC8(void *);

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

extern int func_8009940C(Ctx *, int, int, int, void *);
extern void func_800994B8(Ctx *, int, int, int, int);

int func_800995A8(Ctx *c, Entry *list, void *saved) {
    int ret = 0;
    if (func_800A2CB8(c, ret) == 0) {
        func_800A2DC8(c);
    }
    c->list = list;
    c->next_callback = saved;
    if (list->type == 1) {
        ret = func_80099340(c, &list->a, list->b, list->c, list->d, list->e, func_800994B8);
    } else if (list->type == 0) {
        ret = func_8009940C(c, list->a, list->b, list->d, func_800994B8);
    }
    return ret;
}
