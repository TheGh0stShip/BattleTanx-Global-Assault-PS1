typedef unsigned char u8;

extern u8 D_800ABD60[];
extern u8 D_800AC080[];
extern u8 D_800D2FEC;
extern void func_80054A30(int value);

int func_80065498(void) {
    if (D_800D2FEC == 1) {
        D_800ABD60[0xE0] = 4;
        D_800ABD60[0x140] = 7;
    } else {
        D_800AC080[0xC0] = 4;
        D_800AC080[0x120] = 7;
        D_800AC080[0x1A0] = 4;
        D_800AC080[0x200] = 7;
    }
    func_80054A30(0xD);
    return 1;
}
