typedef struct FileCtl {
    int handle;
    char pad4[260];
    int mode;
    volatile int active;
    void (*callback)(int, int);
    void (*volatile callback4)(int, char *, unsigned int, int);
    int pad118;
    char *volatile buf;
    unsigned int total;
    unsigned int done;
    int busy;
    unsigned int pos;
    int count;
} FileCtl;

extern FileCtl D_800EC200;
extern int D_80086058;
extern int func_8007EB1C(int, char *, unsigned int);

void func_8007EF64(void) {
    FileCtl *ctl = &D_800EC200;
    void (*cb)(int, int);
    void (*cb4)(int, char *, unsigned int, int);
    char *buf;
    unsigned int n;
    int active;
    void (*fail)(int, char *, unsigned int, int);

    if (ctl->mode == 0) {
        ctl->mode = 2;
    }
    if (D_80086058 == 0 || ctl->mode != 2 || ctl->active == 0) {
        return;
    }
    buf = ctl->buf;
    if (buf == 0) {
        cb = ctl->callback;
        ctl->callback = 0;
        ctl->busy = 0;
        ctl->active = 0;
        if (cb != 0) {
            cb(D_800EC200.handle, 1);
        }
        return;
    }
    if (ctl->total > ctl->done) {
        n = ctl->total - ctl->done;
        if (n > 5120) {
            n = 5120;
        }
        D_800EC200.count = 0;
        if (func_8007EB1C(ctl->active, buf + ctl->done, n)) {
            ctl->done += n;
            return;
        }
        fail = ctl->callback4;
        buf = ctl->buf;
        ctl->callback4 = 0;
        ctl->buf = 0;
        ctl->busy = 0;
        ctl->active = 0;
        if (fail != 0) {
            fail(D_800EC200.handle, buf, 0, 0);
        }
        return;
    }
    cb4 = ctl->callback4;
    active = ctl->active;
    ctl->callback4 = 0;
    ctl->buf = 0;
    ctl->active = 0;
    ctl->busy = active;
    ctl->pos += ctl->total;
    if (cb4 != 0) {
        cb4(D_800EC200.handle, buf, ctl->total, 1);
    }
}
