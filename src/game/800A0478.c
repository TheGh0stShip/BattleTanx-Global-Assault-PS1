typedef unsigned char u_char;

extern int CD_debug;
extern char *CD_comstr[];
extern char *CD_intstr[];
extern int CD_comtbl[2][64];
extern u_char CD_pos[4];
extern u_char CD_mode;
extern u_char CD_com;
extern volatile u_char CD_status[3];
extern volatile u_char *CD_reg0;
extern volatile u_char *CD_reg1;
extern volatile u_char *CD_reg2;
extern void (*CD_cbready)(int, u_char *);
extern void (*CD_cbsync)(int, u_char *);
extern int CD_timeout_limit;
extern int CD_timeout_count;
extern char *CD_timeout_name;
extern u_char CD_ready_result[8];
extern u_char CD_sync_result[8];
extern char D_800C5F20[], D_800C5F28[], D_800C5F38[], D_800C5E84[], D_800C5E94[];

int printf(const char *, ...);
int puts(const char *);
int VSync(int);
int CD_sync(int, u_char *);
void CD_flush(void);
int CheckCallback(void);
int CD_getintr(void);

static inline void CD_memcpy(u_char *dst, u_char *src, int n)
{
    if (dst) {
        for (n--; n != -1; n--) {
            *dst++ = *src++;
        }
    }
}

static inline int CD_checktimeout(void)
{
    if (CD_timeout_limit < VSync(-1) || CD_timeout_count++ > 0x3C0000) {
        char **com = CD_comstr;
        char **intr = CD_intstr;
        puts(D_800C5E84);
        {
            int s = CD_status[0];
            char *r = intr[CD_status[1]];
            printf(D_800C5E94, CD_timeout_name, com[CD_com], intr[s], r);
        }
        CD_flush();
        return -1;
    }
    return 0;
}

int func_800A0478(u_char com, u_char *param, u_char *result, int async)
{
    u_char *p = param;
    int a = async;
    u_char c = com;
    int i;
    register int zero asm("$0");

    if (CD_debug >= 2) {
        printf(D_800C5F20, CD_comstr[c]);
    }
    if (CD_comtbl[1][c] && p == 0) {
        if (CD_debug > 0) {
            printf(D_800C5F28, CD_comstr[c]);
        }
        return -2;
    }
    CD_sync(zero, (u_char *)zero);
    if (c == 2) {
        for (i = 0; i < 4; i++) {
            CD_pos[i] = p[i];
        }
    }
    if (c == 14) {
        CD_mode = p[0];
    }
    {
        int (*tbl)[64] = CD_comtbl;
        int *cnt;

        CD_status[0] = 0;
        if (tbl[0][c]) {
            CD_status[1] = 0;
        }
        *CD_reg0 = 0;
        cnt = tbl[1];
        for (i = 0; i < cnt[c]; i++) {
            *CD_reg2 = p[i];
        }
    }
    CD_com = c;
    *CD_reg1 = c;
    if (a) {
        return 0;
    }
    CD_timeout_limit = VSync(-1) + 960;
    CD_timeout_count = 0;
    CD_timeout_name = D_800C5F38;
    while (CD_status[0] == 0) {
        if (CD_checktimeout() != 0) {
            return -1;
        }
        if (CheckCallback()) {
            int old = *CD_reg0 & 3;
            int ret;
            while ((ret = CD_getintr()) != 0) {
                if ((ret & 4) && CD_cbready) {
                    CD_cbready(CD_status[1], CD_ready_result);
                }
                if ((ret & 2) && CD_cbsync) {
                    CD_cbsync(CD_status[0], CD_sync_result);
                }
            }
            *CD_reg0 = old;
        }
    }
    CD_memcpy(result, CD_sync_result, 8);
    i = 0;
    if (CD_status[0] == 5) {
        i = -1;
    }
    return i;
}
