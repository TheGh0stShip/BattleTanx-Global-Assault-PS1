typedef unsigned char u8;

extern u8 D_800ABD60[];
extern u8 D_800AC080[];
extern u8 D_800D2FEC;
extern void func_80054A30(int value);

int func_80065588(void) {
    if (D_800D2FEC == 1) {
        D_800ABD60[0x180] = 4;
        D_800ABD60[0x200] = 5;
    } else {
        D_800AC080[0x260] = 4;
        D_800AC080[0x2E0] = 5;
    }
    func_80054A30(0xA);
    return 1;
}
