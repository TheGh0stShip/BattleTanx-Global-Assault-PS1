extern signed char D_800A6188;
extern signed char D_800A6189;
extern void func_8005A54C(int);

void func_8005F83C(int arg) {
    D_800A6189++;
    if (D_800A6188 == 2 || D_800A6188 == 6) {
        if (D_800A6189 >= 6) {
            D_800A6189 = 0;
        }
    } else if (D_800A6189 >= 7) {
        D_800A6189 = 0;
    }
    func_8005A54C(arg);
}
