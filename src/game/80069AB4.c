typedef struct {
    int pad;
    int count32;
    int count8;
} ModelHeader;

typedef struct {
    char pad[0x22];
    short radius;
} ModelInfo;

typedef struct {
    ModelHeader *header;
    int pad;
    ModelInfo *info;
} Model;

typedef struct {
    int kind;
    void *buffer;
    Model *model;
    void *verts;
    char done;
} Node;

typedef struct {
    int x, y, z;
} Vector;

typedef struct {
    int data[8];
} Block32;

typedef struct {
    int min_x;
    int min_z;
    int max_x;
    int max_z;
} Bounds;

typedef struct {
    char pad[0xC];
    int count;
    char *top;
    char *heap;
    int pad18;
    int free;
} Pool;

extern Pool D_800ADD14;
extern Bounds D_800D2E04;

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

static inline int in_bounds(Vector *pos, int radius) {
    if (pos->x + radius < D_800D2E04.min_x << 12 || pos->z + radius < D_800D2E04.min_z << 12
        || D_800D2E04.max_x << 12 < pos->x - radius || D_800D2E04.max_z << 12 < pos->z - radius) {
        return 0;
    }
    return 1;
}

void *func_80069AB4(Model *model, Block32 *params, Vector *pos) {
    Node *node;
    Block32 *copy;
    void *buffer = 0;

    if (model != 0 && model->header != 0) {
        if (!in_bounds(pos, model->info->radius << 12)) {
            return 0;
        }
        node = pool_push(sizeof(Node));
        node->kind = 6;
        node->model = model;
        copy = pool_alloc(sizeof(Block32));
        node->verts = copy;
        *copy = *params;
        buffer = node->buffer = pool_alloc(model->header->count8 * 8);
        node->done = 0;
        D_800ADD14.count++;
    }
    return buffer;
}
