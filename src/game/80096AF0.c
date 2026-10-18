extern int D_800EF050;
extern int D_800EF054;
extern int D_800EF058;
extern int D_800EF05C;
extern int D_800EF060;
extern int D_800EF064;
extern int D_800EF068;
extern int D_800EF06C;
extern volatile int D_800EF070;
extern volatile int D_800EF074;
extern volatile int D_800EF078;
extern volatile int D_800EF07C;
extern volatile int D_800EF080;
extern volatile int D_800EF084;
extern volatile int D_800EF088;
extern volatile int D_800EF08C;
int func_8009AED4(int);

void func_80096AF0(void)
{
    func_8009AED4(D_800EF050);
    func_8009AED4(D_800EF054);
    func_8009AED4(D_800EF058);
    func_8009AED4(D_800EF05C);
    func_8009AED4(D_800EF060);
    func_8009AED4(D_800EF064);
    func_8009AED4(D_800EF068);
    func_8009AED4(D_800EF06C);
    D_800EF070 = D_800EF074 = D_800EF078 = D_800EF07C = 0;
    D_800EF080 = D_800EF084 = D_800EF088 = D_800EF08C = 0;
}
