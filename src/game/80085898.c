typedef struct Block {
    struct Block *prev;
    unsigned int size;
    int pad08;
} Block;

typedef struct Heap {
    char *end;
} Heap;

extern int func_800852BC(unsigned int);
extern void func_8008532C(Heap *, Block *, unsigned int, int);
extern Block *func_80085394(Heap *, Block *, unsigned int, unsigned int);
extern void func_80085300(Heap *, Block *, unsigned int, int);

int func_80085898(Heap *h, Block *b, unsigned int size, unsigned int base, unsigned int want) {
    int ok = 0;
    Block *next = (Block *)((char *)b + (size + 12));
    unsigned int offset;
    unsigned int need;
    unsigned int free_size;
    unsigned int merged;
    unsigned int total;
    Block *after;

    if ((char *)next < h->end) {
        offset = size - base;
        need = want - base;
        __asm__ volatile("");
        free_size = next->size & ~1;
        merged = free_size + 12;
        if (next->size != free_size && merged >= need) {
            func_8008532C(h, next, free_size, func_800852BC(free_size));
            total = size + merged;
            b->size = total;
            after = (Block *)((char *)b + (total + 12));
            if ((char *)after < h->end) {
                after->prev = b;
            }
            free_size = total - offset - want;
            if (free_size >= 16) {
                next = func_80085394(h, b, offset + want, (free_size - 12) | 1);
                free_size -= 12;
                func_80085300(h, next, free_size, func_800852BC(free_size));
            }
            ok = 1;
        }
    }
    return ok;
}
