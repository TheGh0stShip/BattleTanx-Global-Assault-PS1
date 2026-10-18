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

extern void func_80091604(int a);
extern void func_8009162C(int a);
extern void func_80091618(int a);
extern void func_8009166C(void);
extern void func_80088DC8(unsigned char a);

void func_80088E48(int mode) {
    func_80091604(0);
    func_8009162C(0);
    func_80091618(0);
    D_800EEAE8.w44 = 0;
    D_800EEAE8.b40 = 0;
    D_800EEAE8.b42 = 0;
    D_800EEAE8.b39 = 0;
    D_800EEAE8.b38 = 0;
    func_8009166C();
    if (D_800EEAE8.b33 == 0) {
        func_80088DC8(mode);
    }
}
