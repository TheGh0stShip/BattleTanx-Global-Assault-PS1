typedef struct {
    int state;
    int result;
    int f8;
    int chan;
} CardState;

extern volatile int D_800EF090;
extern CardState D_800EF094;
extern int D_800EF03C;
extern int D_800EF040;
extern void func_80096AF0(void);
extern int func_8009F6AC(int);
extern int func_80096DA8(void);
extern int func_80096BF8(void);
extern int func_8009663C(int);

int func_80094E80(int *state)
{
    int r;
    int bit;
    int nbit;
    int v;
    int arg;
    volatile int *chan;
    volatile CardState *card;

    switch (*state) {
    case 0:
        D_800EF040 = 0;
        D_800EF03C = 0;
        func_80096AF0();
        *state = 10;
    case 10:
        func_8009F6AC(D_800EF094.chan);
        (*state)++;
        break;
    case 11:
        if (func_80096DA8() == 0) {
            return 0;
        }
        r = func_80096BF8();
        D_800EF040 = r;
        switch (r) {
        case 4:
            arg = D_800EF040;
            chan = &D_800EF094.chan;
            r = D_800EF090 | (1 << *chan);
            goto finish;
        case 0:
            chan = &D_800EF094.chan;
            bit = 1 << *chan;
            if ((D_800EF090 & bit) == 0) {
                D_800EF040 = 4;
                D_800EF090 |= bit;
            }
            v = func_8009663C(D_800EF040);
            {
                volatile CardState *c = (volatile CardState *)(chan - 3);
                c->result = v;
            }
            return 1;
        case 1:
            if (++D_800EF03C < 16) {
                *state = 10;
                break;
            }
        default:
            arg = D_800EF040;
            chan = &D_800EF094.chan;
            nbit = 1;
            nbit <<= *chan;
            r = D_800EF090 & ~nbit;
        finish:
            D_800EF090 = r;
            __asm__ volatile("");
            card = (volatile CardState *)(chan - 3);
            __asm__("" : "=r"(card) : "0"(card));
            card->result = func_8009663C(arg);
            return 1;
        }
        break;
    }
    return 0;
}
