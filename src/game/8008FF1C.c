extern int func_8008FE78(char *, int *);
extern int func_8008FC80(int, char *, unsigned int, void *);
extern int func_8008FBBC(int, unsigned char *, unsigned int);
extern void func_8008F4B4(int);

typedef struct {
    int handle;
    volatile int flags;
    char pad8[8];
    int count;
    char pad20[24];
    volatile int direct;
    char pad48[12];
    int dpos;
} S8008FF1C;
extern S8008FF1C D_800EEDF4;

int func_8008FF1C(unsigned int cmd, ...) {
    int r = 0;
    char *ap = (char *)&cmd + 4;

    switch (cmd) {
    case 0:
        r = 0;
        D_800EEDF4.handle = *(int *)ap;
        break;
    case 1: {
        int a;
        int b;
        int *z;

        ap += 4;
        a = ((int *)ap)[-1];
        ap += 4;
        b = ((int *)ap)[-1];
        z = *(int **)ap;
        r = func_8008FE78((char *)a, (int *)b);
        if (z != 0) {
            *z = 0;
        }
        break;
    }
    case 2: {
        register int m asm("$3") = 3;

        if (D_800EEDF4.direct != 0) {
            m = 11;
        }
        r = m;
        break;
    }
    case 5:
    case 6: {
        int *q = ((int **)ap)[3];

        r = ++D_800EEDF4.count;
        if (q != 0) {
            *q = 0;
        }
        break;
    }
    case 7:
        r = 1;
        break;
    case 10: {
        int a;
        int b;
        int c;
        void *d;

        ap += 4;
        a = ((int *)ap)[-1];
        ap += 8;
        b = ((int *)ap)[-1];
        ap += 4;
        c = ((int *)ap)[-1];
        ap += 4;
        d = ((void **)ap)[-1];
        r = func_8008FC80(a, (char *)b, c, d);
        break;
    }
    case 11: {
        int a;
        int b;
        int c;
        void (*cb)(int, int, int, int);

        ap += 4;
        a = ((int *)ap)[-1];
        ap += 8;
        b = ((int *)ap)[-1];
        ap += 4;
        c = ((int *)ap)[-1];
        cb = *(void (**)(int, int, int, int))ap;
        r = func_8008FBBC(a, (unsigned char *)b, c);
        if (cb != 0) {
            if (r == 0) {
                c = 0;
            }
            cb(D_800EEDF4.handle, b, c, r);
            return r;
        }
        break;
    }
    case 12: {
        int a;
        int b;

        ap += 4;
        a = ((int *)ap)[-1];
        b = *(int *)ap;
        r = 1;
        if (D_800EEDF4.direct == a) {
            if (b != 0) {
                while (D_800EEDF4.direct != 0) {
                }
            }
            r = D_800EEDF4.direct == 0;
        }
        break;
    }
    case 13: {
        int a = *(int *)ap;

        if (D_800EEDF4.direct == a && a != 0) {
            D_800EEDF4.flags |= 4;
            func_8008F4B4(0);
        }
        return r;
    }
    case 3:
    case 4:
    case 8:
    case 9:
    case 14:
    case 15:
        r = 0;
        break;
    case 16: {
        int a = *(int *)ap;

        r = 0;
        if (D_800EEDF4.direct == a && a != 0) {
            r = D_800EEDF4.dpos;
        }
        break;
    }
    }
    return r;
}
