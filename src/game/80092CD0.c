extern void func_8009C5C8(int);
extern void func_8009C9BC(void);
extern void func_80097114(int);
extern void func_80097558(int);
extern void func_80097128(int);
extern void func_8009166C(void);

typedef struct {
    char pad0[2];
    unsigned char b2;
    char pad3;
    unsigned char b4;
    char pad5[7];
    int w12;
    char pad16[132];
    int a;
    int b;
    int c;
} S80092CD0;
extern S80092CD0 D_800EEF0C;

void func_80092CD0(void) {
    S80092CD0 *s = &D_800EEF0C;
    s->b2 = 0;
    s->b4 = 0;
    s->w12 = 0;
    func_8009C5C8(0);
    func_8009C9BC();
    func_80097114(s->a);
    func_80097558(s->b);
    func_80097128(s->c);
    func_8009166C();
}
