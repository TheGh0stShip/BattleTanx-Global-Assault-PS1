extern signed char D_800A6080;
extern signed char D_800A6081;
extern unsigned char D_800E4830;
extern unsigned char D_800E4834;
extern int D_800EAFBC;
extern void func_80054DC4(int);
extern void func_8006B044(short);

int func_8005F678(void) {
    D_800A6080 = D_800E4834;
    D_800A6081 = D_800E4830;
    func_80054DC4(D_800A6080 * 60);
    func_8006B044(D_800A6081 * 360);
    D_800EAFBC = 2;
    return 1;
}
