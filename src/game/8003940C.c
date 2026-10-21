typedef struct { int x; int z; } Pos2;
typedef struct { short x; short z; int pad; } Corner;
typedef struct { short x; short z; } Delta;
typedef struct { int a; int b; int c; int d; } Slopes;
extern Corner D_800D5B0C[5];
extern Corner D_800D5AA4[5];
extern int D_800D5B88;
extern int D_800D5B80;
extern int D_800D5B34;
extern int D_800D5B84;
extern Slopes D_800D5B40;

static inline int sine_lookup(unsigned short angle) {
    int value;

    __asm__ volatile("andi $8, %1, 0x4000\n\tandi $9, %1, 0x3fff\n\tbeqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\n\tandi $9, $9, 0x3ffe\n\t.set noat\n\tlui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\t.set at\n\tandi $8, %1, 0x8000\n\tbeqz $8, 2f\n\tnop\n\tneg $9, $9\n2:\n\tsll %0, $9, 1"
                     : "=r"(value)
                     : "r"(angle)
                     : "$8", "$9");
    return value;
}

static inline int cosine_lookup(unsigned short angle) {
    int value;

    __asm__ volatile("addiu $10, %1, 0x4000\n\tandi $8, $10, 0x4000\n\tandi $9, $10, 0x3fff\n\tbeqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\n\tandi $9, $9, 0x3ffe\n\t.set noat\n\tlui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\t.set at\n\tandi $8, $10, 0x8000\n\tbeqz $8, 2f\n\tnop\n\tneg $9, $9\n2:\n\tsll %0, $9, 1"
                     : "=r"(value)
                     : "r"(angle)
                     : "$8", "$9", "$10");
    return value;
}

void func_8003940C(int angle, Pos2 *pos) {
    short px;
    short pz;
    int left;
    int right;
    short cx;
    short cz;
    int s;
    int c;
    short far;
    int k;
    Delta delta;

    left = angle + 3094;
    left &= 0xffff;
    right = angle - 3094;
    right &= 0xffff;
    k = -9;
    px = (short)pos->x >> 8;
    pz = (short)pos->z >> 8;
    cx = px - ((sine_lookup(angle) * k) >> 16);
    cz = pz + ((cosine_lookup(angle) * k) >> 16);

    s = sine_lookup(left);
    c = cosine_lookup(left);
    k = 11;
    D_800D5B0C[0].x = cx - ((s * k) >> 16);
    D_800D5B0C[0].z = cz + ((c * k) >> 16);
    far = (short)D_800D5B88 >> 8;
    k = 44;
    if (far >= k) {
        k = far;
    }
    D_800D5B0C[1].x = cx - ((k * s) >> 16);
    D_800D5B0C[1].z = cz + ((k * c) >> 16);
    k = 40;
    D_800D5B0C[2].x = cx - ((s * k) >> 16);
    D_800D5B0C[2].z = cz + ((c * k) >> 16);
    k = 84;
    if (far >= k) {
        k = far;
    }
    D_800D5B0C[3].x = cx - ((k * s) >> 16);
    D_800D5B0C[3].z = cz + ((k * c) >> 16);
    k = 200;
    D_800D5B0C[4].x = cx - ((s * k) >> 16);
    D_800D5B0C[4].z = cz + ((c * k) >> 16);

    s = sine_lookup(right);
    c = cosine_lookup(right);
    k = 10;
    D_800D5AA4[0].x = cx - ((s * k) >> 16);
    D_800D5AA4[0].z = cz + ((c * k) >> 16);
    k = 44;
    D_800D5AA4[1].x = cx - ((s * k) >> 16);
    D_800D5AA4[1].z = cz + ((c * k) >> 16);
    k = 40;
    D_800D5AA4[2].x = cx - ((s * k) >> 16);
    D_800D5AA4[2].z = cz + ((c * k) >> 16);
    k = far;
    D_800D5AA4[3].x = cx - ((k * s) >> 16);
    D_800D5AA4[3].z = cz + ((k * c) >> 16);
    k = 200;
    D_800D5AA4[4].x = cx - ((s * k) >> 16);
    D_800D5AA4[4].z = cz + ((c * k) >> 16);

    delta.x = D_800D5B0C[0].x - D_800D5B0C[4].x;
    delta.z = D_800D5B0C[0].z - D_800D5B0C[4].z;
    if (delta.z != 0) {
        D_800D5B80 = (delta.x << 16) / delta.z;
    } else {
        D_800D5B80 = 0;
    }
    delta.x = D_800D5AA4[0].x - D_800D5AA4[4].x;
    delta.z = D_800D5AA4[0].z - D_800D5AA4[4].z;
    if (delta.z != 0) {
        D_800D5B34 = (delta.x << 16) / delta.z;
    } else {
        D_800D5B34 = 0;
    }
    delta.x = D_800D5B0C[3].x - D_800D5AA4[4].x;
    delta.z = D_800D5B0C[3].z - D_800D5AA4[4].z;
    if (delta.z != 0) {
        D_800D5B84 = (delta.x << 16) / delta.z;
    } else {
        D_800D5B84 = 0;
    }
    D_800D5B40.a = D_800D5B84;
    D_800D5B40.b = D_800D5B34;
    D_800D5B40.c = D_800D5B84;
    D_800D5B40.d = D_800D5B80;
}
