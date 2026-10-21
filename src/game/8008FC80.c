extern void func_8008F4B4(int);
extern void func_8008F410(int);
extern void func_8008F368(int);
extern void func_8008A7BC(void *, void *, unsigned int);

typedef void (*ReadCb8008FC80)(int, char *, unsigned int, int);

typedef struct {
    int handle;
    int flags;
    char pad8[12];
    unsigned int low_water;
    char pad24[4];
    char *ring;
    unsigned int size;
    unsigned int head;
    unsigned int count;
    volatile int direct;
    ReadCb8008FC80 cb;
    char *dbuf;
    unsigned int dlen;
    unsigned int dpos;
} S8008FC80;
extern S8008FC80 D_800EEDF4;

int func_8008FC80(int handle, char *dst, unsigned int len, ReadCb8008FC80 cb) {
    S8008FC80 *s = &D_800EEDF4;
    unsigned int got;
    unsigned int n;

    if (s->direct != 0) {
        func_8008F4B4(0);
    }
    if (!(s->flags & 8)) {
        func_8008F410(0);
        got = 0;
        while (got < len) {
            if (D_800EEDF4.count == 0) {
                break;
            }
            n = D_800EEDF4.size - D_800EEDF4.head;
            if (D_800EEDF4.count < n) {
                n = D_800EEDF4.count;
            }
            if (len - got < n) {
                n = len - got;
            }
            func_8008F410(1);
            func_8008A7BC(dst, D_800EEDF4.ring + D_800EEDF4.head, n);
            func_8008F410(0);
            D_800EEDF4.count -= n;
            D_800EEDF4.head += n;
            got += n;
            if (D_800EEDF4.head >= D_800EEDF4.size) {
                D_800EEDF4.head = 0;
            }
        }
        if (got == len) {
            func_8008F410(1);
            if (cb != 0) {
                cb(D_800EEDF4.handle, dst, got, 1);
            }
        } else {
            D_800EEDF4.cb = cb;
            D_800EEDF4.dbuf = dst;
            D_800EEDF4.dlen = len;
            D_800EEDF4.dpos = got;
            D_800EEDF4.direct = handle;
            func_8008F410(1);
        }
        } else if (cb != 0) {
        cb(D_800EEDF4.handle, dst, 0, 0);
    }
    if (!(D_800EEDF4.flags & 0x10) && D_800EEDF4.size - D_800EEDF4.count >= D_800EEDF4.low_water) {
        func_8008F368(1);
    }
    return 1;
}
