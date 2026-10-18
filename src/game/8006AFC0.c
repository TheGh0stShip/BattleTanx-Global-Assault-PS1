extern short D_800E540C;
extern void func_80091CC8(int value, int first, int second);
extern void func_80093CBC(void);

void func_8006AFC0(int enabled) {
    func_80093CBC();
    if (enabled) {
        func_80091CC8(0xFA, D_800E540C, D_800E540C);
    }
}
