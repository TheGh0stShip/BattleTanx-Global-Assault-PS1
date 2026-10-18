typedef unsigned char u8;

extern u8 D_800AAE24[];
extern int func_800862D4(int sound);
extern void func_80086270(int sound, int enabled);
extern void func_8008634C(int sound, void *data, int value);

int func_80063B58(void) {
    if (func_800862D4(1)) {
        func_80086270(1, 0);
    } else {
        func_80086270(1, 1);
        func_8008634C(1, D_800AAE24, 0);
    }
    return 0;
}
