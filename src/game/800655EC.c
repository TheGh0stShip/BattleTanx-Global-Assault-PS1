typedef unsigned char u8;

extern u8 D_800ABD60[];
extern u8 D_800AC080[];
extern u8 D_800D2FEC;
extern void func_80054A30(int value);

int func_800655EC(void) {
    if (D_800D2FEC == 1) {
        D_800ABD60[0x1C0] = 4;
        D_800ABD60[0x240] = 7;
    } else {
        D_800AC080[0x2A0] = 4;
        D_800AC080[0x320] = 7;
    }
    func_80054A30(0x1C);
    func_80054A30(0x23);
    return 1;
}
