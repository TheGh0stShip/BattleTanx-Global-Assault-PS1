typedef struct Block {
    struct Block *owner;
    unsigned int size;
    int pad8;
} Block;

typedef struct Heap {
    char *end;
} Heap;

extern void func_800853DC(Heap *, Block *, void *, int);
extern int func_800852BC(unsigned int);
extern void func_8008532C(Heap *, Block *, unsigned int, int);
extern void *func_8008A7BC(void *, void *, int);
extern Block *func_80085394(Heap *, Block *, unsigned int, unsigned int);
extern void func_80085300(Heap *, Block *, unsigned int, int);

void *func_800859C8(Heap *heap, Block *slot, unsigned int slot_size, void *src, int src_len, unsigned int need) {
    void *result = 0;
    Block *blk = slot->owner;
    unsigned int flags;
    unsigned int size;
    unsigned int next_size;
    unsigned int next_total;
    unsigned int total;
    unsigned int rest;
    Block *next;
    char *dst;

    flags = 0;
    if (blk != 0) {
        flags = blk->size;
    }
    if (flags & 1) {
        size = flags & ~1;
        next = (Block *)((char *)slot + (slot_size + 12));
        next_size = 0;
        next_total = 0;
        if ((char *)next < heap->end && (next->size & 1)) {
            next_size = next->size & ~1;
            next_total = next_size + 12;
        }
        total = size + 12 + slot_size + next_total;
        if (total >= need) {
            func_800853DC(heap, blk, slot, 1);
            if (next_size != 0) {
                func_8008532C(heap, next, next_size, func_800852BC(next_size));
                func_800853DC(heap, blk, next, 1);
            }
            func_8008532C(heap, blk, total, func_800852BC(total));
            dst = (char *)blk + 12;
            blk->size = total;
            func_8008A7BC(dst, src, src_len);
            rest = total - need;
            if (rest >= 16) {
                Block *split = func_80085394(heap, blk, need, (rest - 12) | 1);

                rest -= 12;
                func_80085300(heap, split, rest, func_800852BC(rest));
            }
            result = dst;
        }
    }
    return result;
}
