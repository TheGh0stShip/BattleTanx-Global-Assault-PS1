typedef unsigned char u8;

extern u8 D_800ABD60[];
extern u8 D_800AC080[];
extern u8 D_800D2FEC;
extern void func_80054A30(int value);

int func_8006542C(void) {
    if (D_800D2FEC == 1) {
        D_800ABD60[0xA0] = 4;
        D_800ABD60[0x100] = 7;
    } else {
        D_800AC080[0x80] = 4;
        D_800AC080[0xE0] = 7;
        D_800AC080[0x160] = 4;
        D_800AC080[0x1C0] = 7;
    }
    func_80054A30(0xC);
    return 1;
}
