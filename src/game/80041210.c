typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    short m[3][3];
    int t[3];
} MATRIX;
typedef struct {
    char pad0[0x10];
    int flags;
    char pad14[0x80 - 0x14];
    Vector mount;
    char pad8C[0xD0 - 0x8C];
} VehicleInfo;
typedef struct {
    char pad0[8];
    Vector pos;
    char pad14[0x30 - 0x14];
    unsigned short heading;
    char pad32[0x9C - 0x32];
    int type;
    char padA0[0x2BC - 0xA0];
    MATRIX matrix;
} Tank;
extern VehicleInfo D_800A4EF4[];
void func_8008A65C(MATRIX *, Vector *, Vector *);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int sine_lookup(int angle) {
    int value;

    __asm__ volatile("andi $8, %1, 0x4000\n\tandi $9, %1, 0x3fff\n\tbeqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\n\tandi $9, $9, 0x3ffe\n\t.set noat\n\tlui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\t.set at\n\tandi $8, %1, 0x8000\n\tbeqz $8, 2f\n\tnop\n\tneg $9, $9\n2:\n\tsll %0, $9, 1"
                     : "=r"(value)
                     : "r"(angle)
                     : "$8", "$9");
    return value;
}

static inline int cosine_lookup(int angle) {
    int value;

    __asm__ volatile("addiu $10, %1, 0x4000\n\tandi $8, $10, 0x4000\n\tandi $9, $10, 0x3fff\n\tbeqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\n\tandi $9, $9, 0x3ffe\n\t.set noat\n\tlui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\t.set at\n\tandi $8, $10, 0x8000\n\tbeqz $8, 2f\n\tnop\n\tneg $9, $9\n2:\n\tsll %0, $9, 1"
                     : "=r"(value)
                     : "r"(angle)
                     : "$8", "$9", "$10");
    return value;
}



void func_80041210(Tank *tank, Vector *out) {
    Vector v;
    short s;
    short c;

    if (D_800A4EF4[tank->type].flags & 1) {
        s = sine_lookup(tank->heading) >> 4;
        c = cosine_lookup(tank->heading) >> 4;
        v.x = D_800A4EF4[tank->type].mount.x + fixed_mul(D_800A4EF4[tank->type].mount.x, -c) +
              fixed_mul(D_800A4EF4[tank->type].mount.z, -s);
        v.y = D_800A4EF4[tank->type].mount.y;
        v.z = D_800A4EF4[tank->type].mount.z + fixed_mul(D_800A4EF4[tank->type].mount.x, s) +
              fixed_mul(D_800A4EF4[tank->type].mount.z, -c);
        func_8008A65C(&tank->matrix, &v, out);
        out->x += tank->matrix.t[0];
        out->y += tank->matrix.t[1];
        out->z += tank->matrix.t[2];
    } else {
        *out = tank->pos;
    }
}
