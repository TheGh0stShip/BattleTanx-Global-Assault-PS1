extern void func_800916F4(void);
extern void func_80091A34(void);
extern void func_80091604(void *);
extern int func_8009713C(int, int, int);
extern void func_80093744(int);
extern void func_80093C90(void);

typedef struct {
    unsigned char active;
    char pad1[4];
    volatile unsigned char b5;
    volatile unsigned char b6;
} S80093CBC;
extern S80093CBC D_800EEFAC;

int func_80093CBC(void) {
    S80093CBC *s = &D_800EEFAC;
    int r = 0;

    if (s->active != 0) {
        func_800916F4();
        if (s->b6 != 0) {
            func_80091A34();
            s->b6 = 0;
            s->b5 = 1;
            func_80091604(func_80093C90);
            if (func_8009713C(27, 0, 0) != 0) {
                r = 1;
            } else {
                func_80093744(5);
            }
        }
    }
    return r;
}
