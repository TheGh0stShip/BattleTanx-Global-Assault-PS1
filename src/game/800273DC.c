typedef struct {
    short x;
    short y;
    short z;
    short w;
} Vert;

typedef struct {
    char pad0[8];
    int count;
    char pad0C[0x18 - 0xC];
    Vert verts[1];
} Mesh;

typedef struct {
    char pad0[0x3C];
    void *model;
} Entry;

typedef struct {
    char pad0[8];
    int pos[3];
    char pad14[3];
    unsigned char state;
    Mesh **models[5];
    char pad2C[8];
    Entry *entry;
    short timer;
} Crate;

extern Vert *func_80069AB4(Mesh **, Entry *, int *);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline void mesh_lerp(Mesh **from, Mesh **to, int t, Entry *id, int *mode) {
    Mesh *b = *to;
    Mesh *a = *from;
    Vert *va = a->verts;
    Vert *vb = b->verts;
    Vert *out = func_80069AB4(from, id, mode);
    int n;

    if (out == 0) {
        return;
    }
    n = (*from)->count;
    while (1) {
        out->x = va->x + fixed_mul(t, vb->x - va->x);
        out->y = va->y + fixed_mul(t, vb->y - va->y);
        out->z = va->z + fixed_mul(t, vb->z - va->z);
        out->w = va->w;
        if (--n <= 0) {
            break;
        }
        va++;
        vb++;
        out++;
    }
}

void func_800273DC(Crate *c) {
    switch (c->state) {
    case 4:
        c->entry->model = 0;
        mesh_lerp(c->models[0], c->models[1], (c->timer << 12) / 15, c->entry, c->pos);
        break;
    case 6:
        c->entry->model = c->models[4];
        mesh_lerp(c->models[2], c->models[3], (c->timer << 12) / 15, c->entry, c->pos);
        break;
    }
}
