extern int D_800DDDEC;
extern int D_800A48DC;
extern void func_8007FA74(int value);
extern void func_80068F9C(int value);
extern void func_80068E70(void);

void func_8003DD64(void) {
    func_8007FA74(0);
    func_80068F9C(D_800DDDEC);
    D_800DDDEC = 0;
    if (D_800A48DC == 0) {
        func_80068E70();
    }
}
