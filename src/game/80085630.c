typedef struct Block {
    struct Block *owner;
    unsigned int size;
    struct Block *prev;
    struct Block *next;
} Block;

typedef struct Heap {
    int pad0;
    unsigned int free;
    Block *bins[32];
} Heap;

extern Heap **func_800855D0(void);
extern unsigned int func_800852BC(unsigned int);
extern void func_8008532C(Heap *, Block *, unsigned int, unsigned int);
extern Block *func_80085394(Heap *, Block *, unsigned int, unsigned int);
extern void func_80085300(Heap *, Block *, unsigned int, unsigned int);
extern void *func_8008AA48(void *, int, unsigned int);

void *func_80085630(Heap **handle, unsigned int size, int from_top, int clear, unsigned char fill) {
    unsigned int result = 0;
    Heap *heap;
    unsigned int bin;
    unsigned int rest_bin;
    unsigned int block_size;
    Block *blk;
    Block *found;

    if (handle == (Heap **)-1) {
        handle = func_800855D0();
    }
    if (size != 0) {
        if (*handle != 0) {
            size = (size + 3) & ~3;
            heap = *handle;
            bin = func_800852BC(size);
            for (; bin < 32 && result == 0; bin++) {
                blk = heap->bins[bin];
                while (blk != 0 && result == 0) {
                    block_size = blk->size;
                    block_size &= ~1;
                    if (block_size >= size) {
                        found = blk;
                        if (block_size - size >= 16) {
                            result = block_size - size - 12;
                            rest_bin = func_800852BC(result);
                            if (from_top == 0) {
                                found = func_80085394(heap, blk, result | 1, size);
                                if (rest_bin != bin) {
                                    func_8008532C(heap, blk, block_size, bin);
                                    func_80085300(heap, blk, result, rest_bin);
                                } else {
                                    heap->free -= block_size - result;
                                }
                            } else {
                                func_8008532C(heap, blk, block_size, bin);
                                blk = func_80085394(heap, blk, size, result | 1);
                                func_80085300(heap, blk, result, rest_bin);
                            }
                        } else {
                            func_8008532C(heap, blk, block_size, bin);
                            blk->size = block_size;
                        }
                        result = (unsigned int)found + 12;
                    } else {
                        blk = blk->next;
                    }
                }
            }
            if (result != 0 && clear != 0) {
                func_8008AA48((void *)result, fill, size);
            }
        }
    }
    return (void *)result;
}
