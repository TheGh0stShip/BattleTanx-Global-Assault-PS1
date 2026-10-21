typedef int (*CallbackFn)(int op, int a, int b, int c, int d, int e);
typedef void (*AllocFn)(int op, void *ctx, ...);

typedef struct Buffer {
    int ok;
    char *data;
    unsigned int capacity;
    unsigned int used;
    void *alloc;
    void *ctx;
    unsigned int granule;
} Buffer;

typedef struct LinkState {
    volatile unsigned int flags;
    int user;
    AllocFn alloc;
    void *alloc_ctx;
    int unk10;
    void (*notify)(void);
    CallbackFn callback;
    Buffer buf;
    void *block;
    int block_size;
    int unk40;
    int pending;
    void *read_done;
    void *write_done;
    int write_result;
} LinkState;

typedef struct HostState {
    volatile unsigned int flags;
    void (*done)(int, int, int, int);
    void (*on_cmd15)(int, int);
    void (*on_cmd16)(int, int);
    char pad[0x19C - 0x10];
    char *name;
    char *dest;
    unsigned int dest_size;
    int pad2;
    int busy;
} HostState;

extern LinkState D_800EEBE0;
extern HostState D_800EEC34;

extern int func_80099BEC(Buffer *b, AllocFn alloc, void *ctx, unsigned int size, unsigned int granule);
extern void func_80099CA0(Buffer *b, int flag);
extern int func_80099CE8(Buffer *b, int a, int n);
extern void func_800996A4(int a);
extern void func_8008E008(int a, int b, int c, int d);
extern void func_8008AA48(void *p, int c, int n);
extern void func_8008A7BC(void *d, void *s, unsigned int n);
extern int func_80090184(char *s);
extern void func_8009940C(int a, int b, char *s, int n, void *fn);
extern void func_8008EA00(void);

