extern int func_8009278C(void *, int);
extern void func_8009312C(void *, char *, char *, int, char *, char *, int, char *, int, int, int);

typedef struct {
    char pad0[48];
    int arg;
    char *buf;
    int w56;
    int w60;
    int w64;
    int w68;
    int w72;
} S8009304C;

void func_8009304C(S8009304C *p, char *buf, int arg, int a3, int a4) {
    int n = func_8009278C(p, 0);
    int m = func_8009278C(p, 1);

    func_8009312C(p, buf, buf + n, n, buf + n * 2, buf + (n * 2 + m), m, buf + (n + m) * 2, 0x11000, a3, a4);
    p->buf = buf;
    p->arg = arg;
    p->w56 = 0;
    p->w60 = 0;
    p->w64 = 0;
    p->w68 = 0;
    p->w72 = 0;
}
