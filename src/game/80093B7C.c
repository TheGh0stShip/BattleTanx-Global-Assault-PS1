extern int func_80093960(int, int, int, int, int);
extern void func_800936D8(unsigned char);

typedef struct {
    char pad0[2];
    unsigned char open;
    char pad3[9];
    int handle;
    char pad16[8];
    int mode;
} S80093B7C;
extern S80093B7C D_800EEFAC;

int func_80093B7C(int a0, int a1, int a2) {
    S80093B7C *s = &D_800EEFAC;
    int r = 0;

    if (s->open != 0) {
        r = func_80093960(s->handle, s->mode, a0, a1, a2);
    }
    return r;
}

void func_80093BCC(int mode) {
    func_800936D8(mode);
}
