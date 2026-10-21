typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct Vector {
    s32 x;
    s32 y;
    s32 z;
} Vector;

typedef struct Hit {
    s32 pad00[2];
    s32 x;
    s32 pad0C;
    s32 z;
    s32 angle_x;
    s32 pad18;
    s32 angle_z;
    s32 pad20;
} Hit;

typedef struct MatrixObject {
    s16 m00;
    s16 m01;
    s16 m02;
    s16 pad06;
    s32 scale;
    s16 m10;
    s16 m11;
    s16 m12;
    s16 pad12;
    s32 zero14;
    s32 zero18;
    s32 zero1C;
    s32 x;
    s32 y;
    s32 z;
    s8 pad2C[0x10];
    s32 source;
    s32 enabled;
} MatrixObject;

typedef struct TurretSweep {
    s8 pad00[8];
    MatrixObject *object;
    s8 pad0C[8];
    s32 source;
    s8 pad18[8];
    s32 radius;
    s32 x;
    s32 y;
    s32 z;
    s8 pad30[2];
    u16 heading;
    u16 sweep;
    u8 direction;
    u8 mode;
} TurretSweep;

extern u16 func_80019D80(Vector *, Vector *, s32, s32, s32, Hit *);
extern void func_800235E0(Vector *, s32, s32, s32, s32);
extern s32 func_80047B7C(u16, s32);
extern s32 func_80053354(s32);
extern s32 func_8008ACC0(s32);
extern s32 func_8008AD60(s32);
extern s32 func_8008AE30(s32, s32);
extern u8 D_800B0EEC[];
extern s16 D_800C628C;

static __inline__ s32 fixed_mul(s32 a, s32 b) {
    s32 low;
    s32 high;
    __asm__ volatile(
        "mult %2,%3\n\t"
        "mflo %0\n\t"
        "mfhi %1\n\t"
        "srl %0,%0,12\n\t"
        "sll %1,%1,20\n\t"
        "or %0,%0,%1"
        : "=&r"(low), "=&r"(high) : "r"(a), "r"(b));
    return low;
}

static __inline__ void gte_ldlzc(s32 value) {
    __asm__ volatile("mtc2 %0, $30\n\tnop\n\tnop" : : "r"(value));
}

static __inline__ void gte_stlzc(s32 *result) {
    __asm__ volatile("swc2 $31, 0(%0)" : : "r"(result) : "memory");
}

static __inline__ s32 leading_zeros(s32 value) {
    s32 count;
    gte_ldlzc(value);
    gte_stlzc(&count);
    return count;
}

extern s32 abs(s32);

