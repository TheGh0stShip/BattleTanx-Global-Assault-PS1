extern void func_80096FFC(int);
extern void func_80094198(void);
extern int func_800A40C4(void);
extern void func_800A40D4(int);
extern void func_800A4280(void);
extern void func_800A417C(void);
extern void func_800A4210(void);
extern void func_80094168(void);

void func_8009F7BC(int a) {
    func_80096FFC(0);
    func_80094198();
    if (func_800A40C4() == 0) {
        a = 0;
    }
    func_800A40D4(a);
    func_800A4280();
    func_800A417C();
    func_800A4210();
    func_80094168();
}
