typedef struct {
    int mode;
    int count;
    int a;
    int b;
} Setup;
extern unsigned short D_800E4994;
extern unsigned char D_800A6188;
extern unsigned char D_800A6189;
extern unsigned short D_800AACDC;
extern unsigned char D_800AEA46;
extern unsigned short D_800A60D8;
extern int D_800A6070;
extern int D_800EAFBC;
extern unsigned char D_800AACD6;
extern unsigned char D_800AACD7;
extern unsigned char D_800AACD8;
extern unsigned char D_800AACD9;
extern unsigned char D_800AACDA;
extern unsigned char D_800A60DC[];
extern int D_800A60C4[];
extern int D_800A6094[];
extern Setup D_800A6084;
extern int func_80054A30(unsigned char);
extern void func_8003DFC8(void);
extern void func_8003DF4C(void);

int func_8005B0DC(void) {
    unsigned char i;

    D_800E4994 = 4;
    D_800A6188 = 0;
    D_800A6189 = 0;
    if (D_800AACDC == 0) {
        func_80054A30(1);
        D_800AACDC = 1;
    }
    D_800AEA46 = 100;
    if (D_800A60D8 != 0 && D_800A6070 == 1) {
        D_800A6070 = 2;
    }
    if (D_800A6070 != 1) {
        if (D_800A6070 == 2) {
            D_800A6070 = 1;
            D_800EAFBC = 6;
        } else {
            D_800EAFBC = 0;
            D_800AACD6 = 0;
            D_800AACD7 = 0;
            D_800AACD8 = 0;
            D_800AACD9 = 0;
            D_800AACDA = 0;
            for (i = 0; i < 4; i++) {
                D_800A60DC[i] = 0;
                D_800A60C4[i] = 0;
                D_800A6094[i] = 2;
            }
            D_800A6084.mode = 3;
            D_800A6084.count = 1;
            D_800A6084.a = 0;
            D_800A6084.b = 0;
            func_8003DFC8();
            func_8003DF4C();
        }
    }
    return 0;
}
