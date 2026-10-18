typedef struct FileCtl {
    int handle;
    char pad4[260];
    int mode;
    int active;
    void (*callback)(int, int);
    void (*callback4)(int, int, int, int);
    int pad118;
    int arg;
    char pad120[8];
    int busy;
} FileCtl;

extern FileCtl D_800EC200;
extern int func_800942B4(int, int, int);
extern void func_8007EC2C(void);

int func_8007ECA0(int handle, int offset, int whence, void (*done)(int, int)) {
    FileCtl *ctl = &D_800EC200;

    if (ctl->busy == handle) {
        ctl->busy = 0;
    }
    if (ctl->mode != 2) {
        func_800942B4(handle - 1, offset, whence);
        if (done != 0) {
            done(D_800EC200.handle, 1);
        }
    } else {
        func_8007EC2C();
        func_800942B4(handle - 1, offset, whence);
        ctl->arg = 0;
        ctl->callback = done;
        ctl->active = handle;
    }
    return 1;
}
