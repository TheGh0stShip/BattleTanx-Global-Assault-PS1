typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;
typedef struct Body {
    int vx;
    int vz;
    int speed;
    int max_speed;
    char pad10[0x18 - 0x10];
    unsigned short mass;
} Body;
typedef struct Pos2 {
    int x;
    int z;
} Pos2;
int func_8001EE10(int, int, int, int);
int func_8001EE5C(Body *);
void func_8008AAD0(Vector *, Vector *);

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

void func_8001B328(Body *body, Pos2 *impulse) {
    Vector v;
    int momentum;
    int shift;

    momentum = body->speed * body->mass;
    body->vx = fixed_mul2(momentum, body->vx);
    body->vz = fixed_mul(momentum, body->vz);
    body->vx += impulse->x;
    body->vz += impulse->z;
    body->speed = func_8001EE10(body->vx, body->vz, 0, 0);
    if (body->speed == 0) {
        return;
    }
    shift = func_8001EE5C(body);
    if (shift != 0) {
        v.x = body->vx >> shift;
        v.y = 0;
        v.z = body->vz >> shift;
    } else {
        v.x = body->vx;
        v.y = 0;
        v.z = body->vz;
    }
    func_8008AAD0(&v, &v);
    body->vx = v.x;
    body->vz = v.z;
    if (is_zero2(body->vx, body->vz)) {
        body->vz = 4096;
    }
    body->speed = body->speed / body->mass;
    if (body->max_speed * 2 < body->speed) {
        body->speed = body->max_speed * 2;
    }
}
