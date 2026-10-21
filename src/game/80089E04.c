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
extern void func_80088C30(unsigned int *, char **, int *);
extern int func_80089B70(unsigned int, char *, int, int, void (*)(int, char *, int, int), int, char *);

int func_80089E04(unsigned int addr, char *dst, int size, void (*cb)(int, char *, int, int)) {
    int ret = 1;
    int rem = size;
    unsigned int end;
    char *start;

    if (D_800EEAE8.enabled != 0) {
        end = addr + size;
        start = dst;
        D_800EEAE8.f62 = 0;
        D_800EEAE8.hit = 0;
        D_800EEAE8.active = 0;
        if (size != 0) {
            D_800EEAE8.active = 1;
            if (addr >= D_800EEAE8.lo && addr < D_800EEAE8.hi) {
                func_80088C30(&addr, &dst, &rem);
            }
        }
        if (rem != 0) {
            ret = func_80089B70(addr, dst, rem, size, cb, 0, start);
        }
        D_800EEAE8.active = 0;
        D_800EEAE8.next = end;
        if (rem == 0) {
            if ((D_800EEAE8.f56 != 0 && D_800EEAE8.busy != 0 && D_800EEAE8.hit != 0) ||
                (D_800EEAE8.valid != 0 && D_800EEAE8.f50 != 0 && D_800EEAE8.busy == 0 && D_800EEAE8.f60 == 0 &&
                 D_800EEAE8.busy == 0 && !(end >= D_800EEAE8.lo && end < D_800EEAE8.lo + 2048) &&
                 D_800EEAE8.lo != D_800EEAE8.hi)) {
                func_80089B70(D_800EEAE8.hi, 0, 2048, 2048, 0, 1, 0);
            }
            D_800EEAE8.valid = 1;
            if (cb != 0) {
                D_800EEAE8.done_a = size;
                D_800EEAE8.done_b = size;
                cb(D_800EEAE8.arg, start, size, 1);
            }
            if (size != 0) {
                D_800EEAE8.reads++;
            }
        } else if (rem != size) {
            D_800EEAE8.misses++;
        } else {
            D_800EEAE8.partial++;
        }
    } else if (cb != 0) {
        D_800EEAE8.done_a = 0;
        D_800EEAE8.done_b = 0;
        cb(D_800EEAE8.arg, dst, 0, 0);
        ret = 0;
    }
    return ret;
}
