extern unsigned char D_800D2FEC;
extern unsigned char D_800ABD60[];
extern unsigned char D_800AC080[];
extern int D_800ABA84;
extern void func_80054A30(int value);

void func_80065504(void) {
    if (D_800D2FEC == 1) {
        D_800ABD60[0x60] = 4;
        D_800ABD60[0x160] = 4;
        D_800ABD60[0x1E0] = 5;
        D_800ABD60[0x2A0] = 6;
    } else {
        D_800AC080[0x220] = 4;
        D_800AC080[0x240] = 4;
        D_800AC080[0x2C0] = 5;
        D_800AC080[0x380] = 6;
    }
    func_80054A30(12);
    D_800ABA84 = 1;
}
