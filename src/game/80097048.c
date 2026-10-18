extern void func_800A0AD0(void);
extern int func_800A0B1C(void);
extern int func_800A09E0(void);

int func_80097048(int mode) {
    int busy;

    if (mode == 2) {
        func_800A0AD0();
        return 1;
    }
    if (func_800A0B1C() != 0) {
        return 0;
    }
    if (mode == 1) {
        busy = func_800A09E0();
        if (busy != 0) {
            return 0;
        }
    }
    return 1;
}
