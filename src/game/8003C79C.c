extern int D_800DE050;
extern int D_800DE05C;
extern int D_800DE060;
extern int D_800DE064;
extern void *D_800A48D8;
extern void *D_800A48D4;
extern void *D_800DDDEC;
extern char D_800BEB08[];
extern char D_800BEB18[];
extern char D_800BEAC0[];
extern char D_800BEAD0[];
extern char D_800BEAE4[];
extern char D_800BEAF4[];
extern int D_800E48CC;
extern int D_800E48D4;
extern int D_800E48E4;
extern void *func_80068F34(int);
extern void func_8008D318(void *, void *, int, int, int, int, int);
extern void func_8003E030(void);
extern void func_8003CEDC(char *, int *);
extern void func_800579A0(int, char *, int *);
extern void func_8003C490(void);
extern void func_8007F708(void *, int);
extern void func_8007F740(int);

void func_8003C79C(void)
{
    D_800DE060 = 0;
    D_800DE05C = 0;
    D_800DE050 = 0;
    D_800DE064 = 0;
    D_800A48D8 = func_80068F34(0x8000);
    D_800A48D4 = func_80068F34(136);
    func_8008D318(D_800A48D4, D_800A48D8, 2048, 0, 0, 1024, 256);
    func_8003E030();
    func_8003CEDC(D_800BEB08, &D_800E48CC);
    func_800579A0(2, D_800BEB18, &D_800E48CC);
    func_8003CEDC(D_800BEAC0, &D_800E48D4);
    func_800579A0(0, D_800BEAD0, &D_800E48D4);
    func_8003CEDC(D_800BEAE4, &D_800E48E4);
    func_800579A0(3, D_800BEAF4, &D_800E48E4);
    func_8003C490();
    D_800DDDEC = func_80068F34(32000);
    func_8007F708(D_800DDDEC, 32000);
    func_8007F740(2);
}
