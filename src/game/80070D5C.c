typedef struct {
    int x, y, z;
} Vector;

typedef struct {
    char pad0[8];
    unsigned short *outer;
    unsigned short *inner;
    unsigned short outer_id;
    unsigned short inner_id;
    unsigned char flag;
    char pad15;
    short center[3];
    short min[3];
    short max[3];
} Zone;

extern Zone *func_800237D0(int, int);
extern unsigned short *func_8006C334(int, int, Vector *, Vector *, int, int, int, int);

static inline int fixed_to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

Zone *func_80070D5C(Vector *a, Vector *b, int arg2, int arg3) {
    Zone *zone;
    Vector near;
    Vector far;
    unsigned short *shape;
    unsigned int hx, hy, hz;

    zone = func_800237D0(67, 40);
    if (zone != 0) {
        near.x = a->x + (b->x - a->x) * 2560 / 8192;
        near.y = a->y + (b->y - a->y) * 2560 / 8192;
        near.z = a->z + (b->z - a->z) * 2560 / 8192;
        far.x = b->x - (b->x - a->x) * 2560 / 8192;
        far.y = b->y - (b->y - a->y) * 2560 / 8192;
        far.z = b->z - (b->z - a->z) * 2560 / 8192;
        shape = func_8006C334(0, 7, a, b, 0, 4096, arg2, arg3);
        zone->outer = shape;
        zone->outer_id = *shape;
        shape = func_8006C334(0, 1, &near, &far, 0, 9216, arg2, arg3);
        zone->inner = shape;
        zone->inner_id = *shape;
        zone->flag = 0;
        hx = (unsigned int)fixed_to_int((b->x - a->x) >> 1) >> 2;
        hy = (unsigned int)fixed_to_int((b->y - a->y) >> 1) >> 2;
        hz = (unsigned int)fixed_to_int((b->z - a->z) >> 1) >> 2;
        zone->center[0] = (unsigned int)fixed_to_int((b->x + a->x) >> 1) >> 2;
        zone->center[1] = (unsigned int)fixed_to_int((b->y + a->y) >> 1) >> 2;
        zone->center[2] = (unsigned int)fixed_to_int((b->z + a->z) >> 1) >> 2;
        zone->min[0] = -hx;
        zone->min[1] = -hy;
        zone->min[2] = -hz;
        zone->max[0] = hx;
        zone->max[1] = hy;
        zone->max[2] = hz;
    }
    return zone;
}
