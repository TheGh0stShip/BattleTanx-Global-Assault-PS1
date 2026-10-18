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

extern Vert *func_80069AB4(Mesh **, int, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_80027DE0(Mesh **from, Mesh **to, int t, int id, int mode) {
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
