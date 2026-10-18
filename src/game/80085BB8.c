typedef struct Block {
    struct Block *owner;
    unsigned int size;
    struct Block *prev;
    struct Block *next;
} Block;

typedef struct Heap {
    char *end;
} Heap;

extern Block *func_80085B68(void *, char **, Heap **);
extern void func_80085DD4(void *);
extern Block *func_80085394(Heap *, Block *, unsigned int, unsigned int);
extern void func_800853DC(Heap *, Block *, Block *, int);
extern unsigned int func_800852BC(unsigned int);
extern void func_80085300(Heap *, Block *, unsigned int, unsigned int);
extern int func_80085898(Heap *, Block *, unsigned int, unsigned int, unsigned int);
extern void *func_8008A7BC(void *, void *, unsigned int);
extern void *func_800859C8(Heap *, Block *, unsigned int, void *, unsigned int, unsigned int);
extern void *func_80085630(Heap **, unsigned int, int, int, unsigned char);

void *func_80085BB8(void *ptr, unsigned int size, int may_move, int from_top) {
    void *result = 0;
    char *base;
    Heap *heap;
    Block *blk;
    Block *split;
    Block *next;
    unsigned int cur;
    unsigned int offset;
    unsigned int avail;
    void *moved;

    size = (size + 3) & ~3;
    blk = func_80085B68(ptr, &base, &heap);
    cur = blk->size;
    offset = (char *)ptr - base;
    avail = cur - offset;
    if (size == 0) {
        func_80085DD4(ptr);
        return result;
    }
    if (avail >= size) {
        avail -= size;
        if (avail >= 16) {
            cur = avail - 12;
            split = func_80085394(heap, blk, offset + size, cur | 1);
            next = (Block *)((char *)split + avail);
            if ((char *)next < heap->end && (next->size & 1)) {
                func_800853DC(heap, split, next, 0);
                cur = split->size & ~1;
            }
            func_80085300(heap, split, cur, func_800852BC(cur));
        }
        result = ptr;
    } else if (func_80085898(heap, blk, cur, avail, size)) {
        result = ptr;
    } else if (may_move) {
        if (cur >= size) {
            func_8008A7BC(base, ptr, avail);
            result = base;
        } else {
            moved = func_800859C8(heap, blk, cur, ptr, avail, size);
            if (moved != 0) {
                result = moved;
            } else {
                moved = func_80085630(&heap, size, from_top, 0, 0);
                if (moved != 0) {
                    func_8008A7BC(moved, ptr, cur);
                    func_80085DD4(ptr);
                    result = moved;
                }
            }
        }
    }
    return result;
}
