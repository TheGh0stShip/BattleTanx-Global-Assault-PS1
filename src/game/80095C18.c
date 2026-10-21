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
    int fd;
    int f14;
    int f18;
    int f1C;
    char name[32];
} CardState;

extern CardIo D_800EF0A4;
extern CardState D_800EF094;
extern int D_800B6C2C;
extern void func_8009F5AC(int (*)(int *));
extern int func_80094E80(int *state);
extern int func_8009F70C(char *, int);
extern int func_8009F71C(int);
extern int func_8009F72C(int, int, int);
extern int func_8009F74C(int, int, int);
extern void func_80096AF0(void);
extern int func_80096DA8(void);
extern int func_80096BF8(void);
extern int func_8009663C(int);

int func_80095C18(int *state)
{
    CardIo *io;
    CardState *cs;
    int r;

    switch (*state) {
    case 0:
        D_800B6C2C = 0;
        func_8009F5AC(func_80094E80);
        *state = 10;
        break;
    case 10:
        if (D_800EF094.result != 0) {
            return 1;
        }
        if ((D_800EF094.fd = func_8009F70C(D_800EF094.name, 0x8001)) < 0) {
            ((volatile CardState *)&D_800EF094)->result = 5;
            return 1;
        }
    case 11:
        io = &D_800EF0A4;
        while (func_8009F72C(io->chan, io->count, 0) != io->count) {
        }
        *state = 20;
        break;
    case 20:
        func_80096AF0();
        io = &D_800EF0A4;
        while (func_8009F74C(io->chan, io->argC, io->arg8) != 0) {
        }
        *state = 30;
        break;
    case 30:
        if (func_80096DA8() == 0) {
            return 0;
        }
        r = func_80096BF8();
        if (r == 1 && ++D_800B6C2C < 16) {
            *state = 11;
            break;
        }
        r = func_8009663C(r);
        cs = &D_800EF094;
        __asm__("" : "=r"(cs) : "0"(cs));
        cs->result = r;
        func_8009F71C(cs->fd);
        cs->fd = -1;
        return 1;
    }
    return 0;
}
