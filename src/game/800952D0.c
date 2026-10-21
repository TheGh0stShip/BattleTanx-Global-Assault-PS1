typedef struct {
    int state;
    int result;
    int f8;
    int chan;
    int fd;
    int f14;
    int f18;
    int f1C;
    char name[32];
} CardState;

extern CardState D_800EF094;
extern int D_800EF0A0;
extern int D_800EF0E8;
extern char D_800C52C0[];
extern char D_800C5218[];
extern int func_800943B0(char *);
extern void func_80096714(int, char *);
extern char *func_8008D954(char *, char *);
extern int func_8009F70C(char *, int);
extern int func_80096008(int);
extern int func_8009601C(int, int *, int *);
extern void func_8009F5AC(int (*)(int *));
extern int func_800950D4(int *);

static inline int card_start_format(CardState *p, char *name, int chan)
{
    CardState *q = (CardState *)(name - 32);
    if (q->state != 0) {
        func_800943B0(D_800C5218);
        return 0;
    }
    q->state = 2;
    p->result = 0;
    p->f8 = 0;
    D_800EF0A0 = chan;
    func_8009F5AC(func_800950D4);
    return 0;
}

int func_800952D0(int chan, char *path, int mode_arg)
{
    int mode = mode_arg;
    CardState *cs;
    char *nm;
    int result;
    int retry = 0;
    int fd;
    int busy;
    int unformatted;
    int unknown;

    if (D_800EF094.fd >= 0) {
        func_800943B0(D_800C52C0);
        return -1;
    }
    nm = D_800EF094.name;
    func_80096714(chan, nm);
    __asm__("" : : "r"(chan), "r"(chan));
    func_8008D954(nm, path);
    D_800EF094.chan = chan;
    __asm__("" : : "r"(nm));
    cs = &D_800EF094;
    for (;;) {
        busy = 2;
        unformatted = 3;
        unknown = 5;
        fd = func_8009F70C(nm, mode | 0x8000);
        ((CardState *)(nm - 32))->fd = fd;
        if (fd >= 0) {
            goto opened;
        }
        D_800EF0E8 = func_80096008(0);
        func_8009601C(card_start_format(cs, nm, chan), 0, &result);
        func_80096008(D_800EF0E8);
        if (result == unformatted) {
            continue;
        }
        if (result == busy) {
            __asm__ volatile("");
            if (++retry < 16) continue;
        }
        if (result == 0) {
            result = unknown;
        }
        break;
    }
    return result;
opened:
    return 0;
}
