extern int func_80097720(void *, int, int);
extern void func_8008A7BC(void *, void *, int);
extern void func_800977E0(void *);
extern int func_80097AA0(void *, int);
extern void func_8008AA48(void *, int, int);

typedef struct {
    char *root;
    char *cur;
    char *end;
    unsigned int min;
    char *buf;
} Dir80097D64;
extern Dir80097D64 D_800EF0EC;
extern char D_800EF100[];
extern int D_800EF0FC;

int func_80097D64(char *buf, int arg) {
    int r = func_80097720(buf, 16, 1);

    if (r != 0) {
        func_8008A7BC(D_800EF100, buf + 813, 17);
        func_800977E0(buf + 156);
        r = func_80097AA0(buf, arg);
        if (r == 0) {
            func_8008AA48(D_800EF100, 0, 17);
        }
    }
    return r;
}
