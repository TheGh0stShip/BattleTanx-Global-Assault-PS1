typedef void *(*AllocFn)(int op, void *ctx, ...);

typedef struct Buffer {
    int ok;
    char *data;
    unsigned int capacity;
    unsigned int used;
    AllocFn alloc;
    void *ctx;
    unsigned int granule;
} Buffer;

extern unsigned int func_80099B90(Buffer *, unsigned int);
extern void func_8008A7BC(void *, void *, unsigned int);

int func_80099BEC(Buffer *b, AllocFn alloc, void *ctx, unsigned int size, unsigned int granule) {
    int ok = 1;
    unsigned int grow = 0;
    char *p;
    b->ok = ok;
    b->data = 0;
    b->capacity = 0;
    b->used = 0;
    b->alloc = alloc;
    b->ctx = ctx;
    b->granule = granule;
    if (size != 0) {
        grow = func_80099B90(b, size);
    }
    if (grow != 0) {
        p = alloc(0, ctx, grow);
        b->data = p;
        if (p != 0) {
            b->capacity = grow;
        } else {
            b->ok = 0;
            ok = 0;
        }
    }
    return ok;
}
