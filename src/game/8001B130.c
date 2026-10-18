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

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int to_int(int v) {
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

static inline int sq(int v) {
    return v * v;
}

static inline int dist2(int dx, int dz) {
    return dx * dx + dz * dz;
}

int func_8001B130(Body *body, Pos2 *p) {
    Pos2 ends[2];
    int d0;
    int d1;
    int len;

    ends[0].x = body->segment->x;
    ends[0].z = body->segment->z;
    ends[1].x = ends[0].x + fixed_mul(body->segment->length, body->segment->dx);
    ends[1].z = ends[0].z + fixed_mul(body->segment->length, body->segment->dz);
    d0 = dist2(to_int(p->x - ends[0].x), to_int(p->z - ends[0].z));
    d1 = dist2(to_int(p->x - ends[1].x), to_int(p->z - ends[1].z));
    len = sq(to_int(body->segment->length));
    if (len < d0) {
        p->x = ends[1].x;
        p->z = ends[1].z;
        return 1;
    }
    if (len < d1) {
        p->x = ends[0].x;
        p->z = ends[0].z;
        return 1;
    }
    return 0;
}
