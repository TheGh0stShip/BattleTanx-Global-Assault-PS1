extern void func_800A30B4(int);
extern int D_800EF200;
extern int D_800EF1F8;
extern int D_800EF214;
extern int D_800EF208;
extern int D_800EF20C;
extern short D_800EF224;
extern int D_800EF210;
extern int D_800EF1FC;

void func_8009CE4C(int flag, int a1, int a2, int a3, int a4) {
    func_800A30B4(1);
    D_800EF200 = 0;
    D_800EF1F8 = a3;
    D_800EF214 = flag & 1;
    D_800EF208 = 0;
    D_800EF20C = 0;
    D_800EF224 = 0;
    D_800EF210 = 0;
    D_800EF1FC = a4;
    __asm__ volatile("");
}
