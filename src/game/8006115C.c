extern signed char D_800A6188;
extern signed char D_800A6189;
extern int D_800A60E0[][6];
extern int D_800A60D4;
extern char D_800A4381;
extern void func_8006A290(void);
extern void func_800203E0(void);
extern void func_8005A648(int);

int func_8006115C(int arg) {
    D_800A60D4 = D_800A60E0[D_800A6188][D_800A6189];
    func_8006A290();
    D_800A4381 = 0;
    func_800203E0();
    func_8005A648(arg);
    return 1;
}
