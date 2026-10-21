typedef struct CacheCtl {
    int reads;
    int partial;
    int misses;
    char pad0C[32];
    int arg;
    volatile unsigned char enabled;
    char pad31;
    volatile unsigned char f50;
    volatile unsigned char valid;
    char pad34[4];
    volatile unsigned char f56;
    volatile unsigned char busy;
    volatile unsigned char active;
    volatile unsigned char hit;
    volatile unsigned char f60;
    char pad3D;
    volatile unsigned char f62;
    char pad3F[25];
    unsigned int lo;
    unsigned int hi;
    char pad60[36];
    int done_a;
    int done_b;
    unsigned int next;
} CacheCtl;

extern CacheCtl D_800EEAE8;
extern int func_80091804(void);
extern int func_800982B0(int, int *, int *);
extern int func_800893AC(int, int);
extern int func_80089E04(unsigned int, char *, int, void (*)(int, char *, int, int));
extern void func_80089120(void);

int func_8008A078(int op, ...) {
    char *ap;
    int ok = 0;

    if (D_800EEAE8.enabled == 0) {
        return ok;
    }
    ap = (char *)&op + 4;
    switch (op) {
    case 0: {
        int *out;

        D_800EEAE8.arg = *(int *)((ap += 4) - 4);
        out = *(int **)((ap += 4) - 4);
        if (out != 0) {
            *out = 0;
        }
        ok = 1;
        break;
    }
    case 1: {
        unsigned char *name = *(unsigned char **)((ap += 4) - 4);
        int *p1 = *(int **)((ap += 4) - 4);
        int *p2 = *(int **)((ap += 4) - 4);

        if (name[2] == ':' && ((name[0] == 'c' && name[1] == 'd') || (name[0] == 'm' && name[1] == 's'))) {
            *p1 = 0;
            ok = 1;
        }
        if (p2 != 0) {
            *p2 = 0;
        }
        break;
    }
    case 2:
        ok = 0;
        if (func_80091804() != 0) {
            ok = 3;
            if (D_800EEAE8.valid == 0 || D_800EEAE8.f50 == 0) {
                ok = 11;
            }
        }
        break;
    case 5: {
        int name;
        int *size_out;
        int handle;
        int size;

        ap += 4;
        name = *(int *)((ap += 4) - 4);
        ap += 4;
        size_out = *(int **)((ap += 4) - 4);
        if (func_800982B0(name, &handle, &size) == 0) {
            break;
        }
        if (size_out != 0) {
            *size_out = size;
        }
        ok = handle;
        break;
    }
    case 4:
    case 7:
        ok = 1;
        break;
    case 9: {
        int base, offset, count;

        base = *(int *)((ap += 4) - 4);
        offset = *(int *)((ap += 4) - 4);
        ap += 8;
        count = *(int *)((ap += 4) - 4);
        ok = func_800893AC(base + offset, count);
        break;
    }
    case 10: {
        int base, offset;
        char *dst;
        int size;
        void (*cb)(int, char *, int, int);

        base = *(int *)((ap += 4) - 4);
        offset = *(int *)((ap += 4) - 4);
        dst = *(char **)((ap += 4) - 4);
        size = *(int *)((ap += 4) - 4);
        cb = *(void **)((ap += 4) - 4);
        ok = func_80089E04(base + offset, dst, size, cb);
        break;
    }
    case 12: {
        int wait;

        ap += 4;
        wait = *(int *)((ap += 4) - 4);
        for (;;) {
            ok = 0;
            if (D_800EEAE8.valid != 0 && D_800EEAE8.f50 != 0) {
                ok = D_800EEAE8.f60 == 0;
            }
            if (ok != 0) {
                break;
            }
            if (wait == 0) {
                break;
            }
        }
        break;
    }
    case 13:
        func_80089120();
        break;
    case 3:
    case 6:
    case 8:
    case 11:
    case 14:
    case 15:
        ok = 0;
        break;
    case 16:
        ok = 0;
        if (D_800EEAE8.valid != 0 && D_800EEAE8.f50 != 0) {
            break;
        }
        ok = D_800EEAE8.done_a;
        break;
    }
    return ok;
}
