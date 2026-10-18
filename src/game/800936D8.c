extern void func_80091604(int);

typedef struct {
    char pad0[4];
    unsigned char b4;
    char pad5;
    volatile unsigned char b6;
    char pad7[49];
    void (*cb)(int);
} S800936D8;
extern S800936D8 D_800EEFAC;

void func_800936D8(unsigned char mode) {
    S800936D8 *s = &D_800EEFAC;
    void (*cb)(int) = s->cb;

    s->cb = 0;
    func_80091604(0);
    s->b4 = 0;
    s->b6 = 1;
    if (cb != 0) {
        cb(mode == 2);
    }
}
