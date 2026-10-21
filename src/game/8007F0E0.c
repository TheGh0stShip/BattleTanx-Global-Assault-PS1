typedef struct FileCtl {
    int handle;
    char pad4[264];
    int active;
    char pad110[12];
    int buf;
    int total;
    int done;
    int busy;
} FileCtl;

extern volatile FileCtl D_800EC200;
extern int D_80086058;
extern int func_8007EA24(char *, int, int *);
extern int func_8007EAC8(int);
extern int func_800942D8(int);
extern int func_8007ECA0(int, int, int, void *);
extern int func_8007ED6C(int, char *, unsigned int, void *);
extern int func_8007F52C(int, char *, unsigned int);
extern void func_8007EC2C(void);

int func_8007F0E0(int op, ...) {
    char *ap;
    int ok = 0;

    if (D_80086058 == 0) {
        return ok;
    }
    ap = (char *)&op + 4;
    switch (op) {
    case 0: {
        int *out;

        D_800EC200.handle = *(int *)((ap += 4) - 4);
        out = *(int **)((ap += 4) - 4);
        ok = 1;
        if (out != 0) {
            *out = 0;
        }
        break;
    }
    case 1: {
        char *name = *(char **)((ap += 4) - 4);
        int *p1 = *(int **)((ap += 4) - 4);
        int *p2 = *(int **)((ap += 4) - 4);

        if (!(name[1] == ':' && name[0] >= 'a' && name[0] <= 'z')) {
            if (name[2] != ':' || name[0] != 'p' || name[1] != 'c') {
                return ok;
            }
        }
        if (p1 != 0) {
            *p1 = 0;
        }
        if (p2 != 0) {
            *p2 = name[1] == ':';
        }
        ok = 1;
        break;
    }
    case 2: {
        register int r asm("$3") = 3;

        if (D_800EC200.active) {
            r = 11;
        }
        ok = r;
        break;
    }
    case 3:
        ok = -1;
        break;
    case 4:
        ok = 1;
        break;
    case 5: {
        char *name;
        int mode;
        int *size;

        ap += 4;
        name = *(char **)((ap += 4) - 4);
        mode = *(int *)((ap += 4) - 4);
        size = *(int **)((ap += 4) - 4);
        ok = func_8007EA24(name, mode, size);
        break;
    }
    case 6: {
        int handle;
        int *out;

        ap += 4;
        handle = *(int *)((ap += 4) - 4);
        out = *(int **)((ap += 4) - 4);
        ok = func_8007EAC8(handle);
        if (out != 0) {
            *out = 0;
        }
        break;
    }
    case 7: {
        int handle = *(int *)((ap += 4) - 4);

        if (D_800EC200.busy == handle) {
            D_800EC200.busy = 0;
        }
        ok = func_800942D8(handle - 1) >= 0;
        break;
    }
    case 9: {
        int handle = *(int *)((ap += 4) - 4);
        int offset;
        int whence;
        void *done;

        ap += 4;
        offset = *(int *)((ap += 4) - 4);
        whence = *(int *)((ap += 4) - 4);
        done = *(void **)((ap += 4) - 4);
        ok = func_8007ECA0(handle, offset, whence, done);
        break;
    }
    case 10: {
        int handle = *(int *)((ap += 4) - 4);
        char *buf;
        unsigned int len;
        void *done;

        ap += 4;
        buf = *(char **)((ap += 4) - 4);
        len = *(unsigned int *)((ap += 4) - 4);
        done = *(void **)((ap += 4) - 4);
        ok = func_8007ED6C(handle, buf, len, done);
        break;
    }
    case 11: {
        int handle = *(int *)((ap += 4) - 4);
        char *buf;
        unsigned int len;
        void (*done)(int, char *, unsigned int, int);

        ap += 4;
        buf = *(char **)((ap += 4) - 4);
        len = *(unsigned int *)((ap += 4) - 4);
        done = *(void **)((ap += 4) - 4);
        ok = func_8007F52C(handle, buf, len);
        if (done != 0) {
            if (ok == 0) {
                len = 0;
            }
            done(D_800EC200.handle, buf, len, ok);
            return ok;
        }
        break;
    }
    case 12: {
        int handle = *(int *)((ap += 4) - 4);
        int wait = *(int *)((ap += 4) - 4);

        ok = 1;
        if (D_800EC200.active == handle) {
            if (wait != 0) {
                while (D_800EC200.active != 0) {
                }
            }
            ok = D_800EC200.active == 0;
        }
        break;
    }
    case 13: {
        int handle = *(int *)((ap += 4) - 4);

        if (D_800EC200.active == handle) {
            func_8007EC2C();
        }
        return ok;
    }
    case 8:
    case 14:
    case 15:
        ok = 0;
        break;
    case 16: {
        int handle = *(int *)((ap += 4) - 4);

        ok = 0;
        if (D_800EC200.active == handle) {
            if (D_800EC200.buf == 0) {
                return ok;
            }
            ok = D_800EC200.done;
        }
        break;
    }
    }
    return ok;
}
