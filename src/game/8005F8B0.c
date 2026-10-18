extern short D_800E4994;
extern int D_800EAFBC;
extern int D_800A8F0C;

void func_8005CA14(void);

int func_8005F8B0(void) {
    D_800E4994 = 1;
    D_800EAFBC = 2;
    D_800A8F0C = 0;
    func_8005CA14();
    return 0;
}
