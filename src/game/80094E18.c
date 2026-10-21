typedef struct {
    int state;
    int result;
    int w8;
    int chan;
} CardCtx80094E18;

extern CardCtx80094E18 D_800EF094;
extern char D_800C5218[];
extern void func_800943B0(char *, ...);
extern void func_8009F5AC(void *);

extern int func_80094E80(int *state);

int func_80094E18(int chan) {
    CardCtx80094E18 *c;

    __asm__("" : "=r"(c) : "0"(&D_800EF094));

    if (c->state != 0) {
        func_800943B0(D_800C5218);
        return 0;
    }
    c->state = 1;
    c->result = 0;
    c->w8 = 0;
    c->chan = chan;
    func_8009F5AC(func_80094E80);
    return 1;
}
