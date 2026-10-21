typedef struct IntrEnv {
    unsigned short enabled;
    short pad;
    void (*handler[11])(void);
    unsigned short mask;
} IntrEnv;

extern IntrEnv D_800B5A78;
extern volatile unsigned short *D_800B6B08;
extern void func_80096FFC(int on);
extern void func_8009700C(int ch, int on);

void (*func_800947B4(int irq, void (*fn)(void)))(void) {
    void (**tbl)(void) = D_800B5A78.handler;
    void (*old)(void) = tbl[irq];
    int m;

    if (fn != old && D_800B5A78.enabled) {
        m = *D_800B6B08;
        *D_800B6B08 = 0;
        if (fn != 0) {
            tbl[irq] = fn;
            m |= 1 << irq;
            D_800B5A78.mask |= 1 << irq;
        } else {
            tbl[irq] = 0;
            m &= ~(1 << irq);
            D_800B5A78.mask &= ~(1 << irq);
        }
        do {
        if (irq == 0) {
            func_80096FFC(fn == 0);
            func_8009700C(3, fn == 0);
        }
        if (irq == 4) {
            func_8009700C(0, fn == 0);
        }
        if (irq == 5) {
            func_8009700C(1, fn == 0);
        }
        if (irq == 6) {
            func_8009700C(2, fn == 0);
        }
        } while (0);
        *D_800B6B08 = m;
    }
    return old;
}
