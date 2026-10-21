typedef void (*CdlCB)(unsigned char, unsigned char *);

extern CdlCB D_800B8D24;
extern unsigned char D_800B8D34;
extern int D_800B6C94[];
extern int func_800A0478(unsigned char com, unsigned char *param, unsigned char *result, int arg3);
extern int func_8009FF30(int mode, unsigned char *result);

static inline char CdStatus(void)
{
    return D_800B8D34;
}

static inline int cd_cw(unsigned char com, unsigned char *param, unsigned char *result, int arg3)
{
    CdlCB old = D_800B8D24;
    int count = 3;
    int stop;
    int nop;

    do {
        nop = 1;
        D_800B8D24 = 0;
        if (com != nop && (CdStatus() & 0x10)) {
            func_800A0478(1, 0, 0, 0);
        }
        if (param == 0 || D_800B6C94[com] == 0 || !func_800A0478(2, param, result, 0)) {
            D_800B8D24 = old;
            if (!func_800A0478(com, param, result, arg3)) {
                return 0;
            }
        }
        stop = -1;
    } while (--count != stop);

    D_800B8D24 = old;
    return -1;
}

int func_800973AC(unsigned char com, unsigned char *param, unsigned char *result)
{
    if (cd_cw(com, param, result, 0) != 0) {
        return 0;
    }
    return func_8009FF30(0, result) == 2;
}
