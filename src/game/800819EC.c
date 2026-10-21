extern volatile int D_800B0D58;
extern volatile int D_800B0D5C;
extern volatile unsigned int *D_800B0D44;
extern volatile unsigned int *D_800B0D38;
extern void func_80081B28(void);
extern void func_8008163C(void);
extern int func_80081B5C(void);

int func_800819EC(int mode) {
    int pending;

    if (mode == 0) {
        func_80081B28();
        while (D_800B0D58 != D_800B0D5C) {
            func_8008163C();
            if (func_80081B5C() != 0) {
                return -1;
            }
        }
        while ((*D_800B0D44 & 0x01000000) || !(*D_800B0D38 & 0x04000000)) {
            if (func_80081B5C() != 0) {
                return -1;
            }
        }
        return 0;
    }
    pending = (D_800B0D58 - D_800B0D5C) & 0x3F;
    if (pending != 0) {
        func_8008163C();
    }
    if ((*D_800B0D44 & 0x01000000) || !(*D_800B0D38 & 0x04000000)) {
        if (pending != 0) {
            return pending;
        }
        return 1;
    }
    return pending;
}
