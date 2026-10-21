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
extern char D_800C5368[];
extern char D_800C52C0[];
extern char D_800C5388[];
extern int func_800943B0(char *);
extern void func_8009F5AC(int (*)(int *));
extern void func_80096714(int, char *);
extern char *func_8008D954(char *, char *);
extern int func_80095978(int *state);

int func_80095874(int chan, char *path, int a2, int a3, int a4_arg)
{
    register int a4 __asm__("$22") = a4_arg;
    CardState *p;

    p = &D_800EF094;
    __asm__("" : "=r"(p) : "0"(p));
    if (p->state != 0) {
        func_800943B0(D_800C5368);
        return 0;
    }
    if (p->fd >= 0) {
        func_800943B0(D_800C52C0);
        return 0;
    }
    if ((a4 & 0x7F) != 0) {
        func_800943B0(D_800C5388);
        return 0;
    }
    func_80096714(chan, p->name);
    func_8008D954(p->name, path);
    p->state = 3;
    p->result = 0;
    p->f8 = 0;
    p->f14 = a3;
    p->f1C = a2;
    p->f18 = a4;
    p->chan = chan;
    func_8009F5AC(func_80095978);
    return 1;
}
