typedef struct PadRegs {
    int unk00;
    int unk04;
} PadRegs;

typedef struct PadPort {
    char pad0[0xF0];
} PadPort;

extern int D_800B8CAC;
extern int D_800EFC38;
extern int D_800EFC48[2];
extern PadRegs *D_800B8CD4;
extern PadPort *D_800B8CA8;
extern void (*D_800B8C78)(PadPort *p);

void func_80094198(void);
void func_80094168(void);
void func_800A3A04(int n, void *p);
void func_800A3A14(int n, void *p);
void func_8009700C(int a, int b);

void func_8009E528(void)
{
    volatile PadRegs *r;
    int *c;

    D_800B8CAC = 0;
    func_80094198();
    func_800A3A04(2, &D_800EFC38);
    func_800A3A14(2, &D_800EFC38);
    r = D_800B8CD4;
    r->unk00 = -2;
    r->unk04 |= 1;
    func_8009700C(3, 0);
    func_80094168();
    D_800B8C78(D_800B8CA8);
    D_800B8C78(D_800B8CA8 + 1);
    c = D_800EFC48;
    c[1] = 0;
    c[0] = 0;
    D_800B8CAC = 1;
    __asm__ volatile("");
}
