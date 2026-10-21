typedef struct {
    int chan;
    int count;
    int arg8;
    int argC;
} CardIo;

typedef struct {
    int state;
    int result;
    int f8;
    int chan;
} CardState;

extern CardIo D_800EF0A4;
extern CardState D_800EF094;
extern int D_800B6C20;
extern int func_8009F72C(int, int, int);
extern int func_8009F73C(int, int, int);
extern void func_80096AF0(void);
extern int func_80096DA8(void);
extern int func_80096BF8(void);
extern int func_8009663C(int);

int func_80095538(int *state)
{
    CardIo *io;
    CardState *cs;
    int r;

    switch (*state) {
    case 0:
        D_800B6C20 = 0;
        *state = 10;
    case 10:
        io = &D_800EF0A4;
        while (func_8009F72C(io->chan, io->count, 0) != io->count) {
        }
        *state = 20;
        break;
    case 20:
        func_80096AF0();
        io = &D_800EF0A4;
        while (func_8009F73C(io->chan, io->argC, io->arg8) != 0) {
        }
        *state = 30;
        break;
    case 30:
        if (func_80096DA8() == 0) {
            return 0;
        }
        r = func_80096BF8();
        if (r == 1 && ++D_800B6C20 < 16) {
            *state = 10;
            break;
        }
        r = func_8009663C(r);
        cs = &D_800EF094;
        __asm__("" : "=r"(cs) : "0"(cs));
        cs->result = r;
        return 1;
    }
    return 0;
}
