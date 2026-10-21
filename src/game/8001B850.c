typedef struct Pos2 {
    int x;
    int z;
} Pos2;
typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;
typedef struct Mover {
    int dx;
    int dz;
    int speed;
    int length;
    int accel;
    char pad14[0x30 - 0x14];
    int grip;
} Mover;
extern unsigned short D_800B0EEC[];
extern int D_800DE30C;
int func_8001EE10(int, int, int, int);
int func_8001EE5C(Mover *);
void func_8008AAD0(Vec3 *, Vec3 *);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int table_sin_t2(int value) {
    register int angle asm("$10") = value;
    int r;

    __asm__ volatile("andi $8,%1,0x4000\n\tandi $9,%1,0x3FFF\n\tbeqz $8,1f\n\tnop\n\taddiu $8,$0,0x3FFF\n\t"
                     "sub $9,$8,$9\n1:\n\tandi $9,$9,0x3FFE\n\tlui $1,%%hi(D_800B0EEC)\n\taddu $1,$1,$9\n\t"
                     "lhu $9,%%lo(D_800B0EEC)($1)\n\tandi $8,%1,0x8000\n\tbeqz $8,2f\n\tnop\n\tsub $9,$0,$9\n2:\n\t"
                     "sll %0,$9,1"
                     : "=r"(r)
                     : "r"(angle)
                     : "$8", "$9");
    return r >> 4;
}

static inline int table_sin(int angle) {
    int r;

    __asm__ volatile("andi $8,%1,0x4000\n\tandi $9,%1,0x3FFF\n\tbeqz $8,1f\n\tnop\n\taddiu $8,$0,0x3FFF\n\t"
                     "sub $9,$8,$9\n1:\n\tandi $9,$9,0x3FFE\n\tlui $1,%%hi(D_800B0EEC)\n\taddu $1,$1,$9\n\t"
                     "lhu $9,%%lo(D_800B0EEC)($1)\n\tandi $8,%1,0x8000\n\tbeqz $8,2f\n\tnop\n\tsub $9,$0,$9\n2:\n\t"
                     "sll %0,$9,1"
                     : "=r"(r)
                     : "r"(angle)
                     : "$8", "$9");
    return r >> 4;
}

void func_8001B850(Mover *m, int force, int angle) {
    Pos2 add;
    Pos2 dir;
    Vec3 t;
    int power;
    int top;
    int k;
    int shift;
    int zero;
    int lt;

    if (m->grip == 4096) {
        power = fixed_mul(force, m->length);
    } else {
        power = fixed_mul(force, fixed_mul(m->grip, m->length));
    }
    if (power == 0) {
        return;
    }
    top = m->speed;
    dir.x = table_sin(angle);
    __asm__ volatile("");
    dir.z = table_sin_t2(angle + 0x4000);
    if (power < 0) {
        power = -power;
        dir.x = -dir.x;
        dir.z = -dir.z;
    }
    k = fixed_mul(D_800DE30C, m->accel);
    add.x = fixed_mul(dir.x, k);
    add.z = fixed_mul(dir.z, k);
    m->dx = fixed_mul(m->speed, m->dx);
    m->dz = fixed_mul(m->speed, m->dz);
    m->dx += add.x;
    m->dz += add.z;
    m->speed = func_8001EE10(m->dx, m->dz, 0, 0);
    shift = func_8001EE5C(m);
    if (shift != 0) {
        t.x = m->dx >> shift;
        t.y = 0;
        t.z = m->dz >> shift;
    } else {
        t.x = m->dx;
        t.y = 0;
        t.z = m->dz;
    }
    func_8008AAD0(&t, &t);
    m->dx = t.x;
    m->dz = t.z;
    zero = m->dx == 0 && m->dz == 0;
    if (zero) {
        m->dz = 4096;
    }
    lt = power < top;
    if (!lt && power < m->speed) {
        m->speed = power;
    } else if (lt && top < m->speed) {
        m->speed = top;
    }
}
