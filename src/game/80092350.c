extern int func_8009B2A8(char *, int, int, int, ...);
extern void func_80091D4C(int, int, int, int, int, char *);
extern void func_8007F80C(int);
extern void func_8007F980(int);
extern void func_8008B894(void);
extern void func_8008AA48(void *, int, int);
extern void func_80094A48(int);

void func_80092350(int a0, int x, int y, int a3, int a4, char *fmt, ...) {
    char buf[32];
    int len;
    int x0;

    if (fmt != 0) {
        x0 = x;
        len = func_8009B2A8(buf, 32, 1, fmt, &fmt + 1);
        while (len != 0) {
            func_80091D4C(a0, x, y, a3, a4, buf);
            x = -1;
            if (buf[len - 1] == '\n') {
                x = x0;
            }
            y = -1;
            len = func_8009B2A8(buf, 32, 1, 0, 0);
        }
    }
}

typedef struct {
    int w0;
    int w4;
    int w8;
    int w12;
    char pad16[42];
    short h58;
} S80092450;
extern S80092450 D_800EEE70;

typedef struct {
    int w0;
    int mode;
} Cfg80092450;
extern Cfg80092450 D_80086058;

void func_80092450(void) {
    S80092450 *s;
    Cfg80092450 *c;
    int mode;

    func_8007F80C(0);
    func_8007F980(0);
    func_8008B894();
    s = &D_800EEE70;
    func_8008AA48(s, 0, 156);
    c = &D_80086058;
    mode = c->mode;
    if (mode == 50) {
        func_80094A48(1);
        mode = c->mode;
    }
    D_800EEE70.w0 = 0;
    s->w4 = 0;
    s->w8 = 0;
    s->w12 = 0;
    if (mode == 50) {
        s->h58 = 280;
    }
}
