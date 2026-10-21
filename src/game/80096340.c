typedef struct {
    volatile int state;
    volatile int f4;
    volatile int f8;
    volatile int chan;
} CardState;

extern CardState D_800EF094;
extern int D_800EF090;
extern volatile int D_800EF09C;
extern volatile int D_800EF0E0;
extern int D_800EF0E8;
extern char D_800C5368[];
extern char D_800C5218[];
extern void func_800950D4(void);
extern int func_800943B0(char *);
extern void func_80096714(int, char *);
extern void func_8008D954(char *, int);
extern int func_8009F77C(char *);
extern int func_80096008(int);
extern void func_8009F5AC(void (*)(void));

int func_80096340(int a0, int a1)
{
    struct { char buf[32]; int result; } s;
    register CardState *p asm("$19");
    CardState *q;
    register int i asm("$17");
    register int busy asm("$19");

    p = &D_800EF094;
    i = 0;
    if (p->state != 0) {
        func_800943B0(D_800C5368);
        return -1;
    }
    func_80096714(a0, s.buf);
    func_8008D954(s.buf, a1);
    q = p;
    __asm__("" : "=r"(q) : "0"(q));
    busy = 2;
    D_800EF090 |= 1 << q->chan;
retry:
        if ((s.result = func_8009F77C(s.buf)) != 0) {
            goto fail;
        }
        D_800EF0E8 = func_80096008(0);
        if (q->state != 0) {
            func_800943B0(D_800C5218);
        } else {
            q->state = busy;
            q->f4 = 0;
            q->f8 = 0;
            D_800EF094.chan = a0;
            func_8009F5AC(func_800950D4);
        }
        if (q->state != 0 || q->f8 != 0) {
            q->state;
            q->f4;
            if (q->f8 == 0) {
                while (*(volatile int *)&D_800EF09C == 0) {
                }
            }
            {
                int r;

                r = *(volatile int *)&D_800EF0E0;
                q->f8 = 0;
                s.result = r;
            }
        }
        func_80096008(D_800EF0E8);
        if (s.result == 3) {
            goto retry;
        }
        if (s.result == busy && ++i < 16) {
            goto retry;
        }
    if (s.result == 0) {
        s.result = 5;
    }
    return s.result;
fail:
    return 0;
}
