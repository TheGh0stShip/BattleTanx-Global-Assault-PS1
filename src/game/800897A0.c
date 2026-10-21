typedef struct {
    char pad0[0xC];
    int w0c;
    char pad10[8];
    int w18;
    char pad1c[4];
    int w20;
    char pad24[0xC];
    volatile unsigned char b30;
    volatile unsigned char b31;
    volatile unsigned char b32;
    volatile unsigned char b33;
    volatile unsigned char b34;
    volatile unsigned char b35;
    volatile unsigned char b36;
    volatile unsigned char b37;
    volatile unsigned char b38;
    volatile unsigned char b39;
    volatile unsigned char b3a;
    volatile unsigned char b3b;
    volatile unsigned char b3c;
    char pad3d[3];
    volatile unsigned char b40;
    volatile unsigned char b41;
    volatile unsigned char b42;
    volatile unsigned char b43;
    volatile unsigned int w44;
    int w48;
    int w4c;
    int w50;
    int w54;
    int w58;
    int w5c;
    unsigned char loc[4];
    int w64;
    char pad68[8];
    int w70;
    char pad74[0x10];
    int w84;
    char pad88[8];
    unsigned int w90;
    unsigned int w94;
    void *w98;
    unsigned char result[0xC];
} StreamState;
extern StreamState D_800EEAE8;
extern void func_80089518(void);
extern void func_80091618(void (*cb)(void));
extern unsigned int func_800976A0(unsigned char *result);
extern void *func_80088B24(void);
extern int func_80097518(void *buf, int n);
extern int func_80089098(int arg);
extern void func_80089A58(void);
extern void func_80088E48(int mode);

void func_800897A0(void) {
    StreamState *s;
    register unsigned int pos asm("$4");
    register unsigned int sh asm("$3");

    func_80091618(0);
    s = &D_800EEAE8;
    if (s->b3a != 0) {
        s->b3b = 1;
        return;
    }
    if (func_800976A0(s->result) == (sh = (pos = s->w90) >> 11)) {
        s->w98 = func_80088B24();
        func_80091618(func_80089518);
        if (func_80097518(s->w98, 512) != 0) {
            return;
        }
        if (func_80089098(1) == 0) {
            func_80088E48(5);
            return;
        }
    }
    func_80089A58();
}
