extern signed char D_800A6188;

void func_8005A54C(void);

void func_8005F798(void) {
    D_800A6188++;
    if (D_800A6188 >= 8) {
        D_800A6188 = 0;
    }
    func_8005A54C();
}
