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

static __inline__ s32 fixed_div(s32 numerator, s32 denominator) {
    register s32 negative asm("$9");
    register s32 n asm("$3");
    register s32 d asm("$6");
    register s32 n_zeros asm("$4");
    register s32 d_zeros asm("$5");
    register s32 excess asm("$8");
    register s32 difference asm("$7");
    register s32 divisor asm("$2");
    s32 scale;
    register u32 quotient asm("$4");

    s32 result;

    __asm__ volatile(
        "lui $2,0x8000\n"
        "and $3,$5,$2\n"
        "and $2,$4,$2\n"
        "xor $9,$3,$2\n"
        ".word 0x04A10002\n"
        "addu $3,$5,$0\n"
        "negu $3,$3\n"
        "1:\n"
        ".word 0x04810002\n"
        "addu $6,$4,$0\n"
        "negu $6,$6\n"
        "2:\n"
        : "=r"(negative), "=r"(n), "=r"(d)
        : "r"(numerator), "r"(denominator));
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        n <<= n_zeros;
        d_zeros = leading_zeros(d);
        difference = d_zeros - n_zeros;
        if (difference >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                divisor = d >> scale;
            } else {
                divisor = d << -scale;
            }
            quotient = (u32)n / (u32)divisor;
            quotient <<= difference;
        } else {
            divisor = d >> -excess;
            quotient = (u32)n / (u32)divisor;
        }
    } else {
        n <<= 12;
        quotient = (u32)n / (u32)d;
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

void func_8002A378(TurretSweep *arg0, s32 *arg1) {
    Hit hit;
    s32 target[2];
    s32 current[2];
    Vector from;
    Vector to;
    s32 collided;
    register s32 *done asm("$19") = arg1;
    register TurretSweep *sweep asm("$16") = arg0;
    s32 reach;
    register u8 mode asm("$18");
    s32 angle;
    s32 heading_value;
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
        register s32 direction_one asm("$3") = 1;
        register s32 current_direction asm("$2");

        if (sweep->direction == 0) {
            angle = (func_8008AE30(hit.angle_x, hit.angle_z) & 0xFFF) << 4;
            if (func_80047B7C(sweep->heading, angle) > 0) {
                sweep->direction = 1;
            } else {
                sweep->direction = mode;
            }
            __asm__ volatile("addiu $3,$0,1");
        }
        current_direction = sweep->direction;
        __asm__ volatile("" : "+r"(current_direction));
        heading_value = sweep->heading;
        if (current_direction == direction_one) {
            current_direction = heading_value + 0x400;
        } else {
            current_direction = heading_value - 0x400;
        }
        angle = current_direction;
        sweep->heading = angle;

        target[0] = sweep->x + fixed_mul(func_8008AD60((u32)(angle & 0xFFFF) >> 4), reach);
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
            register s32 delta_z asm("$6");
            register s32 largest asm("$5");
            register s32 delta_x asm("$2");
            register s32 abs_x asm("$4");
            register s32 smallest asm("$3");
            register s32 hit_z asm("$3");
            register s32 origin_z asm("$2");
            register s32 hit_x asm("$2");
            register s32 origin_x asm("$3");

            hit_z = hit.z;
            origin_z = sweep->z;
            delta_z = hit_z - origin_z;
            hit_x = hit.x;
            origin_x = sweep->x;
            largest = delta_z;
            if (delta_z < 0) {
                largest = -largest;
            }
            delta_x = hit_x - origin_x;
            abs_x = delta_x;
            if (delta_x < 0) {
                abs_x = -abs_x;
            }
            if (largest < abs_x) {
                largest = abs_x;
            }
            smallest = delta_z;
            if (delta_z < 0) {
                smallest = -smallest;
            }
            __asm__ volatile(
                "slt $2,$4,$3\n"
                "beqz $2,1f\n"
                "sll $2,$3,1\n"
                "addu $3,$4,$0\n"
                "sll $2,$3,1\n"
                "1:\n"
                : "+r"(smallest), "=r"(delta_x)
                : "r"(abs_x));
            delta_x += smallest;
            if (delta_x < 0) {
                delta_x += 7;
            }
            largest += delta_x >> 3;
            abs_x = sweep->radius;
            if (abs_x == 0) {
                abs_x = 2;
            }
            sweep->sweep = func_80053354(fixed_div(largest, abs_x)) << 4;
        }
    }

    if (sweep->sweep < 0x4000) {
        return;
    }

    {
    register s32 three asm("$2") = 3;
    __asm__ volatile(
        "addiu $6,$0,1\n"
        "sb $2,0x37($16)\n"
        "sw $6,0($19)\n"
        "lw $2,8($16)\n"
        "nop\n"
        "sw $0,0x40($2)\n"
        "lw $3,8($16)\n"
        "lw $2,0x14($16)\n"
        "nop\n"
        "sw $2,0x3c($3)\n"
        "lw $3,8($16)\n"
        "lw $2,0x24($16)\n"
        "nop\n"
        "sw $2,0x20($3)\n"
        "lw $3,8($16)\n"
        "lw $2,0x2c($16)\n"
        "nop\n"
        "sw $2,0x28($3)\n"
        "lw $2,8($16)\n"
        "nop\n"
        "sw $0,0x24($2)\n"
        "lw $11,8($16)\n"
        "lhu $12,0x32($16)\n"
        "addiu $8,$0,0x1000\n"
        "sw $8,8($11)\n"
        "sh $0,2($11)\n"
        "sh $0,6($11)\n"
        "sh $0,0xe($11)\n"
        "sw $0,0x14($11)\n"
        "sw $0,0x18($11)\n"
        "sw $0,0x1c($11)\n"
        "andi $8,$12,0x4000\n"
        "andi $9,$12,0x3fff\n"
        ".word 0x11000003\n"
        "nop\n"
        "addiu $8,$0,0x3fff\n"
        "sub $9,$8,$9\n"
        "andi $9,$9,0x3ffe\n"
        "lui $1,%%hi(D_800B0EEC)\n"
        "addu $1,$1,$9\n"
        "lhu $9,%%lo(D_800B0EEC)($1)\n"
        "andi $8,$12,0x8000\n"
        ".word 0x11000002\n"
        "nop\n"
        "neg $9,$9\n"
        "sll $10,$9,1\n"
        "sra $10,$10,4\n"
        "sh $10,4($11)\n"
        "neg $10,$10\n"
        "sh $10,0xc($11)\n"
        "addiu $10,$12,0x4000\n"
        "andi $8,$10,0x4000\n"
        "andi $9,$10,0x3fff\n"
        ".word 0x11000003\n"
        "nop\n"
        "addiu $8,$0,0x3fff\n"
        "sub $9,$8,$9\n"
        "andi $9,$9,0x3ffe\n"
        "lui $1,%%hi(D_800B0EEC)\n"
        "addu $1,$1,$9\n"
        "lhu $9,%%lo(D_800B0EEC)($1)\n"
        "andi $8,$10,0x8000\n"
        ".word 0x11000002\n"
        "nop\n"
        "neg $9,$9\n"
        "sll $10,$9,1\n"
        "sra $10,$10,4\n"
        "sh $10,0($11)\n"
        "sh $10,0x10($11)\n"
        "addiu $4,$29,0x50\n"
        "sw $6,0($19)\n"
        "lw $2,0x40($29)\n"
        "lw $3,0x44($29)\n"
        "addiu $5,$0,0x64\n"
        "sw $2,0x50($29)\n"
        "sw $3,0x58($29)\n"
        "lw $2,0x28($16)\n"
        "addiu $7,$0,0x7f\n"
        "sw $2,0x54($29)\n"
        "addiu $2,$0,0x100\n"
        ".word 0x0C008D78\n"
        "sw $2,0x10($29)\n"
        : : "r"(three), "r"(done), "r"(sweep) : "memory");
    }
}
