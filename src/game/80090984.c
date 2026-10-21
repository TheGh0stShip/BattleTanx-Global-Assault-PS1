typedef struct {
    unsigned long addr;
    unsigned long size;
} SpuMemList;

extern long D_800B7768;
extern long D_800B776C;
extern long D_800B7718;
extern long D_800B7720;
extern SpuMemList *D_800B7BD8;
extern long D_800B7BD0;
extern long D_800B7BD4;
extern void func_8009ABD4(void);

long func_80090984(long size) {
    long i = 0;
    long found = -1;
    long space;
    long last;
    long next;
    unsigned long tsize;
    unsigned long a1;
    unsigned long a0;
    SpuMemList *p;

    if (D_800B7768 == 0) {
        space = 0;
    } else {
        space = (0x10000 - D_800B776C) << D_800B7718;
    }
    if (size & ~D_800B7720) {
        size += D_800B7720;
    }
    size >>= D_800B7718;
    size <<= D_800B7718;
    if (D_800B7BD8[0].addr & 0x40000000) {
        found = 0;
    } else {
        func_8009ABD4();
        for (; i < D_800B7BD0; i++) {
            if ((D_800B7BD8[i].addr & 0x40000000)
                || ((D_800B7BD8[i].addr & 0x80000000) && !(D_800B7BD8[i].size < (unsigned long)size))) {
                found = i;
                break;
            }
        }
    }
    if (found == -1) {
        return -1;
    }
    p = (SpuMemList *)((found << 3) + (unsigned long)D_800B7BD8);
    if (p->addr & 0x40000000) {
        __asm__("" : "=r"(p) : "0"(p));
        if (found >= D_800B7BD0) {
            return -1;
        }
        if (p->size - space < (unsigned long)size) {
            return -1;
        }
        next = found + 1;
        D_800B7BD8[next].addr = ((p->addr & 0x0FFFFFFF) + size) | 0x40000000;
        D_800B7BD8[next].size = p->size - size;
        D_800B7BD4 = next;
        p->size = size;
        p->addr &= 0x0FFFFFFF;
        func_8009ABD4();
        return D_800B7BD8[found].addr;
    }
    tsize = D_800B7BD8[found].size;
    if ((unsigned long)size < tsize) {
        last = D_800B7BD4;
        if (last < D_800B7BD0) {
            unsigned long n = D_800B7BD8[found].addr + size;
            a1 = D_800B7BD8[last].addr;
            a0 = D_800B7BD8[last].size;
            D_800B7BD8[last].addr = n | 0x80000000;
            D_800B7BD8[last].size = tsize - size;
            D_800B7BD4 = last + 1;
            D_800B7BD8[last + 1].addr = a1;
            D_800B7BD8[last + 1].size = a0;
        }
    }
    D_800B7BD8[found].size = size;
    D_800B7BD8[found].addr &= 0x0FFFFFFF;
    func_8009ABD4();
    return D_800B7BD8[found].addr;
}
