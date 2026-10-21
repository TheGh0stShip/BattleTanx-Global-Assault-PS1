extern volatile int D_800B6C74;
extern char D_800C4DB8[];
extern void func_80096F9C(char *msg);
extern void func_80096FFC(int a);
extern void func_8009700C(int a, int b);

void func_800889E8(int target, int timeout) {
    volatile int count = timeout << 15;

    while (D_800B6C74 < target) {
        if (--count == -1) {
            func_80096F9C(D_800C4DB8);
            func_80096FFC(0);
            func_8009700C(3, 0);
            return;
        }
    }
}
