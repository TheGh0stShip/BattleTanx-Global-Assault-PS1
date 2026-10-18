extern unsigned short D_800E4994;
extern unsigned char D_800E4834;
extern unsigned char D_800E4830;
extern unsigned char D_800A6080;
extern unsigned char D_800A6081;
extern int D_800A6070;
extern unsigned short D_800A60D8;
extern signed char D_800A606C;
extern unsigned char D_800A4381;
extern short D_800AACDC;
extern char D_800A8618[];
extern char D_800A9A14[];
extern char D_800A75F0[];
extern char D_800AA208[];
extern char D_800AA978[];
extern void func_80059550(void *, void *, int);
extern void func_8006A290(void);
extern void func_800203E0(void);

int func_8005B24C(void *back) {
    switch (D_800E4994) {
    case 1:
        D_800E4834 = D_800A6080;
        D_800E4830 = D_800A6081;
        func_80059550(D_800A8618, back, 1);
        break;
    case 3:
        func_80059550(D_800A9A14, back, 1);
        break;
    case 2:
        break;
    default:
        if (D_800A6070 == 1) {
            if (D_800A60D8 != 0) {
                func_80059550(D_800A75F0, back, 1);
            } else {
                func_8006A290();
                D_800A4381 = 0;
                func_800203E0();
            }
        } else if (D_800A606C == 1) {
            func_80059550(D_800AA208, back, 1);
        } else {
            func_80059550(D_800AA978, back, 1);
        }
        break;
    }
    D_800AACDC = 0;
    return 1;
}
