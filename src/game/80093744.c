extern void *func_80091604(void *);
extern void func_8009365C(unsigned char);
extern int func_8009713C(int, int, int);

typedef struct {
    char pad0[5];
    unsigned char b5;
    char pad6;
    volatile unsigned char b7;
    char pad8[40];
    void (*cb)(void);
    char pad52[8];
    void *prev;
} S80093744;
extern S80093744 D_800EEFAC;

void func_80093744(void) {
    S80093744 *s = &D_800EEFAC;

    func_80091604(s->prev);
    s->prev = 0;
    s->b5 = 0;
}

void func_8009377C(unsigned char mode) {
    S80093744 *s;
    void (*cb)(void);

    func_80091604(0);
    if (mode == 2) {
        s = &D_800EEFAC;
        s->b7 = 1;
        if ((cb = s->cb) != 0) {
            s->cb = 0;
            cb();
        }
    } else {
        func_8009365C(mode);
    }
}

void func_800937E4(unsigned char mode) {
    int ok = 0;

    if (mode == 2) {
        func_80091604(func_8009377C);
        ok = func_8009713C(27, 0, 0);
    }
    if (ok == 0) {
        func_8009365C(5);
    }
}
