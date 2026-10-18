typedef struct {
    int data[8];
} Block32;

typedef struct {
    int pad;
    int unused;
    int count;
} ModelHeader;

typedef struct {
    int kind;
    void *buffer;
    ModelHeader **model;
    Block32 *params;
    char done;
} Node;

typedef struct {
    Block32 params;
    int pad[7];
    ModelHeader **model;
} Source;

typedef struct {
    char pad[0xC];
    int count;
    char *top;
    char *heap;
    int pad18;
    int free;
} Pool;

extern Pool D_800ADD14;

static inline void *pool_push(int size) {
    Pool *pool = &D_800ADD14;

    pool->top -= size;
    pool->free -= size;
    return pool->top;
}

static inline void *pool_alloc(int size) {
    Pool *pool = &D_800ADD14;
    char *p = pool->heap;

    pool->heap += size;
    pool->free -= size;
    return p;
}

void func_800693B8(Source *src) {
    ModelHeader **model;
    Node *node;
    Block32 *params;

    model = src->model;
    if (model != 0) {
        node = pool_push(sizeof(Node));
        node->kind = 4;
        node->model = model;
        params = pool_alloc(sizeof(Block32));
        node->params = params;
        *params = src->params;
        node->buffer = pool_alloc((*model)->count * 8);
        node->done = 0;
        D_800ADD14.count++;
    }
}
