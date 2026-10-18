extern int D_800C60C0;
extern int D_800EAFBC;
extern void func_8007646C(void);
extern void func_8006AB60(int transition);
extern void func_80075AEC(void);

int func_8005F440(void) {
    if (D_800C60C0 & 1) {
        func_8007646C();
        func_8006AB60(11);
        func_80075AEC();
    }
    D_800EAFBC = 5;
    return 0;
}
