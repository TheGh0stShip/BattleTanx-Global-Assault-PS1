typedef unsigned char u8;

extern u8 D_800AAD00;
extern u8 D_800ABA5B;
extern int D_800C60C8;
extern int D_800C60DC;

int func_80065324(void) {
    D_800ABA5B = 1;
    D_800AAD00 = 2;
    D_800C60C8 = 0;
    D_800C60DC = 2;
    return 3;
}
