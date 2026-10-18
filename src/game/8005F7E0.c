extern signed char D_800A6188;
extern signed char D_800A6189;

void func_80058A8C(int value);

void func_8005F7E0(int value) {
    D_800A6189--;
    if (D_800A6189 < 0) {
        if (D_800A6188 == 2 || D_800A6188 == 6) {
            D_800A6189 = 5;
        } else {
            D_800A6189 = 6;
        }
    }
    func_80058A8C(value);
}
