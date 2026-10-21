typedef struct {
    char pad0[0x10];
    int w10;
    int w14;
    char pad18[0x31 - 0x18];
    volatile unsigned char b31;
    volatile unsigned char b32;
    volatile unsigned char b33;
    char pad34[0x39 - 0x34];
    volatile unsigned char b39;
    volatile unsigned char b3a;
    volatile unsigned char b3b;
    volatile unsigned char b3c;
    char pad3d[0x5C - 0x3D];
    int w5c;
    char pad60[0x6C - 0x60];
    int w6c;
    int w70;
    int w74;
    int w78;
    int w7c;
    int w80;
    int w84;
    char pad88[8];
    int w90;
} StreamState;
extern StreamState D_800EEAE8;

extern void func_80091984(void);
extern void func_8009194C(void);
extern void func_80088FB0(void);
extern void func_800916F4(void);
extern void func_80088A80(void);
extern int func_80089A58(void);

int func_80089B70(int pos, int dest, int len, int total, int arg4, int arg5, int arg6)
{
    int primed;
    int saved;
    int result;
    int ok;
    int prev;
    int count;

    primed = D_800EEAE8.b3c == 1;
    saved = D_800EEAE8.w6c;
    D_800EEAE8.w6c = arg6;
    func_80091984();
    func_8009194C();
    result = 1;
    if (!D_800EEAE8.b33 || !D_800EEAE8.b32) {
        D_800EEAE8.w6c = saved;
        func_80088FB0();
        D_800EEAE8.w6c = arg6;
    }
    func_800916F4();

    D_800EEAE8.w78 = pos & 0x7FF;
    __asm__ volatile("");
    pos &= ~0x7FF;
    D_800EEAE8.w70 = dest;
    prev = D_800EEAE8.w90;
    D_800EEAE8.w74 = total;
    D_800EEAE8.w7c = 0x800 - D_800EEAE8.w78;
    if (len < D_800EEAE8.w7c)
        D_800EEAE8.w7c = len;
    ok = 1;
    D_800EEAE8.w80 = arg4;
    D_800EEAE8.w90 = pos;
    D_800EEAE8.w84 = total - len;

    if (D_800EEAE8.b39 && prev == pos) {
        if (!D_800EEAE8.b3b) {
            D_800EEAE8.b33 = 0;
            D_800EEAE8.b39 = 0;
            if (primed) {
                D_800EEAE8.b3c = 1;
                D_800EEAE8.b33 = 1;
            }
            D_800EEAE8.b3a = 0;
            ok = D_800EEAE8.b3b == 1;
        }
        if (ok) {
            D_800EEAE8.b3a = 1;
            D_800EEAE8.b33 = 1;
            D_800EEAE8.b39 = 1;
            D_800EEAE8.w14++;
        } else {
            D_800EEAE8.w10++;
        }
    }
    if (ok) {

    if (!D_800EEAE8.b33 || !D_800EEAE8.b32 || D_800EEAE8.b39 || D_800EEAE8.b3c) {
        D_800EEAE8.w6c = saved;
        func_80088FB0();
        D_800EEAE8.w6c = arg6;
    }
    func_800916F4();
    if (pos != D_800EEAE8.w5c && !primed)
        func_80088A80();
    D_800EEAE8.b33 = 0;
    D_800EEAE8.b39 = 0;
    D_800EEAE8.b31 = 0;
    D_800EEAE8.b3b = 0;
    D_800EEAE8.b3a = 0;
    if (primed) {
        D_800EEAE8.b3c = 1;
        D_800EEAE8.b33 = 1;
    } else if (arg5) {
        D_800EEAE8.b39 = 1;
        D_800EEAE8.b33 = 1;
    }
    result = func_80089A58();
    }
    return result;
}
