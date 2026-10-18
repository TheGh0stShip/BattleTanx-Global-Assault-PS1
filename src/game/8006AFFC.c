extern void func_80091D00(int value);
extern void func_80093D6C(void);

void func_8006AFFC(int enabled) {
    if (enabled) {
        func_80091D00(0xFA);
    }
    func_80093D6C();
}
