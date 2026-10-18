typedef unsigned char u8;

extern u8 D_800E4838;
extern void func_80091A90(int first, int second);

void func_8006AEE8(int enabled) {
    if (enabled) {
        func_80091A90(0, 0);
        D_800E4838 = 1;
    }
}
