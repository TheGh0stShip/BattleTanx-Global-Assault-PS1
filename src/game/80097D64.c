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

void func_80097E00(void) {
    func_8008AA48(&D_800EF0EC, 0, 40);
}

int func_80097E2C(int (*alloc)(), int arg) {
    int ok = 0;
    int own = 1;
    char *end;
    int temp = 0;
    char *mem = (char *)ok;
    register Dir80097D64 *d asm("$20") = &D_800EF0EC;
    unsigned int used;
    char *buf = d->buf;

    if (D_800EF0EC.root == 0) {
        {
            unsigned int size = alloc(3, arg);
            mem = (char *)alloc(ok, arg, size);
            used = size;
        }
        D_800EF0EC.root = mem;
        if (mem != 0) {
            d->end = mem + used;
            if (buf == 0) {
                buf = mem + 4096;
                own = ok;
            }
        }
    } else if (buf == 0) {
        buf = (char *)alloc(0, arg, 8192);
        if (buf != 0) {
            temp = 1;
        }
    }
    used = 0;
    d = &D_800EF0EC;
    d->cur = D_800EF0EC.root;
    if (D_800EF0EC.root != 0) {
        if (buf != 0 && func_80097D64(buf, own) != 0) {
            used = d->cur - D_800EF0EC.root;
        }
        d = &D_800EF0EC;
        if (used < d->min) {
            used = (d->min + 3) & ~3;
        }
        end = D_800EF0EC.root + used;
        if (mem != 0) {
            alloc(1, arg, mem, used);
            ok = used;
            d->end = end;
            if (ok == 0) {
                D_800EF0EC.root = 0;
                d->cur = 0;
                d->end = 0;
            }
        }
    }
    if (temp) {
        alloc(2, arg, buf);
    }
    D_800EF0FC = 0;
    return ok;
}
