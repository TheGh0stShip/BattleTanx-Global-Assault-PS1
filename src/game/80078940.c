typedef struct PadState {
    unsigned char ready;
    unsigned char port;
} PadState;

extern unsigned int D_800EBC3C;
extern int D_800C60CC;
extern int D_800EBC38;
extern int D_800EBC40;
extern int D_800EBC44;
extern int D_800EBC48;
extern unsigned char D_800EBC4C;
extern unsigned char D_800AEB38;
extern PadState D_800EBBB4;
extern char D_800EBC54[];
extern char *D_800AE9A0;
extern char D_800C3E5C[];
extern char D_800C3E60[];
extern char D_800AEA4C[];
extern unsigned int func_80088324(int, int, ...);
extern char *func_8008DA04(char *, char *);
extern char *func_8008D954(char *, char *);
extern void func_80056E48(void *, int, int, int, int, int, int, int, int, void *);
extern void func_80078664(void);
extern void func_800770B8(void);
extern void func_80077D98(void);
extern void func_800773CC(void);
extern void func_80077660(void);
extern void func_80077830(void);
extern void func_80077260(void);
extern void func_800775A8(void);
extern unsigned char func_80078464(void);
extern void func_800876A8(int);

static inline unsigned char card_has_file(char *info) {
    if (func_80088324(14, D_800EBBB4.port, D_800EBC54, info) != 0) {
        return 1;
    }
    return 0;
}

static inline unsigned char card_has_space(void) {
    if (func_80088324(3, D_800EBBB4.port) < 7932) {
        return 0;
    }
    return 1;
}

unsigned char func_80078940(void) {
    unsigned char ok = 0;
    unsigned int status;
    PadState *pad;
    int x;
    int y;
    char text[128];

    if (D_800AEB38 == 0) {
        func_80078664();
        switch (D_800EBC3C) {
        case 0:
            D_800EBBB4.port = 0;
            D_800EBC38 = 0;
            D_800EBBB4.ready = 0;
            D_800EBC44 = 0;
            D_800EBC4C = 1;
            D_800EBC3C = 1;
            break;
        case 1:
            D_800EBC40 = 0;
            func_800770B8();
            break;
        case 2:
            func_80077D98();
            break;
        case 4:
            if (card_has_file(text)) {
                D_800EBC44 = 1;
                D_800EBC3C = 12;
            } else {
                D_800EBC40 = 2;
                D_800AEB38 = 5;
                D_800EBC44 = 0;
                D_800EBC3C = 10;
            }
            break;
        case 3:
            D_800EBC40 = 0;
            if (!(func_80088324(2, D_800EBBB4.port) & 3)) {
                D_800EBC3C = 2;
            }
            func_800773CC();
            break;
        case 5:
            D_800EBC40 = 0;
            func_80077660();
            break;
        case 6:
            D_800EBC40 = 0;
            status = func_80088324(2, D_800EBBB4.port);
            if (status & 1) {
                if (status & 2) {
                    D_800EBC3C = 2;
                } else {
                    func_80077830();
                }
            } else {
                D_800EBC3C = 2;
            }
            break;
        case 7:
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
            func_8008DA04(text, D_800AE9A0);
            if (pad->port == 0) {
                func_8008D954(text, D_800C3E5C);
            } else {
                func_8008D954(text, D_800C3E60);
            }
            func_80056E48(text, 3, y, 100, 4096, 4096, x, 0, -1, D_800AEA4C);
            break;
        case 12:
            if (!(func_80088324(2, D_800EBBB4.port) & 3)) {
                D_800EBC3C = 2;
            }
            func_80077260();
            break;
        case 8:
            ok = func_80078464();
            if (ok) {
                D_800EBC48 = 0;
                D_800EBC3C = 13;
            }
            break;
        case 13:
            D_800EBC40 = 0;
            func_800775A8();
            break;
        case 10:
            D_800EBC40 = 2;
            if (card_has_space()) {
                D_800EBBB4.ready = 1;
                D_800EBC3C = 8;
            } else {
                D_800EBBB4.ready = 0;
                D_800EBC3C = 7;
            }
            break;
        case 11:
            func_800876A8(D_800EBBB4.port);
            D_800EBC3C = 10;
            break;
        case 9:
        case 14:
            break;
        }
    }
    return ok;
}
