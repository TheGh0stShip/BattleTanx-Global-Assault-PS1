typedef struct {
    int state;
    int result;
    int f8;
    int chan;
} CardState;

extern CardState D_800EF094;
extern char D_800C5218[];
extern int func_800943B0(char *);
extern void func_8009F5AC(int (*)(int *));
extern int func_800950D4(int *state);

int func_8009506C(int chan)
{
    CardState *p;

    p = &D_800EF094;
    __asm__("" : "=r"(p) : "0"(p));
    if (p->state != 0) {
        func_800943B0(D_800C5218);
        return 0;
    }
    p->state = 2;
    p->result = 0;
    p->f8 = 0;
    p->chan = chan;
    func_8009F5AC(func_800950D4);
    return 1;
}
