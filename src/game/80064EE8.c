extern int D_800AD9E8;
extern unsigned char D_800D2FEC;
extern unsigned char D_800ABD60[];
extern unsigned char D_800AC080[];
extern unsigned int D_800E5338;
extern unsigned int D_800E52D0;
extern unsigned int D_800E52B0;
extern void func_80054A30(int);
extern void func_80054D4C(void);

int func_80064EE8(void) {
    if (D_800AD9E8 == 0) {
        if (D_800D2FEC == 1) {
            D_800ABD60[0x1A0] = 4;
            D_800ABD60[0x220] = 7;
        } else {
            D_800AC080[0x280] = 4;
            D_800AC080[0x300] = 7;
        }
        D_800E52B0 = (D_800E52D0 + 30 - D_800E5338) / 30;
        func_80054A30(0);
        D_800AD9E8 = 1;
    }
    D_800E5338 += D_800E52B0;
    if (D_800E5338 >= D_800E52D0) {
        D_800E5338 = D_800E52D0;
        func_80054D4C();
        func_80054A30(13);
        D_800AD9E8 = 0;
        return 1;
    }
    return 0;
}
