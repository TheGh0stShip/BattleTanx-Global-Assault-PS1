typedef struct IntrEnv {
    unsigned short enabled;
    unsigned short in_intr;
    void (*handler[11])(void);
    unsigned short mask;
} IntrEnv;

extern IntrEnv D_800B5A78;
extern volatile unsigned short *D_800B6B04;
extern volatile unsigned short *D_800B6B08;
extern int D_800B6B10;
extern char D_800C51BC[];
extern char D_800C51D8[];
extern int func_800943B0(char *fmt, ...);
extern void func_8009DA58(void);

void func_800945E4(void) {
    IntrEnv *env = &D_800B5A78;
    unsigned short st;
    int i;
    int bit;
    void (**tbl)(void);

    __asm__("" : "=r"(env) : "0"(env));
    if (env->enabled == 0) {
        func_800943B0(D_800C51BC, *D_800B6B04);
        func_8009DA58();
    }
    env->in_intr = 1;
    if ((st = (env->mask & *D_800B6B04) & *D_800B6B08) != 0) {
        bit = 1;
        tbl = env->handler;
        do {
            for (i = 0; st != 0 && i < 11; i++, st >>= 1) {
                if (st & 1) {
                    *D_800B6B04 = ~(bit << i);
                    if (tbl[i] != 0) {
                        tbl[i]();
                    }
                }
            }
        } while ((st = (D_800B5A78.mask & *D_800B6B04) & *D_800B6B08) != 0);
    }
    {
        register unsigned short stat asm("$2") = *D_800B6B04;
        register unsigned short mask asm("$3") = *D_800B6B08;

        if (stat & mask) {
            int *cnt = &D_800B6B10;
            int v = *cnt;
            int old = v;

            v++;
            *cnt = v;
            if (old > 2048) {
                func_800943B0(D_800C51D8, *D_800B6B04, *D_800B6B08);
                D_800B6B10 = 0;
                *D_800B6B04 = 0;
            }
        } else {
            D_800B6B10 = 0;
        }
    }
    D_800B5A78.in_intr = 0;
    func_8009DA58();
}
