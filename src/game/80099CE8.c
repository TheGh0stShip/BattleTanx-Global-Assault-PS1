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

int func_80099CE8(Buffer *b, void *src, unsigned int n) {
    char *p;
    unsigned int grow;
    unsigned int size;
    unsigned int used;

    if (b->ok != 0 && n != 0) {
        p = b->data;
        grow = func_80099B90(b, n);
        if (grow != 0) {
            size = grow + b->capacity;
            if (p == 0) {
                p = b->alloc(0, b->ctx, size);
            } else {
                p = b->alloc(1, b->ctx, p, size);
            }
            if (p != 0) {
                b->data = p;
                b->capacity = size;
            } else {
                b->ok = 0;
            }
        }
        if (b->ok != 0) {
            used = b->used;
            func_8008A7BC(p + used, src, n);
            b->used = used + n;
        }
    }
    return b->ok;
}
