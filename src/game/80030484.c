typedef struct { int x, y, z; } Vector;
typedef struct { int pad[2]; int x; int z; int pad2; int y; int pad3[2]; unsigned short angle; } Body;
typedef struct {
    int pad[2];
    Body *body;
    int pad2;
    int offset;
    int pad3;
    int length;
    int pad4;
    unsigned short sound;
    short pad5;
    int pad6[3];
    int model;
    int state;
} Arm;
int func_8008AD60(int);
int func_8008ACC0(int);
void func_8001B094(int);
void func_80035948(int, Vector *, int, int, int, int, int, int);
void func_8006FDB0(int, Vector *, int, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int half_length(Arm *arm) {
    return arm->length / 2;
}

void func_80030484(Arm *arm, int quiet) {
    Body *body = arm->body;
    Vector v;
    int half;
    int a;

    if (arm->sound != 0xFFFF) {
        func_8001B094(arm->sound);
        arm->sound = 0xFFFF;
    }
    a = body->angle >> 4;
    half = half_length(arm);
    v.x = body->x + fixed_mul(func_8008AD60(a), arm->offset + half);
    a = body->angle >> 4;
    half = half_length(arm);
    v.z = body->z + fixed_mul(func_8008ACC0(a), arm->offset + half);
    v.y = body->y;
    if (arm->model != 0) {
        func_80035948(arm->model, &v, body->angle, 0, 0, 0, 0, 0);
    }
    func_8006FDB0(4, &v, 0, 0);
    arm->state = quiet ? -100 : -1;
}
