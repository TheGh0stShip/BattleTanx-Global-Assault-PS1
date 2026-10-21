typedef unsigned char u_char;

extern char *CD_comstr[];
extern char *CD_intstr[];
extern u_char CD_com;
extern volatile u_char CD_status[3];
extern volatile u_char *CD_reg0;
extern void (*CD_cbready)(int, u_char *);
extern void (*CD_cbsync)(int, u_char *);
extern int CD_timeout_limit;
extern int CD_timeout_count;
extern char *CD_timeout_name;
extern u_char CD_ready_result[8];
extern u_char CD_sync_result[8];
extern u_char CD_data_result[8];
extern char D_800C5F14[], D_800C5E84[], D_800C5E94[];

int printf(const char *, ...);
int puts(const char *);
int VSync(int);
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

int func_800A01B0(int mode, u_char *result)
{
    int c;
    int m;
    u_char *res;

    m = mode;
    res = result;
    CD_timeout_limit = VSync(-1) + 960;
    CD_timeout_count = 0;
    CD_timeout_name = D_800C5F14;
    do {
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
        if ((c = CD_status[2]) != 0) {
            volatile u_char *p = CD_status;

            p[2] = 0;
            CD_memcpy(res, CD_data_result, 8);
            return c;
        }
        if ((c = CD_status[1]) != 0) {
            volatile u_char *p = CD_status;

            p[1] = 0;
            CD_memcpy(res, CD_ready_result, 8);
            return c;
        }
    } while (m == 0);
    return 0;
}
