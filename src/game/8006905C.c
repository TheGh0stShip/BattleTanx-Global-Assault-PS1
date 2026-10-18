typedef struct {
    short m[3][3];
    short pad;
    int t[3];
} Matrix;

typedef struct {
    int pad;
    int count32;
    int count8;
    int pad0C[3];
    char data[1];
} ModelHeader;

typedef struct {
    unsigned int kind;
    void *buffer;
    ModelHeader **model;
    void *verts;
    char done;
} Node;

typedef struct {
    char pad[0xC];
    int count;
    char *top;
    char *heap;
    char *cursor;
    int free;
} Pool;

extern Pool D_800ADD14;
extern void func_8003E0E4(void *cam, void *params, Matrix *out);
extern void func_80092510(void *m, void *data, void *buffer, int count);
extern void func_8007E570(void *m, void *data, void *buffer, int count);

static inline void *pool_alloc(int size) {
    Pool *pool = &D_800ADD14;
    char *p = pool->heap;

    pool->heap += size;
    pool->free -= size;
    return p;
}

void func_8006905C(void *cam) {
    Node *node;
    int i;
    int count;
    int bytes;
    void *m;
    Matrix local;

    node = (Node *)D_800ADD14.top;
    D_800ADD14.cursor = (char *)node;
    for (i = 0; i < D_800ADD14.count; node++, i++) {
        m = &local;
        count = (*node->model)->count8;
        bytes = count * 8;
        switch (node->kind) {
        case 6:
            pool_alloc(bytes);
        case 4:
            func_8003E0E4(cam, node->verts, m);
            break;
        case 3:
        default:
            m = node->verts;
            break;
        }
        switch (node->kind) {
        case 6:
            func_8007E570(m, node->buffer, node->buffer, count);
            break;
        case 3:
            func_80092510(m, (*node->model)->data, node->buffer, (*node->model)->count32);
            break;
        default:
            func_8007E570(m, (*node->model)->data, node->buffer, count);
            break;
        }
    }
}
