extern unsigned char D_800A4380;
extern int D_800A437C;
extern unsigned char D_800AACE4;
extern int D_800C60CC;
extern int D_800C60C8;
extern int D_800C60E4;
extern int D_800C60D0;
extern int D_800C60DC;
extern int D_800C60D8;
extern int D_800D2FD4;
extern int D_800D2FD8;
extern int D_800D2FDC;
extern int D_800D2FC8;
extern int D_800D2FCC;
extern int D_800D2FD0;
extern int func_800851D4(void);
extern void func_80054C08(void);
extern void func_8006AF94(int);
extern void func_80054CA0(void);
extern void func_8006AFC0(int);

void func_800201F8(signed char ports) {
    int missing = 0;

    if (ports == 2) {
        missing = (func_800851D4() & 2) ^ 2;
    }
    D_800A4380 = missing | ((func_800851D4() & 1) ^ 1);
    if (ports == 1 && D_800AACE4 != 0) {
        missing = func_800851D4() & 2;
        missing ^= 2;
        missing |= (func_800851D4() & 1) ^ 1;
        D_800A4380 = missing;
    }
    if (D_800A4380 != 0) {
        if (D_800A437C == 0) {
            D_800D2FD4 = D_800C60CC;
            D_800D2FD8 = D_800C60C8;
            D_800D2FDC = D_800C60E4;
            D_800D2FC8 = D_800C60D0;
            D_800D2FCC = D_800C60DC;
            D_800D2FD0 = D_800C60D8;
            if (D_800C60CC == 1) {
                D_800C60DC = 7;
            }
            func_80054C08();
            func_8006AF94(0);
        }
        D_800A437C = 1;
    } else if (D_800A437C == 1) {
        func_80054CA0();
        func_8006AFC0(0);
        D_800A437C = 0;
        D_800C60CC = D_800D2FD4;
        D_800C60C8 = D_800D2FD8;
        D_800C60E4 = D_800D2FDC;
        D_800C60D0 = D_800D2FC8;
        D_800C60DC = D_800D2FCC;
        D_800C60D8 = D_800D2FD0;
    }
}
