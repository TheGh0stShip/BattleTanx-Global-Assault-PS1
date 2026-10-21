typedef struct LoadCtx {
    int unk0;
    volatile int status;
    int unk8;
    int unkC;
    int fd;
    int size;
    int addr;
    int len;
    char name[32];
} LoadCtx;

extern LoadCtx D_800EF094;
extern int D_800B6C28;
extern void func_80094E80(void);
extern void func_8009F5AC(void (*cb)(void));
extern int func_8009F70C(char *name, int mode);
extern int func_8009F72C(int fd, int offset, int whence);
extern int func_8009F73C(int fd, int addr, int len);
extern int func_8009F71C(int fd);
extern void func_80096AF0(void);
extern int func_80096DA8(void);
extern int func_80096BF8(void);
extern int func_8009663C(void);

int func_80095978(int *state) {
    int fd;

    switch (*state) {
    case 0:
        D_800B6C28 = 0;
        func_8009F5AC(func_80094E80);
        *state = 10;
        break;
    case 10:
        if (D_800EF094.status != 0) {
            return 1;
        }
        fd = func_8009F70C(D_800EF094.name, 0x8001);
        D_800EF094.fd = fd;
        if (fd < 0) {
            LoadCtx *p = &D_800EF094;

            p->status = 5;
            return 1;
        }
    case 11:
        while (func_8009F72C(D_800EF094.fd, D_800EF094.size, 0) != D_800EF094.size) {
        }
        *state = 20;
        break;
    case 20:
        func_80096AF0();
        while (func_8009F73C(D_800EF094.fd, D_800EF094.len, D_800EF094.addr) != 0) {
        }
        *state = 30;
        break;
    case 30:
        if (func_80096DA8() == 0) {
            return 0;
        }
        {
            register int r asm("$4") = func_80096BF8();

            __asm__("" : "=r"(r) : "0"(r));

            if (r == 1) {
                if (++D_800B6C28 < 16) {
                    *state = 11;
                    break;
                }
            }
        }
        {
            int r = func_8009663C();
            LoadCtx *p = &D_800EF094;

            p->status = r;
            func_8009F71C(p->fd);
            p->fd = -1;
        }
        return 1;
    }
    return 0;
}
