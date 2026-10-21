typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    short m[3][3];
    short pad;
    int t[3];
} Matrix;

typedef struct {
    int x0;
    int z0;
    int x1;
    int z1;
} Rect;

typedef struct {
    char pad0[0x22];
    short radius;
} Bounds;

typedef struct {
    char pad0[8];
    int count;
} Mesh;

typedef struct {
    Mesh *mesh;
    int pad4;
    Bounds *bounds;
} Model;

typedef struct {
    char pad0[8];
    Vector pos;
    char pad14[0x9C - 0x14];
} Camera;

typedef struct {
    char pad0;
    unsigned char current;
    char pad2[2];
    Camera cams[1];
} CameraSet;

typedef struct {
    int type;
    void *verts;
    Model *model;
    Matrix *matrix;
    unsigned char flags;
} DrawNode;

typedef struct {
    char pad0[0xC];
    int count;
    char *nodes;
    char *data;
    int pad18;
    int free;
} DrawQueue;

extern Rect D_800D2E04;
extern CameraSet D_800D3034;
extern DrawQueue D_800ADD14;

static inline void *pool_push(int size) {
    DrawQueue *pool = &D_800ADD14;

    pool->nodes -= size;
    pool->free -= size;
    return pool->nodes;
}

static inline void *pool_alloc(int size) {
    DrawQueue *pool = &D_800ADD14;
    char *p = pool->data;

    pool->data += size;
    pool->free -= size;
    return p;
}

static inline int in_bounds(Vector *pos, int radius) {
    if (pos->x + radius < D_800D2E04.x0 << 12 || pos->z + radius < D_800D2E04.z0 << 12
        || D_800D2E04.x1 << 12 < pos->x - radius || D_800D2E04.z1 << 12 < pos->z - radius) {
        return 0;
    }
    return 1;
}

static inline int round_to_int(int value) {
    if (value >= 0) {
        value += 2048;
        if (value >= 0) {
            return value >> 12;
        }
        return -(-value >> 12);
    }
    if (value - 2048 >= 0) {
        return (value - 2048) >> 12;
    }
    return -((2048 - value) >> 12);
}

void func_800697D8(Model *model, Vector *pos, Matrix *mat, unsigned char flags) {
    Matrix local;
    Vector p;
    Camera *cam;
    DrawNode *node;
    Matrix *m;

    if (model == 0 || model->mesh == 0) {
        return;
    }
    if (!in_bounds(pos, model->bounds->radius << 12)) {
        return;
    }
    local = *mat;
    {
        int x = pos->x;
        int y = pos->y;
        int z = pos->z;

        p.x = x;
        p.y = y;
        p.z = z;
    }
    cam = &D_800D3034.cams[D_800D3034.current];
    local.t[0] = round_to_int(p.x - cam->pos.x);
    local.t[1] = round_to_int(p.y - cam->pos.y);
    local.t[2] = round_to_int(p.z - cam->pos.z);
    if (model == 0) {
        return;
    }
    node = pool_push(sizeof(DrawNode));
    node->type = 4;
    node->model = model;
    m = node->matrix = pool_alloc(sizeof(Matrix));
    *m = local;
    node->verts = pool_alloc(model->mesh->count * 8);
    node->flags = flags;
    D_800ADD14.count++;
}
