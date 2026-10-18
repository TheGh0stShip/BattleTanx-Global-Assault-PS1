typedef struct { int x; int z; int pad[4]; unsigned short angle; } Frame;
typedef struct { int pad[2]; Frame frame; } Body;
typedef struct { int pad[2]; Body *body; int pad2; int offset; int pad3; int length; int pad4; unsigned short id; } Arm;
int func_8008AD60(int);
int func_8008ACC0(int);
void func_80016190(int, int, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

void func_800301FC(Arm *arm) {
    Body *body = arm->body;
    Frame *f = &body->frame;
    int reach = arm->offset + arm->length / 2;
    int x;
    int z;

    x = body->frame.x + fixed_mul(reach, func_8008AD60(f->angle >> 4));
    z = f->z + fixed_mul(reach, func_8008ACC0(f->angle >> 4));
    func_80016190(arm->id, (to_int(x) << 14) >> 16, (to_int(z) << 14) >> 16);
}
