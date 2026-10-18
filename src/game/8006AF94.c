extern void func_80091D00(int value);
extern void func_80093BEC(int value);

void func_8006AF94(int enabled) {
    if (enabled) {
        func_80091D00(0xFA);
    }
    func_80093BEC(0);
}
