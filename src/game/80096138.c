typedef struct {
    int state;
    int busy;
    int done;
    int slot;
} Card80096138;

extern volatile Card80096138 D_800EF094;
extern int D_800EF090;
extern char *D_800EF0A0;
extern int D_800EF0E0;
extern int D_800EF0E8;
extern char D_800C5368[];
extern char D_800C5218[];
extern void func_800943B0(char *, ...);
extern void func_80096714(char *, char *);
extern void func_8008D954(char *, char *);
extern int func_8009F70C(char *, int);
extern void func_8009F71C(int);
extern int func_80096008(int);
extern void func_8009F5AC(void (*)(void));
extern void func_800950D4(void);

static inline void card_create_request(volatile Card80096138 *c, char *name)
{
    if (c->state != 0) {
        func_800943B0(D_800C5218);
    } else {
        c->state = 2;
        c->busy = 0;
        c->done = 0;
        D_800EF0A0 = name;
        func_8009F5AC(func_800950D4);
    }
}

static inline void card_create_wait(volatile Card80096138 *c, int *result)
{
    if (c->state != 0 || c->done != 0) {
        c->state;
        c->busy;
        if (c->done == 0) {
            while (D_800EF094.done == 0) {
            }
        }
        *result = *(volatile int *)&D_800EF0E0;
        c->done = 0;
    }
}

int func_80096138(char *name, char *suffix, int blocks)
{
    struct {
        char path[32];
        int result;
    } io;
    int retry = 0;
    int fd;
    volatile Card80096138 *c;
    int mode;

    if (D_800EF094.state != 0) {
        func_800943B0(D_800C5368);
        return -1;
    }
    __asm__("" : : "r"(name));
    func_80096714(name, io.path);
    func_8008D954(io.path, suffix);
    D_800EF090 |= 1 << D_800EF094.slot;
    fd = func_8009F70C(io.path, 1);
    if (fd >= 0) {
        func_8009F71C(fd);
        return 6;
    }
    mode = blocks << 16;
    if (0) {
fail:
        return 7;
    }
    for (;;) {
        c = &D_800EF094;
        fd = func_8009F70C(io.path, mode | 0x200);
        if (fd >= 0) {
            goto created;
        }
        D_800EF0E8 = func_80096008(0);
        card_create_request(c, name);
        card_create_wait(c, &io.result);
        func_80096008(D_800EF0E8);
        if (io.result == 0) {
            goto fail;
        }
        if (io.result == 3) {
            continue;
        }
        if (io.result != 2 || ++retry >= 16) {
            break;
        }
    }
    if (io.result == 0) {
        io.result = 5;
    }
    return io.result;
created:
    func_8009F71C(fd);
    return 0;
}
