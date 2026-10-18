typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;
typedef struct Pos2 {
    int x;
    int z;
} Pos2;
typedef struct Body {
    int vx;
    int vz;
    int speed;
    int max_speed;
    char pad10[0x18 - 0x10];
    unsigned short mass;
    char pad1A[0x1C - 0x1A];
    int spin;
} Body;
int func_8001EE10(int, int, int, int);
int func_8001EE5C(Pos2 *);
void func_8008AAD0(Vector *, Vector *);
void func_8001B328(Body *, Pos2 *);

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

static inline int is_zero2(int x, int z) {
    return x == 0 && z == 0;
}

static inline void normalize2(Pos2 *p, Vector *v) {
    int shift = func_8001EE5C(p);

    if (shift != 0) {
        v->x = p->x >> shift;
        v->y = 0;
        v->z = p->z >> shift;
    } else {
        v->x = p->x;
        v->y = 0;
        v->z = p->z;
    }
    func_8008AAD0(v, v);
    p->x = v->x;
    p->z = v->z;
    if (is_zero2(p->x, p->z)) {
        p->z = 4096;
    }
}

void func_8001B4B8(Body *body, Pos2 *point, int amount, Pos2 *dir, Pos2 *center) {
    Pos2 r;
    Vector v;
    int dot;
    int k;
    int mag;

    r.x = point->x - center->x;
    r.z = point->z - center->z;
    if (r.x == 0 && r.z == 0) {
        dir->x = fixed_mul(amount, dir->x);
        dir->z = fixed_mul(amount, dir->z);
        func_8001B328(body, dir);
        return;
    }
    normalize2(&r, &v);
    dot = fixed_mul(r.x, dir->x) + fixed_mul(r.z, dir->z);
    if (dot > 0) {
        k = fixed_mul(dot, amount);
        r.x = fixed_mul(k, r.x);
        r.z = fixed_mul(k, r.z);
        func_8001B328(body, &r);
    }
    dir->x = fixed_mul(amount, dir->x);
    dir->z = fixed_mul(amount, dir->z);
    dir->x -= r.x;
    dir->z -= r.z;
    mag = func_8001EE10(dir->x, dir->z, 0, 0);
    if (mag == 0) {
        return;
    }
    normalize2(dir, &v);
    amount = mag / body->mass;
    if (fixed_mul2(dir->z, r.x) - fixed_mul(dir->x, r.z) < 0) {
        amount = -amount;
    }
    body->spin += amount;
}
