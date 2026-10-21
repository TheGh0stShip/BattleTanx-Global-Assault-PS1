typedef struct PadPort {
    unsigned char pad[0xF0];
} PadPort;

typedef struct {
    int w0;
    int (*handler)(void);
    int (*check)(void);
    int wC;
    int count0;
    int count1;
} PadHook;

typedef struct {
    int w0;
    int w4;
} PadRegs;

typedef struct {
    unsigned char pad0[0x0E];
    unsigned short h0E;
} PadSys;

extern PadHook D_800EFC38;
extern PadRegs *D_800B8CD4;
extern void (*D_800B8C9C)(void);
extern void (*D_800B8C74)(int);
extern int D_800B8CDC;
extern int D_800B8CC4;
extern int D_800B8CC8;
extern int D_800B8CAC;
extern int D_800B8CB4;
extern int D_800B8CB8;
extern int D_800B8CBC;
extern PadPort *D_800B8CA8;
extern PadSys *D_800B8CD8;
extern int func_8009E5F4(PadPort *p);
extern void func_8009E808(PadPort *p);
int func_8009E3BC(void);
int func_8009E354(void);

void func_8009E328(void)
{
    D_800EFC38.handler = func_8009E3BC;
    D_800EFC38.check = func_8009E354;
    D_800EFC38.w0 = 0;
    D_800EFC38.wC = 0;
}

int func_8009E354(void)
{
    if ((D_800B8CD4->w4 & 1) == 0) {
        return 0;
    }
    if ((D_800B8CD4->w0 & 1) == 0) {
        return 0;
    }
    if (D_800B8C9C) {
        D_800B8C9C();
    }
    return 1;
}

int func_8009E3BC(void)
{
    int n;

    D_800B8CDC = 1;
    if (D_800B8CC4 && D_800EFC38.count0 < 150) {
        D_800EFC38.count0++;
    }
    if (D_800B8CC8 == 0 && D_800EFC38.count1 < 150) {
        D_800EFC38.count1++;
    }
    if (D_800B8CAC) {
        n = D_800B8CC4;
        if (n <= D_800B8CC8) {
            D_800B8CB8 = 0;
            D_800B8CB4 = n;
            if (!func_8009E5F4(&D_800B8CA8[n])) {
                D_800B8C74(0xFFFF);
            }
            D_800B8CBC = 0;
            while (D_800B8CB4 <= D_800B8CC8) {
                func_8009E808(&D_800B8CA8[D_800B8CB4]);
            }
            D_800B8CD8->h0E = 0x88;
        }
    }
    return 0;
}
