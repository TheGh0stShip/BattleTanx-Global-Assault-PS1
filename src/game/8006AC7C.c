extern void func_80093590(int a);
extern void func_80091A90(int a, int b);
extern unsigned int func_80086C84(void);
extern void func_8009383C(int a, int b, int c, int d, int e, void (*f)(void));
extern void func_8006ADBC(void);
extern short D_800E540C;
extern int D_800ADE3C[];

static inline unsigned short rnd(void) {
    return func_80086C84() >> 16;
}

void func_8006AC7C(void) {
    unsigned short kind;
    unsigned short sub;

    func_80093590(4);
    func_80091A90(D_800E540C, D_800E540C);
    sub = 0;
    switch (kind = rnd() % 3) {
    case 0:
    case 1:
        sub = rnd() & 7;
        break;
    case 2:
        sub = rnd() % 3;
        break;
    }
    func_8009383C(D_800ADE3C[kind], 0, 0, sub, 0, func_8006ADBC);
}
