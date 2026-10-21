extern int func_80094198(void);
extern void func_80094168(void);
extern int func_80094158(int, int, int, void (*)(void));
extern int func_800940B4(int);
extern int func_80094188(int);
extern void func_8009F860(void);
extern void func_80096AF0(void);
extern void func_80096770(void);
extern void func_80096784(void);
extern void func_80096798(void);
extern void func_800967AC(void);
extern void func_800967C0(void);
extern void func_800967D4(void);
extern void func_800967E8(void);
extern void func_800967FC(void);

extern int D_800EF050;
extern int D_800EF054;
extern int D_800EF058;
extern int D_800EF05C;
extern int D_800EF060;
extern int D_800EF064;
extern int D_800EF068;
extern int D_800EF06C;

void func_80096840(void)
{
    int crit;

    crit = func_80094198();
    D_800EF050 = func_80094158(0xF4000001, 0x0004, 0x1000, func_80096770);
    D_800EF054 = func_80094158(0xF4000001, 0x8000, 0x1000, func_80096784);
    D_800EF058 = func_80094158(0xF4000001, 0x0100, 0x1000, func_80096798);
    D_800EF05C = func_80094158(0xF4000001, 0x2000, 0x1000, func_800967AC);
    D_800EF060 = func_80094158(0xF0000011, 0x0004, 0x1000, func_800967C0);
    D_800EF064 = func_80094158(0xF0000011, 0x8000, 0x1000, func_800967D4);
    D_800EF068 = func_80094158(0xF0000011, 0x0100, 0x1000, func_800967E8);
    D_800EF06C = func_80094158(0xF0000011, 0x2000, 0x1000, func_800967FC);
    func_800940B4(D_800EF050);
    func_800940B4(D_800EF054);
    func_800940B4(D_800EF058);
    func_800940B4(D_800EF05C);
    func_800940B4(D_800EF060);
    func_800940B4(D_800EF064);
    func_800940B4(D_800EF068);
    func_800940B4(D_800EF06C);
    func_80096AF0();
    if (crit == 1) {
        func_80094168();
    }
}

void func_80096A1C(void)
{
    func_8009F860();
}

void func_80096A3C(void)
{
    int crit;

    crit = func_80094198();
    func_80094188(D_800EF050);
    func_80094188(D_800EF054);
    func_80094188(D_800EF058);
    func_80094188(D_800EF05C);
    func_80094188(D_800EF060);
    func_80094188(D_800EF064);
    func_80094188(D_800EF068);
    func_80094188(D_800EF06C);
    if (crit == 1) {
        func_80094168();
    }
}
