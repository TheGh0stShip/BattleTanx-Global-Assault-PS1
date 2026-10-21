typedef struct {
    int state;
    volatile int result;
    int f8;
    int chan;
} CardState;

extern CardState D_800EF094;
extern int D_800EF044;
extern int D_800EF048;
extern int D_800EF04C;
extern int func_80094E80(int *state);
extern void func_8009F5AC(int (*)(int *));
extern void func_80096AF0(void);
extern int func_8009F6BC(int);
extern int func_80096DE4(void);
extern void func_80096CD0(void);
extern int func_8009F6FC(int);
extern int func_80096DA8(void);
extern int func_80096BF8(void);
extern int func_8009663C(int);

int func_800950D4(int *state)
{
    int r;
    int st;
    int res;

    switch (*state) {
    case 0:
        D_800EF04C = 0;
        D_800EF048 = 0;
        D_800EF044 = 0;
        func_8009F5AC(func_80094E80);
        *state = 10;
        break;
    case 10:
        st = D_800EF094.result;
        if (st != 0) {
            if (st != 3) {
                return 1;
            }
            D_800EF04C = 1;
            func_80096AF0();
            func_8009F6BC(D_800EF094.chan);
            *state = 21;
        } else {
            *state = 30;
        }
        break;
    case 21:
        if (func_80096DE4() == 0) {
            return 0;
        }
        func_80096CD0();
        *state = 30;
    case 30:
        func_80096AF0();
        func_8009F6FC(D_800EF094.chan);
        (*state)++;
        break;
    case 31:
        if (func_80096DA8() == 0) {
            return 0;
        }
        r = func_80096BF8();
        D_800EF048 = r;
        switch (r) {
        case 0:
            __asm__("" : "=r"(r) : "0"(r));
            r = 0;
            if (D_800EF04C != 0) {
                r = 3;
            }
        case 4:
            {
                CardState *q = &D_800EF094;

                __asm__("" : "=r"(q) : "0"(q));
                q->result = r;
            }
            return 1;
        case 1:
            if (++D_800EF044 < 16) {
                *state = 0;
                break;
            }
        default:
            res = func_8009663C(D_800EF048);
            {
                CardState *q = &D_800EF094;

                __asm__("" : "=r"(q) : "0"(q));
                q->result = res;
            }
            return 1;
        }
        break;
    }
    return 0;
}
