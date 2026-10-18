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
    char pad34[4];
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
    char pad94[4];
    void *w98;
    unsigned char result[0xC];
} StreamState;
extern StreamState D_800EEAE8;

extern void func_800898F4(unsigned char intr);
extern void func_80091604(void (*cb)(unsigned char));
extern void func_8009759C(unsigned int sector, unsigned char *loc);
extern int func_8009713C(int cmd, unsigned char *param, int c);
extern int func_80089098(int arg);
extern void func_80089A58(void);
extern void func_80088E48(int mode);

void func_80089984(unsigned char intr) {
    int ready = 1;

    if (intr == 2) {
        StreamState *s;

        func_80091604(func_800898F4);
        s = &D_800EEAE8;
        func_8009759C(s->w90 >> 11, s->loc);
        if (func_8009713C(6, s->loc, 0) != 0) {
            s->b38 = ready;
            ready = 0;
        }
    }
    if (ready) {
        if (D_800EEAE8.b3a != 0) {
            D_800EEAE8.b3b = 1;
        } else if (func_80089098(1) != 0) {
            func_80089A58();
        } else {
            func_80088E48(5);
        }
    }
}
