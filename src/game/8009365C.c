extern void func_80091604(int);
extern void func_8009166C(void);

typedef struct {
    char pad0[3];
    unsigned char b3;
    char pad4[3];
    unsigned char b7;
    char pad8;
    unsigned char b9;
    volatile unsigned char b10;
    char pad11[37];
    int w48;
    void (*cb)(int);
} S8009365C;
extern S8009365C D_800EEFAC;

void func_8009365C(unsigned char mode) {
    S8009365C *s = &D_800EEFAC;
    void (*cb)(int) = s->cb;

    s->w48 = 0;
    s->cb = 0;
    func_80091604(0);
    s->b3 = 0;
    s->b7 = 0;
    s->b9 = 0;
    s->b10 = 0;
    func_8009166C();
    if (cb != 0) {
        cb(mode == 2);
    }
}
