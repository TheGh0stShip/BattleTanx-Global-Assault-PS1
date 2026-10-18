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

extern int func_80088B00(int a, int b);

int func_80088B24(void) {
    StreamState *s = &D_800EEAE8;

    if (s->b3c == 0) {
        int pos = s->w50;

        if (pos == s->w54 && s->w58 != s->w5c) {
            s->w50 = func_80088B00(pos, 0x800);
            s->w58 += 0x800;
        }
        return D_800EEAE8.w48 + D_800EEAE8.w54;
    }
    return s->w70 + s->w84;
}
