extern void func_80091A34(void);
extern int func_80091604(void *);
extern int func_8009713C(int, int, int);
extern void func_800936D8(unsigned char);
extern void func_80093744(unsigned char);
extern void func_80093BCC(void);
extern void func_8009377C(void);

typedef struct {
    unsigned char active;
    char pad1[2];
    unsigned char ready;
    volatile unsigned char busy;
    char pad5[51];
    int cb;
    int prev;
} S80093BEC;
extern S80093BEC D_800EEFAC;

int func_80093BEC(int cb) {
    S80093BEC *s = &D_800EEFAC;
    int r = 0;

    if (s->active != 0) {
        if (s->ready != 0) {
            func_80091A34();
            s->busy = 1;
            s->cb = cb;
            s->prev = func_80091604(func_80093BCC);
            if (func_8009713C(9, 0, 0) != 0) {
                r = 1;
            } else {
                func_800936D8(5);
            }
        }
    }
    return r;
}

void func_80093C90(unsigned char mode) {
    func_80093744(mode);
    func_80091604(func_8009377C);
}
