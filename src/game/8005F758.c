extern signed char D_800A6188;

void func_80058A8C(void);

void func_8005F758(void) {
    D_800A6188--;
    if (D_800A6188 < 0) {
        D_800A6188 = 7;
    }
    func_80058A8C();
}
