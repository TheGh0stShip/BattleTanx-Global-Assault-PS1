typedef unsigned char u_char;

extern volatile u_char CD_status[];
extern u_char CD_mode;
extern u_char CD_com;
extern volatile u_char *CD_reg0;
extern volatile u_char *CD_reg2;
extern volatile u_char *CD_reg3;
extern volatile int *CD_comdelay;
extern void (*CD_cbready)(int, u_char *);
extern void (*CD_cbsync)(int, u_char *);
extern int D_800B8D38;
extern int D_800B8D34;
extern char D_800C5F74[]; extern char D_800C5F80[]; extern u_char D_800B9008[];

int printf(const char *, ...);
int puts(const char *);
int ResetCallback(void);
void *InterruptCallback(int, void (*)(void));
void CD_intr(void);
int CD_sync(int, u_char *);
int func_800A0478(u_char com, u_char *param, u_char *result, int async);

int func_800A0B1C(void)
{
        register int zero asm("$0");

    puts(D_800C5F74);
    printf(D_800C5F80, D_800B9008);
    CD_com = 0;
    CD_mode = 0;
    CD_cbready = 0;
    CD_cbsync = 0;
    D_800B8D38 = 0;
    D_800B8D34 = 0;
    ResetCallback();
    InterruptCallback(2, CD_intr);
    *CD_reg0 = 1;
    while (*CD_reg3 & 7) {
        *CD_reg0 = 1;
        *CD_reg3 = 7;
        *CD_reg2 = 7;
    }
    {
        volatile u_char *status = CD_status;

        status[1] = status[2] = 0;
        status[0] = 2;     }
    *CD_reg0 = 0;
    *CD_reg3 = 0;
    *CD_comdelay = 0x1325;
    func_800A0478(1, (u_char *)zero, (u_char *)zero, zero);     if (D_800B8D34 & 0x10) {
        func_800A0478(1, (u_char *)zero, (u_char *)zero, zero);
    }
    if (func_800A0478(10, (u_char *)zero, (u_char *)zero, zero)) {         return -1;
    }
    if (func_800A0478(12, (u_char *)zero, (u_char *)zero, zero)) {         return -1;
    }
    if (CD_sync(zero, (u_char *)zero) != 2) {
        return -1;
    }
    return 0;
}
