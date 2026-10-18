extern int func_80099340(void *, int *, int *, int, int, int, void *);
extern void func_8008EB44(void);
extern void func_8008E8CC(void);

typedef struct {
    volatile int flags;
    char pad4[12];
    char body[136];
    int count;
    int extra;
} S8008EA00;
extern S8008EA00 D_800EEC34;

int func_8008EA00(void) {
    int ok = 1;

    if (!(D_800EEC34.flags & 2)) {
        if ((D_800EEC34.flags & ok) && !(D_800EEC34.flags & 0x10)) {
            if (D_800EEC34.flags & 4) {
                D_800EEC34.flags |= 8;
            } else {
                do {
                    D_800EEC34.count = 0;
                    D_800EEC34.flags &= ~8;
                    D_800EEC34.flags |= 6;
                    if (func_80099340(D_800EEC34.body, &D_800EEC34.count, &D_800EEC34.extra, 0, 255, 0, func_8008E8CC) == 0) {
                        ok = 0;
                        func_8008EB44();
                        D_800EEC34.flags &= ~0xA;
                    }
                    D_800EEC34.flags &= ~4;
                } while (D_800EEC34.flags & 8);
            }
        } else {
            ok = 0;
        }
    }
    return ok;
}
