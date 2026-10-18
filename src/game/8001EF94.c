typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;
typedef struct Segment {
    int x;
    int z;
    int dx;
    int dz;
    int length;
} Segment;
typedef struct Body {
    char pad00[0x60];
    Segment *segment;
} Body;
typedef struct Pos2 {
    int x;
    int z;
} Pos2;
unsigned short func_80049790(Vector *);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int fixed_mul2(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult\t%2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int idiv(int a, int b) {
    return a / b;
}

static inline void set_vec(Vector *v, int x, int y, int z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

unsigned short func_8001EF94(Body *body, Segment *seg, Pos2 *out) {
    Vector dir;

    body->segment = seg;
    out->x = seg->x + fixed_mul(idiv(seg->length, 2), seg->dx);
    out->z = seg->z + fixed_mul2(idiv(seg->length, 2), seg->dz);
    set_vec(&dir, seg->dx, 0, seg->dz);
    return func_80049790(&dir);
}
