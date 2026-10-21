extern char D_800EBC54[];
extern int D_800EBC44;
extern int D_800EBC48;
extern int D_800EBC3C;
extern int D_800AEB30;
extern unsigned char D_800EBBB5;
extern char D_800AEA5C[];
extern void func_8008DA04(char *, char *);
extern void func_80086F8C(char *);
extern void func_80086EA8(int);
extern int func_80088324();
extern unsigned char func_80077B9C(unsigned char, char *, char *);

static inline unsigned char create_file(int port, char *path, char *data) {
    int fd;

    func_80086EA8(1);
    fd = func_80088324(6, port, path, 0);
    if (fd == 0) {
        D_800EBC48 = 2;
        D_800EBC3C = 13;
        return 0;
    }
    func_80088324(11, fd, 0, data, 100, 0);
    func_80088324(12, fd, 1);
    func_80088324(7, fd);
    return 1;
}

static inline int replace_file(int port, char *name, char *path, char *data) {
    unsigned char ok = 0;
    int found;

    func_80088324(8, port, name, &found);
    if (found != 0) {
        ok = create_file(port, path, data);
    } else {
        D_800EBC48 = 2;
        D_800EBC3C = 13;
    }
    return ok;
}

unsigned char func_80078464(void) {
    char path[128];
    unsigned char ok = 0;

    func_8008DA04(path, D_800EBC54);
    func_80086F8C(path);
    if (D_800EBC44 != 0) {
        if (D_800AEB30 == 3) {
            ok = func_80077B9C(D_800EBBB5, D_800EBC54, D_800AEA5C);
        } else if (D_800AEB30 == 4) {
            ok = replace_file(D_800EBBB5, D_800EBC54, path, D_800AEA5C);
        }
    } else {
        ok = create_file(D_800EBBB5, path, D_800AEA5C);
    }
    return ok;
}