static inline int fixed_div(int numerator, int denominator) {
    int negative;
    int n;
    int sign;
    int d;
    int n_zeros;
    int shifted;
    int d_zeros;
    int excess;
    register int difference asm("$7");
    int scale;
    unsigned int quotient;
    int result;

    sign = numerator & 0x80000000;
    negative = sign ^ (denominator & 0x80000000);
    n = abs(numerator);
    d = abs(denominator);
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        shifted = n << n_zeros;
        d_zeros = leading_zeros(d);
        difference = d_zeros - n_zeros;
        if (difference >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                quotient = (unsigned int)shifted / (d >> scale);
            } else {
                quotient = (unsigned int)shifted / (d << -scale);
            }
            quotient <<= difference;
        } else {
            quotient = (unsigned int)shifted / (d >> -excess);
        }
    } else {
        shifted = n << 12;
        quotient = (unsigned int)shifted / d;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

static __inline__ s32 collide(Vector *from, Vector *to, Hit *hit) {
    D_800C628C = 0;
    return func_80019D80(from, to, 0x403, 0, 0, hit) & 0xFFFF;
}

static __inline__ void matrix_rot_y_init(TurretSweep *sweep) {
    __asm__ volatile(
        "lw $11, 8(%0)\n\t"
        "lhu $12, 50(%0)\n\t"
        "li $8, 4096\n\t"
        "sw $8, 8($11)\n\t"
        "sh $0, 2($11)\n\t"
        "sh $0, 6($11)\n\t"
        "sh $0, 14($11)\n\t"
        "sw $0, 20($11)\n\t"
        "sw $0, 24($11)\n\t"
        "sw $0, 28($11)"
        : : "r"(sweep) : "$8", "memory");
}

static __inline__ void matrix_rot_y_sin(void) {
    __asm__ volatile(
        "andi $8, $12, 0x4000\n\t"
        "andi $9, $12, 0x3fff\n\t"
        "beqz $8, 1f\n\t"
        "nop\n\t"
        "li $8, 16383\n\t"
        "sub $9, $8, $9\n"
        "1:\n\t"
        "andi $9, $9, 0x3ffe\n\t"
        ".set noat\n\t"
        "lui $1, %%hi(D_800B0EEC)\n\t"
        "addu $1, $1, $9\n\t"
        "lhu $9, %%lo(D_800B0EEC)($1)\n\t"
        ".set at\n\t"
        "andi $8, $12, 0x8000\n\t"
        "beqz $8, 2f\n\t"
        "nop\n\t"
        "neg $9, $9\n"
        "2:\n\t"
        "sll $10, $9, 1\n\t"
        "sra $10, $10, 4\n\t"
        "sh $10, 4($11)\n\t"
        "neg $10, $10\n\t"
        "sh $10, 12($11)"
        : : : "$8", "$9", "$10", "memory");
}

static __inline__ void matrix_rot_y_cos(void) {
    __asm__ volatile(
        "addiu $10, $12, 0x4000\n\t"
        "andi $8, $10, 0x4000\n\t"
        "andi $9, $10, 0x3fff\n\t"
        "beqz $8, 1f\n\t"
        "nop\n\t"
        "li $8, 16383\n\t"
        "sub $9, $8, $9\n"
        "1:\n\t"
        "andi $9, $9, 0x3ffe\n\t"
        ".set noat\n\t"
        "lui $1, %%hi(D_800B0EEC)\n\t"
        "addu $1, $1, $9\n\t"
        "lhu $9, %%lo(D_800B0EEC)($1)\n\t"
        ".set at\n\t"
        "andi $8, $10, 0x8000\n\t"
        "beqz $8, 2f\n\t"
        "nop\n\t"
        "neg $9, $9\n"
        "2:\n\t"
        "sll $10, $9, 1\n\t"
        "sra $10, $10, 4\n\t"
        "sh $10, 0($11)\n\t"
        "sh $10, 16($11)"
        : : : "$8", "$9", "$10", "memory");
}

void func_8002A378(TurretSweep *arg0, s32 *arg1) {
    s32 *done = arg1;
    TurretSweep *sweep = arg0;
    Hit hit;
    s32 target[2];
    s32 current[2];
    Vector from;
    Vector to;
    s32 reach;
    u8 mode;
    s32 angle;
    s32 collided;
    s32 heading;

    mode = sweep->mode;
    if (mode != 2) {
        return;
    }

    sweep->sweep += 0x800;
    reach = fixed_mul(sweep->radius, func_8008AD60(sweep->sweep >> 4));
    target[0] = sweep->x + fixed_mul(func_8008AD60(sweep->heading >> 4), reach);
    target[1] = sweep->z + fixed_mul(func_8008ACC0(sweep->heading >> 4), reach);
    current[0] = sweep->x;
    current[1] = sweep->z;
    from.x = current[0];
    from.y = 0;
    from.z = current[1];
    to.x = target[0];
    to.y = 0;
    to.z = target[1];
    collided = collide(&from, &to, &hit);
    current[0] = from.x;
    current[1] = from.z;
    target[0] = to.x;
    target[1] = to.z;
    if (collided) {
        if (sweep->direction == 0) {
            angle = (func_8008AE30(hit.angle_x, hit.angle_z) & 0xFFF) << 4;
            if (func_80047B7C(sweep->heading, angle) > 0) {
                sweep->direction = 1;
            } else {
                sweep->direction = mode;
            }
        }
        heading = sweep->heading;
        if (sweep->direction == 1) {
            angle = heading + 0x400;
        } else {
            angle = heading - 0x400;
        }
        sweep->heading = angle;
        target[0] = sweep->x + fixed_mul(func_8008AD60((u16)angle >> 4), reach);
        target[1] = sweep->z + fixed_mul(func_8008ACC0(sweep->heading >> 4), reach);
        current[0] = sweep->x;
        current[1] = sweep->z;
        from.x = current[0];
        from.y = 0;
        from.z = current[1];
        to.x = target[0];
        to.y = 0;
        to.z = target[1];
        collided = collide(&from, &to, &hit);
        current[0] = from.x;
        current[1] = from.z;
        target[0] = to.x;
        target[1] = to.z;
        if (collided) {
            s32 dz = hit.z - sweep->z;
            s32 dx = hit.x - sweep->x;
            s32 big = abs(dz);
            s32 ax = abs(dx);
            s32 small;
            s32 radius;

            if (big < ax) {
                big = ax;
            }
            small = abs(dz);
            if (ax < small) {
                small = ax;
            }
            big += (small * 3) / 8;
            radius = sweep->radius;
            if (radius == 0) {
                radius = 2;
            }
            sweep->sweep = func_80053354(fixed_div(big, radius)) << 4;
        }
    }

    if (sweep->sweep >= 0x4000) {
        MatrixObject *obj;

        sweep->mode = 3;
        *done = 1;
        sweep->object->enabled = 0;
        sweep->object->source = sweep->source;
        sweep->object->x = sweep->x;
        sweep->object->z = sweep->z;
        sweep->object->y = 0;
        matrix_rot_y_init(sweep);
        matrix_rot_y_sin();
        matrix_rot_y_cos();
        *done = 1;
        from.x = target[0];
        from.z = target[1];
        from.y = sweep->y;
        func_800235E0(&from, 100, 1, 127, 256);
    }
}
