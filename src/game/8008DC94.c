typedef struct MemCard {
    volatile unsigned int flags;
    char pad04[12];
    void (*callback)(void);
    char pad14[36];
    char *buf;
    unsigned int size;
    unsigned int pos;
    int busy;
    char pad48[12];
} MemCard;

extern MemCard D_800EEBE0;
extern char D_800C6080[];
extern void func_8008AA48(void *, int, int);
extern int func_80094AAC(int);
extern int func_8009982C(int, int, int, void (*)(void));
extern int func_8009940C(int, int, char *, unsigned int, void (*)(void));
extern void func_8008E09C(int, int, char *);

void func_8008DC94(void) {
    func_8008AA48(&D_800EEBE0, 0, 84);
}

void func_8008DCC0(void) {
    void (*cb)(void) = D_800EEBE0.callback;

    D_800EEBE0.busy = 0;
    if (cb != 0) {
        cb();
    }
}

static inline int card_notify(int ev, int arg, char *msg) {
    D_800EEBE0.flags &= ~2;
    func_8008E09C(ev, arg, msg);
    return 1;
}

int func_8008DCF8(int fd, int op, char *arg, unsigned int len) {
    int ret = 0;

    switch (op) {
    case 6:
        break;
    case 7: {
        char name[8];
        unsigned int n = len;
        char *src = arg;
        unsigned int i;
        int mode;
        unsigned int size;

        if (n >= 5) {
            n = 4;
        }
        for (i = 0; i < n; i++) {
            name[i] = func_80094AAC((unsigned char)src[i]);
        }
        name[i] = 0;
        if (name[3] != ':' || name[0] != 'u' || (unsigned char)name[1] > 'p' || name[2] != 'k') {
            break;
        }
        if (D_800EEBE0.flags & 8) {
            mode = -2;
            size = D_800EEBE0.size;
            D_800EEBE0.flags |= 2;
        } else {
            mode = 0;
            size = 0;
        }
        ret = 2;
        if (func_8009982C(fd, mode, size, func_8008DCC0) != 0) {
            break;
        }
        ret = 1;
        D_800EEBE0.flags &= ~2;
        break;
    }
    case 8:
    case 9:
        break;
    case 10:
        if (len < 4 || *(int *)arg != -2) {
            break;
        }
        ret = card_notify(8, 0, D_800C6080);
        break;
    case 11: {
        unsigned int off;
        unsigned int base;
        int mode;

        if (len < 12 || ((int *)arg)[0] != -2) {
            break;
        }
        mode = ((int *)arg)[2];
        base = ((int *)arg)[1];
        off = base;
        if (mode != 1) {
            if (mode != 0) {
                if (mode == 2) {
                    off = D_800EEBE0.size + base;
                }
            }
        } else {
            off = D_800EEBE0.pos + base;
        }
        D_800EEBE0.pos = off < D_800EEBE0.size ? off : D_800EEBE0.size;
        ret = 1;
        break;
    }
    case 12: {
        unsigned int n;
        unsigned int pos;

        if (len < 8 || ((int *)arg)[0] != -2) {
            break;
        }
        n = ((int *)arg)[1];
        if (!(D_800EEBE0.flags & 8) || D_800EEBE0.buf == 0) {
            n = 0;
        } else if (D_800EEBE0.size - D_800EEBE0.pos < n) {
            n = D_800EEBE0.size - D_800EEBE0.pos;
        }
        ret = 2;
        pos = D_800EEBE0.pos;
        D_800EEBE0.pos = pos + n;
        if (func_8009940C(fd, 14, D_800EEBE0.buf + pos, n, func_8008DCC0) != 0) {
            break;
        }
        ret = 1;
        break;
    }
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
        break;
    }
    return ret;
}
