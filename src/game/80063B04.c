typedef unsigned char u8;

extern u8 D_800AAE24[];
extern int func_800862D4(int sound);
extern void func_80086270(int sound, int enabled);
extern void func_8008634C(int sound, void *data, int value);

int func_80063B04(void) {
    if (func_800862D4(0)) {
        func_80086270(0, 0);
    } else {
        func_80086270(0, 1);
        func_8008634C(0, D_800AAE24, 0);
    }
    return 0;
}
