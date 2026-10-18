typedef struct PadState {
    unsigned char ready;
    unsigned char port;
} PadState;

extern unsigned int D_800EBC3C;
extern int D_800C60CC;
extern int D_800EBC40;
extern int D_800EBC48;
extern char D_800EBC50[];
extern unsigned char D_800AEB38;
extern PadState D_800EBBB4;
extern char D_800EBC54[];
extern char *D_800AE970;
extern char D_800AEAC0[];
extern char D_800C3E5C[];
extern char D_800C3E60[];
extern char D_800AEA4C[];
extern unsigned int func_80088324(int, int, ...);
extern int func_80088270(int, int);
extern char *func_8008DA04(char *, char *);
extern char *func_8008D954(char *, char *);
extern void func_80086F8C(char *);
extern void func_80086EA8(int);
extern void func_80056E48(void *, int, int, int, int, int, int, int, int, void *);
extern void func_80077E88(void);
extern void func_800770B8(void);
extern void func_800773CC(void);
extern void func_80077660(void);
extern void func_80077754(void);
extern void func_800775A8(void);

static inline unsigned char card_has_file(char *info) {
    if (func_80088324(14, D_800EBBB4.port, D_800EBC54, info) != 0) {
        return 1;
    }
    return 0;
}

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

unsigned char func_800780A4(void) {
    unsigned char ok = 0;
    unsigned int status;
    PadState *pad;
    int x;
    int y;
    char text[128];

    if (D_800AEB38 == 0) {
        func_80077E88();
        switch (D_800EBC3C) {
        case 0:
            D_800EBC3C = 1;
            break;
        case 1:
            D_800EBC40 = 0;
            func_800770B8();
            break;
        case 2:
            status = func_80088324(2, D_800EBBB4.port);
            if (!(status & 1)) {
                D_800EBC3C = 5;
                D_800EBBB4.ready = 0;
            } else if (!(status & 2)) {
                D_800EBC3C = 6;
                D_800EBBB4.ready = 0;
            } else {
                D_800EBC3C = 3;
                D_800EBBB4.ready = 1;
            }
            break;
        case 3:
            D_800EBC40 = 0;
            if (!(func_80088324(2, D_800EBBB4.port) & 3)) {
                D_800EBC3C = 2;
            }
            func_800773CC();
            break;
        case 4:
            if (card_has_file(text)) {
                D_800EBC3C = 8;
            } else {
                D_800EBC3C = 9;
            }
            break;
        case 9:
            pad = &D_800EBBB4;
            D_800EBC40 = 0;
            if (!(func_80088324(2, pad->port) & 3)) {
                D_800EBC3C = 2;
            }
            x = 190;
            y = 30;
            if (D_800C60CC == 1) {
                x = 304;
                y = 80;
            }
            func_8008DA04(text, D_800AE970);
            if (pad->port == 0) {
                func_8008D954(text, D_800C3E5C);
            } else {
                func_8008D954(text, D_800C3E60);
            }
            func_80056E48(text, 3, y, 100, 4096, 4096, x, 0, -1, D_800AEA4C);
            break;
        case 5:
            D_800EBC40 = 0;
            func_80077660();
            break;
        case 6:
            D_800EBC40 = 0;
            if (!(func_80088324(2, D_800EBBB4.port) & 3)) {
                D_800EBC3C = 2;
            }
            func_80077754();
            break;
        case 8:
            func_8008DA04(text, D_800EBC54);
            func_80086F8C(text);
            ok = write_icon_block(D_800EBBB4.port, text);
            if (ok) {
                D_800EBC3C = 14;
                D_800EBC40 = 0;
            }
            break;
        case 13:
            D_800EBC40 = 0;
            func_800775A8();
            break;
        case 14:
            D_800EBC40 = 0;
            break;
        case 7:
        case 10:
        case 11:
        case 12:
            break;
        }
    }
    return ok;
}
