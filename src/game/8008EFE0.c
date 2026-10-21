typedef struct DevCtl {
    int handle;
    int read_cb;
    int write_cb;
    int seek_cb;
} DevCtl;

extern DevCtl D_800EEDE4;
extern int func_8008EC84(int, int, int *, int *, int);
extern int func_8008EB9C(int);
extern void func_8008EC0C(void);
extern int func_8008ED08(int, int);
extern int func_8008ED58(int, int, int, void (*)(int, int, int, int));
extern int func_8008EDCC(int, int, int, int, void (*)(int, int, int, int));
extern int func_8008EE60(int, int, int, int, void (*)(int, int, int, int));
extern int func_8008EEF4(int);
extern void func_8008EF5C(int, int, int, int);

int func_8008EFE0(int path, int *flag, int mode) {
    int result = 0;

    if (flag != 0) {
        *flag = 0;
    }
    if (func_8008EC84(path, mode, &result, flag, 0)) {
        func_8008EB9C(1);
    }
    return result;
}

int func_8008F02C(int op, ...) {
    char *ap;
    int ret = 0;

    ap = (char *)&op + 4;
    switch (op) {
    case 0: {
        int *out;

        D_800EEDE4.handle = *(int *)((ap += 4) - 4);
        out = *(int **)((ap += 4) - 4);
        ret = 0;
        if (out != 0) {
            *out = 0;
        }
        break;
    }
    case 1: {
        unsigned char *name = *(unsigned char **)((ap += 4) - 4);
        int *p1 = *(int **)((ap += 4) - 4);
        int *p2 = *(int **)((ap += 4) - 4);
        int drive = 0;

        if (name[3] == ':' && name[0] == 's' && name[1] == 'e' && name[2] == 'r') {
            *p1 = 0;
            ret = 1;
        } else if (name[1] == ':' && name[0] >= 'a' && name[0] <= 'z') {
            *p1 = 0;
            drive = 1;
            ret = 1;
        }
        if (p2 != 0) {
            *p2 = drive;
        }
        break;
    }
    case 2:
        ret = 3;
        if (func_8008EB9C(0) == 0) {
            ret = 11;
        }
        break;
    case 3:
        ret = -1;
        break;
    case 4:
        ret = 1;
        break;
    case 5: {
        int a, b;

        ap += 4;
        a = *(int *)((ap += 4) - 4);
        ap += 4;
        b = *(int *)((ap += 4) - 4);
        ret = func_8008EFE0(a, (int *)b, 0);
        break;
    }
    case 6: {
        int a, b;

        ap += 4;
        a = *(int *)((ap += 4) - 4);
        b = *(int *)((ap += 4) - 4);
        ret = func_8008EFE0(a, (int *)b, 1);
        break;
    }
    case 7:
        if (func_8008ED08(*(int *)((ap += 4) - 4), 0) != 0) {
            func_8008EB9C(1);
            ret = 1;
        }
        break;
    case 9: {
        int h, buf, len;

        h = *(int *)((ap += 4) - 4);
        ap += 4;
        buf = *(int *)((ap += 4) - 4);
        len = *(int *)((ap += 4) - 4);
        D_800EEDE4.read_cb = *(int *)((ap += 4) - 4);
        ret = func_8008ED58(h, buf, len, func_8008EF5C);
        if (ret == 0) {
            if (D_800EEDE4.read_cb != 0) {
                func_8008EF5C(11, 0, 0, 0);
            }
        }
        return ret;
    }
    case 10: {
        int h, buf, len;

        h = *(int *)((ap += 4) - 4);
        ap += 4;
        buf = *(int *)((ap += 4) - 4);
        len = *(int *)((ap += 4) - 4);
        D_800EEDE4.write_cb = *(int *)((ap += 4) - 4);
        ret = func_8008EDCC(h, buf, len, 0, func_8008EF5C);
        if (ret == 0) {
            if (D_800EEDE4.write_cb != 0) {
                func_8008EF5C(12, buf, 0, 0);
            }
        }
        return ret;
    }
    case 11: {
        int h, buf, len;

        h = *(int *)((ap += 4) - 4);
        ap += 4;
        buf = *(int *)((ap += 4) - 4);
        len = *(int *)((ap += 4) - 4);
        D_800EEDE4.seek_cb = *(int *)((ap += 4) - 4);
        ret = func_8008EE60(h, buf, len, 0, func_8008EF5C);
        if (ret == 0) {
            if (D_800EEDE4.seek_cb != 0) {
                func_8008EF5C(13, buf, 0, 0);
            }
        }
        return ret;
    }
    case 12:
        ap += 4;
        ret = func_8008EB9C(*(int *)((ap += 4) - 4));
        break;
    case 13:
        func_8008EC0C();
        D_800EEDE4.read_cb = 0;
        D_800EEDE4.write_cb = 0;
        D_800EEDE4.seek_cb = 0;
        break;
    case 8:
    case 14:
    case 15:
        ret = 0;
        break;
    case 16:
        ret = func_8008EEF4(*(int *)((ap += 4) - 4));
        break;
    }
    return ret;
}
