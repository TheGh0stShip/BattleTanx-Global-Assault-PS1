extern void func_8008AA48(void *, int, int);
extern int func_80091804(void);
extern void func_80091978(void *);
extern void func_80093590(int);
extern void func_80093D6C(void);

typedef struct {
    char pad0[2];
    unsigned char open;
    char pad3[9];
    int handle;
} S80093508;
extern S80093508 D_800EEF0C;
extern unsigned char D_800EEFAC[];

int func_80093508(int handle) {
    S80093508 *s = &D_800EEF0C;
    int r = 0;

    if (s->open != 0) {
        r = s->handle == handle;
    }
    return r;
}

void func_80093538(void) {
    func_8008AA48(D_800EEFAC, 0, 64);
    if (func_80091804() != 0) {
        D_800EEFAC[0] = 1;
        func_80091978(func_80093D6C);
    }
    func_80093590(4);
}
