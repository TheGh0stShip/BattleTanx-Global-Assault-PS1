extern unsigned int *D_800B0D38;
extern unsigned int *D_800B0D3C;
extern unsigned int *D_800B0D40;
extern unsigned int *D_800B0D44;

void func_800812F0(unsigned int value) {
    *D_800B0D38 = 0x04000002;
    *D_800B0D3C = value;
    *D_800B0D40 = 0;
    *D_800B0D44 = 0x01000401;
}
