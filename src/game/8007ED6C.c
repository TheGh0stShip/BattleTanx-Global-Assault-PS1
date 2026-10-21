typedef struct FileCtl {
    int handle;
    char pad4[260];
    int mode;
    volatile int active;
    void (*callback)(int, int);
    void (*callback4)(int, char *, unsigned int, int);
    int pad118;
    char *buf;
    unsigned int total;
    unsigned int done;
    int busy;
    unsigned int pos;
    unsigned int count;
} FileCtl;

extern FileCtl D_800EC200;
extern int func_8007F450(int, char *, unsigned int);
extern int func_8007EB1C(int, char *, unsigned int);
extern void func_8007EC2C(void);

int func_8007ED6C(int handle, char *buf, unsigned int len, void (*done)(int, char *, unsigned int, int)) {
    register FileCtl *ctl asm("$16") = &D_800EC200;
    register unsigned int n asm("$16");
    register int ok asm("$18");

    if (ctl->mode != 2) {
        ok = func_8007F450(handle, buf, len);
        if (done != 0) {
            if (ok == 0) {
                __asm__ volatile("" : "=r"(ok) : "0"(ok));
                len = 0;
            }
            done(D_800EC200.handle, buf, len, ok);
        }
    } else if (ctl->active == 0 && ctl->busy == handle && (ctl->pos >> 11) == ((ctl->pos + len) >> 11)) {
        ctl->count = 0;
        ok = func_8007EB1C(handle, buf, len);
        if (ok) {
            ctl->pos += len;
        } else {
            __asm__ volatile("" : "=r"(ok) : "0"(ok));
            ctl->busy = 0;
        }
        if (done != 0) {
            done(D_800EC200.handle, buf, D_800EC200.count, ok);
        }
    } else {
        func_8007EC2C();
        n = len;
        if (D_800EC200.busy != handle) {
            D_800EC200.pos = 0;
        }
        if (n > 5120) {
            n = 5120;
        }
        D_800EC200.count = 0;
        ok = func_8007EB1C(handle, buf, n);
        if (ok) {
            D_800EC200.buf = buf;
            D_800EC200.total = len;
            D_800EC200.done = n;
            D_800EC200.callback4 = done;
            D_800EC200.active = handle;
            goto out;
        }
        __asm__ volatile("" : "=r"(ok) : "0"(ok));
        if (done != 0) {
            done(D_800EC200.handle, buf, 0, 0);
        }
    }
out:
    return ok;
}
