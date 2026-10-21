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

extern volatile int D_800C60BC;
extern void func_800891F0(unsigned char intr);
extern void func_80091604(void (*cb)(unsigned char));
extern void func_80091618(void (*cb)(unsigned char));
extern void func_8009162C(void (*cb)(unsigned char));
extern void func_8009759C(unsigned int sector, unsigned char *loc);
extern int func_8009713C(int cmd, unsigned char *param, int c);
extern int func_80089098(int arg);
extern void func_80088D50(unsigned char mode);

int func_80089294(void) {
    StreamState *s = &D_800EEAE8;
    int retry;
    int ok = 1;

    if (s->b34 != 0) {
        s->b35 = ok;
        return ok;
    }
    D_800C60BC = ok;
    s->w44 = 0;
    s->b42 = 0;
    s->b41 = 0;
    s->b40 = ok;
    do {
        StreamState *st = &D_800EEAE8;

        st->b35 = 0;
        st->b34 = 1;
        func_80091604(func_800891F0);
        func_80091618(0);
        func_8009162C(0);
        retry = 0;
        func_8009759C(st->w94 >> 11, st->loc);
        if (func_8009713C(2, st->loc, retry) == 0) {
            retry = func_80089098(retry);
            if (retry == 0) {
                func_80088D50(5);
                ok = 0;
            }
        }
        st->b34 = 0;
        if (retry == 0 && ok != 0) {
            retry = st->b35 != 0;
        }
    } while (retry != 0);
    return ok;
}
