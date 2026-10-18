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

extern void func_80089188(void);
extern void func_80091604(void (*cb)(void));
extern int func_8009713C(int cmd, int a, int b);
extern int func_80089098(int arg);
extern void func_80089294(void);
extern void func_80088D50(unsigned char mode);

void func_800891F0(unsigned char intr) {
    int ready = 1;

    if (intr == 2) {
        func_80091604(func_80089188);
        D_800EEAE8.b38 = 0;
        if (func_8009713C(21, 0, 0) != 0) {
            ready = 0;
        } else {
            intr = 5;
        }
    }
    if (ready) {
        if (func_80089098(0) != 0) {
            func_80089294();
        } else {
            func_80088D50(intr);
        }
    }
}
