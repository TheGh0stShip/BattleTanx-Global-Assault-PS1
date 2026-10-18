extern int func_80097114(int);
extern int func_80097558(int);
extern int func_80097128(int);
extern void func_800916F4(void);
extern void func_8009C4F8(int);
extern void func_8009C5C8(void *);
extern void func_80092AFC(void);
extern void func_8009CEDC(int, unsigned int);
extern void func_8009CE4C(int, int, int, int, int);

typedef struct {
    char pad0[16];
    int format;
    char pad20[4];
    int rate;
    int channels;
    char pad32[44];
    unsigned int size;
    char pad80[4];
    int addr;
} Info80092C20;

typedef struct {
    char pad0[2];
    unsigned char b2;
    char pad3;
    unsigned char b4;
    char pad5[7];
    Info80092C20 *info;
    char pad16[132];
    int a;
    int b;
    int c;
} S80092C20;
extern S80092C20 D_800EEF0C;

int func_80092C20(void) {
    S80092C20 *s;
    int a = func_80097114(0);

    s = &D_800EEF0C;
    s->a = a;
    s->b = func_80097558(0);
    s->c = func_80097128(0);
    func_800916F4();
    func_8009C4F8(0);
    func_8009C5C8(func_80092AFC);
    func_8009CEDC(s->info->addr, s->info->size >> 11);
    func_8009CE4C(s->info->format == 3, s->info->rate, s->info->channels, 0, 0);
    s->b2 = 1;
    s->b4 = 0;
    return 1;
}
