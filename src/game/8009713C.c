typedef void (*CdlCB)(unsigned char, unsigned char *);

extern CdlCB D_800B8D24;
extern unsigned char D_800B8D34;
extern int D_800B6C94[];
extern int func_800A0478(unsigned char com, unsigned char *param, unsigned char *result, int arg3);

static inline int CdStatus(void)
{
    return D_800B8D34;
}

static inline int cd_cw(unsigned char com, unsigned char *param, unsigned char *result, int arg3)
{
    CdlCB old = D_800B8D24;
    int count = 3;
    int stop;
    int nop = 1;

    do {
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

int func_8009713C(unsigned char com, unsigned char *param, unsigned char *result)
{
    return cd_cw(com, param, result, 0) + 1;
}
