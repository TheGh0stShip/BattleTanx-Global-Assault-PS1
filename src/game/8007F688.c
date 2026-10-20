typedef struct BufferPool {
    void *begin;
    void *end;
    void *allocation;
    int cursor;
    int chunk_size;
    int chunk_count;
} BufferPool;

typedef char BufferPool_size[(sizeof(BufferPool) == 0x18) ? 1 : -1];
typedef void *(*AllocateBuffer)(int, void *, int);

extern BufferPool D_800EC334;

int func_8007F688(AllocateBuffer allocate_arg, void *argument) {
    register AllocateBuffer allocate asm("$7") = allocate_arg;
    BufferPool *pool = &D_800EC334;
    register int result asm("$6") = 0;
    register int size asm("$16");
    void *allocation;

    if (pool->allocation == 0) {
        register int chunk_size asm("$3");
        asm("" : "+r"(result));
        chunk_size = pool->chunk_size;
        if (chunk_size != 0) {
            register int chunks asm("$2") = pool->chunk_count;
            size = chunk_size * chunks;
            allocation = allocate(result, argument, size);
            if (allocation != 0) {
                pool->allocation = allocation;
                result = size;
            } else {
                result = -1;
            }
        }
    }
    return result;
}