int func_8008E09C(int cmd, ...) {
    int result = 0;
    char *ap = (char *)(&cmd + 1);

    switch ((unsigned int)cmd) {
    case 0: {
        int *out;
        ap += 4;
        D_800EEBE0.user = ((int *)ap)[-1];
        out = *(int **)ap;
        if (out != 0) {
            *out = 0;
        }
        result = 0;
        break;
    }
    case 1: {
        char *s;
        int *a;
        int *b;
        ap += 4;
        s = ((char **)ap)[-1];
        ap += 4;
        a = ((int **)ap)[-1];
        b = *(int **)ap;
        if (s[3] != ':') break;
        if (s[0] != 'u') break;
        if (s[1] >= 113) break;
        if (s[2] != 'k') break;
        if (a != 0) {
            *a = 0;
        }
        if (b != 0) {
            *b = 1;
        }
        result = 1;
        break;
    }
    case 2:
    {
        int kind = 3;
        if (D_800EEBE0.pending != 0 || (D_800EEBE0.flags & 0x10)) {
            kind = 11;
        }
        result = kind;
    }
        break;
    case 3:
        result = -1;
        break;
    case 5: {
        int found;
        int value;
        int key;
        int *out;
        ap += 8;
        found = 0;
        value = 0;
        key = ((int *)ap)[-1];
        out = ((int **)ap)[1];
        if (!(D_800EEBE0.flags & 1) && D_800EEBE0.callback != 0) {
            if (D_800EEBE0.callback(-1, 0, 0, 0, 0, 0) != 0) {
                if (D_800EEBE0.callback(7, key, 0, (int)&found, (int)&value, 0) != 0) {
                    D_800EEBE0.callback(-1, 1, 0, 0, 0, 0);
                }
                if (found == 0) {
                    D_800EEBE0.flags |= 1;
                }
            }
        }
        if (out != 0) {
            *out = value;
        }
        result = found;
        break;
    }
    case 6: {
        int *out = ((int **)ap)[2];
        if (!(D_800EEBE0.flags & 6)) {
            if (D_800EEBE0.block != 0) {
                if (D_800EEBE0.alloc != 0) {
                    D_800EEBE0.alloc(2, D_800EEBE0.alloc_ctx, D_800EEBE0.block);
                }
                D_800EEBE0.block = 0;
            }
            D_800EEBE0.flags &= ~0xC;
            if (D_800EEBE0.alloc != 0) {
                if (func_80099BEC(&D_800EEBE0.buf, D_800EEBE0.alloc, D_800EEBE0.alloc_ctx, 256, 256) != 0) {
                    D_800EEBE0.flags |= 4;
                    result = -3;
                }
            }
        }
        if (out != 0) {
            *out = 0;
        }
        break;
    }
    case 7: {
        int mode = *(int *)ap;
        if (mode == -3) {
            if (D_800EEBE0.flags & 4) {
                Buffer *b;
                D_800EEBE0.block_size = 0;
                D_800EEBE0.block = 0;
                D_800EEBE0.unk40 = 0;
                D_800EEBE0.flags &= ~0xC;
                b = &D_800EEBE0.buf;
                if (b->ok != 0) {
                    result = 1;
                    D_800EEBE0.flags |= 8;
                    D_800EEBE0.block_size = b->used;
                    D_800EEBE0.block = b->data;
                }
                func_80099CA0(b, ((D_800EEBE0.flags >> 3) ^ 1) & 1);
                if (result != 0 && D_800EEBE0.notify != 0) {
                    D_800EEBE0.notify();
                }
            }
        } else if (mode == -2) {
            if (D_800EEBE0.callback(10, mode, 0, 0, 0, 0) != 0) {
                D_800EEBE0.callback(-1, 1, 0, 0, 0, 0);
            }
            result = 1;
            D_800EEBE0.flags &= mode;
        }
        break;
    }
    case 8:
        if (!(D_800EEBE0.flags & 6)) {
            if (D_800EEBE0.block != 0) {
                if (D_800EEBE0.alloc != 0) {
                    D_800EEBE0.alloc(2, D_800EEBE0.alloc_ctx, D_800EEBE0.block);
                }
                D_800EEBE0.block = 0;
                result = 1;
            } else {
                result = 1;
            }
            D_800EEBE0.flags &= ~8;
        }
        break;
    case 9: {
        int mode;
        int a;
        int b;
        void (*done)(int, int, int, int);
        ap += 4;
        mode = ((int *)ap)[-1];
        ap += 8;
        a = ((int *)ap)[-1];
        ap += 4;
        b = ((int *)ap)[-1];
        done = *(void (**)(int, int, int, int))ap;
        if (mode == -2 && D_800EEBE0.callback != 0) {
            D_800EEBE0.read_done = done;
            D_800EEBE0.flags |= 0x10;
            result = D_800EEBE0.callback(11, -2, a, b, 0, (int)func_8008E008);
            if (result == 0) {
                func_8008E008(11, 0, 0, 0);
            }
        } else if (done != 0) {
            done(D_800EEBE0.user, 0, a, b);
        }
        break;
    }
    case 10: {
        int mode;
        int a;
        int b;
        void (*done)(int, int, int, int);
        ap += 4;
        mode = ((int *)ap)[-1];
        ap += 8;
        a = ((int *)ap)[-1];
        ap += 4;
        b = ((int *)ap)[-1];
        done = *(void (**)(int, int, int, int))ap;
        if (mode == -2 && D_800EEBE0.callback != 0) {
            D_800EEBE0.write_done = done;
            D_800EEBE0.flags |= 0x10;
            result = D_800EEBE0.callback(12, -2, a, b, (int)&D_800EEBE0.write_result, (int)func_8008E008);
            if (result == 0) {
                func_8008E008(12, a, 0, 0);
            }
        } else if (done != 0) {
            done(D_800EEBE0.user, a, 0, 0);
        }
        break;
    }
    case 11: {
        int mode;
        int a;
        int n;
        void (*done)(int, int, int, int);
        int got;
        ap += 4;
        mode = ((int *)ap)[-1];
        ap += 8;
        a = ((int *)ap)[-1];
        ap += 4;
        n = ((int *)ap)[-1];
        done = *(void (**)(int, int, int, int))ap;
        got = 0;
        if (mode == -3 && (D_800EEBE0.flags & 4)) {
            got = func_80099CE8(&D_800EEBE0.buf, a, n);
        }
        if (done != 0) {
            if (got == 0) {
                n = 0;
            }
            done(D_800EEBE0.user, a, n, got);
        }
        result = got;
        break;
    }
    case 12: {
        int wait = ((int *)ap)[1];
        result = 1;
        if (D_800EEBE0.pending != 0) {
            do {
                result = D_800EEBE0.pending == 0;
            } while (result == 0 && wait != 0);
        } else if (D_800EEBE0.callback != 0 && (D_800EEBE0.flags & 0x10)) {
            result = D_800EEBE0.callback(-1, wait, 0, 0, 0, 0);
        }
        break;
    }
    case 13:
        if (D_800EEBE0.pending != 0) {
            func_800996A4(D_800EEBE0.pending);
        } else if (D_800EEBE0.callback != 0 && (D_800EEBE0.flags & 0x10)) {
            D_800EEBE0.callback(-2, 0, 0, 0, 0, 0);
        }
        break;
    case 4:
    case 14:
    case 15:
        result = 0;
        break;
    case 16: {
        int status;
        int mode = *(int *)ap;
        result = 0;
        if (mode == -2 && (D_800EEBE0.flags & 0x10) && D_800EEBE0.callback != 0) {
            D_800EEBE0.callback(-3, -2, (int)&status, 0, 0, 0);
            result = status;
        }
        break;
    }
    }
    return result;
}
