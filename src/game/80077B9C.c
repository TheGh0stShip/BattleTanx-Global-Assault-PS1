extern int D_800EBC3C;
extern int D_800EBC48;
extern char D_800EBC50[];
extern char D_800AEAC0[];
extern char D_800AEB18[];
extern char *func_8008DA04(char *, char *);
extern void func_80086F8C(char *);
extern void func_80086EA8(int);
extern int func_80088324(int, ...);
extern int func_80088270(int, int);

static inline unsigned char write_icon_block(int port, char *path) {
    char *header = D_800AEAC0;
    int fd;
    int result;

    func_80086EA8(1);
    fd = func_80088324(5, port, path, 2, D_800EBC50);
    if (fd == 0) {
        D_800EBC48 = 3;
        D_800EBC3C = 13;
        return 0;
    }
    func_80088324(10, fd, 0, header, 100, 0);
    func_80088324(12, fd, 1);
    result = func_80088270(port, fd);
    while (result != 1) {
    }
    func_80088324(7, fd);
    return 1;
}

static inline int write_save_block(int port, char *name, char *data, char *path) {
    int exists;
    int fd;
    int ok = 0;

    __asm__("" : "=r"(ok) : "0"(ok));
    func_80088324(8, port, name, &exists);
    if (exists != 0) {
        func_80086EA8(1);
        fd = func_80088324(6, port, path, 0);
        if (fd != 0) {
            func_80088324(11, fd, 0, data, 100, 0);
            func_80088324(12, fd, 1);
            func_80088324(7, fd);
            ok = 1;
            goto done;
        }
        ok = 0;
    }
    D_800EBC48 = 2;
    D_800EBC3C = 13;
done:
    return ok;
}

int func_80077B9C(int port, char *name, char *data) {
    char path[128];

    func_8008DA04(path, name);
    func_80086F8C(path);
    if (!write_icon_block(port, path)) {
        D_800EBC48 = 2;
        D_800EBC3C = 13;
        return 0;
    }
    func_8008DA04(data + 88, D_800AEB18);
    return write_save_block(port, name, data, path);
}
