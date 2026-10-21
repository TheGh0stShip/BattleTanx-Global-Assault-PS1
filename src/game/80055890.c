typedef struct {
    unsigned long tag;
    unsigned char r0;
    unsigned char g0;
    unsigned char b0;
    unsigned char code;
    short x0;
    short y0;
    unsigned char r1;
    unsigned char g1;
    unsigned char b1;
    unsigned char pad1;
    short x1;
    short y1;
    unsigned char r2;
    unsigned char g2;
    unsigned char b2;
    unsigned char pad2;
    short x2;
    short y2;
} POLY_G3;
typedef struct {
    unsigned addr : 24;
    unsigned len : 8;
} P_TAG;
typedef struct {
    unsigned long ot[0x4008 / 4];
} OrderingTable;
typedef struct {
    short m[3][3];
    int t[3];
} Matrix;
typedef struct {
    short vx;
    short vy;
    short vz;
    short pad;
} SVector;
extern OrderingTable D_800D5B8C[];
extern int D_800A48B4;
extern void *func_80068EE8(int);
extern void func_8007F7E8(void *);

static inline void matrix_clear_y(Matrix *m) {
    __asm__ volatile("li $8, 4096\n\tsw $8, 8(%0)\n\tsh $0, 2(%0)\n\tsh $0, 6(%0)\n\tsh $0, 14(%0)\n\tsw $0, 20(%0)\n\tsw $0, 24(%0)\n\tsw $0, 28(%0)"
                     :
                     : "r"(m)
                     : "$8", "memory");
}

static inline void matrix_sin_y(Matrix *m, int angle) {
    __asm__ volatile("andi $8, %0, 0x4000\n\tandi $9, %0, 0x3fff\n\tbeqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\n\tandi $9, $9, 0x3ffe\n\t.set noat\n\tlui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\t.set at"
                     :
                     : "r"(angle)
                     : "$8", "$9");
    __asm__ volatile("andi $8, %1, 0x8000\n\tbeqz $8, 2f\n\tnop\n\tneg $9, $9\n2:\n\tsll $10, $9, 1\n\tsra $10, $10, 4\n\tsh $10, 4(%0)\n\tneg $10, $10\n\tsh $10, 12(%0)"
                     :
                     : "r"(m), "r"(angle)
                     : "$8", "$9", "$10", "memory");
}

static inline void matrix_cos_y(Matrix *m, int angle) {
    __asm__ volatile("addiu $10, %1, 16384\n\tandi $8, $10, 0x4000\n\tandi $9, $10, 0x3fff\n\tbeqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\n\tandi $9, $9, 0x3ffe\n\t.set noat\n\tlui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\t.set at\n\tandi $8, $10, 0x8000\n\tbeqz $8, 2f\n\tnop\n\tneg $9, $9\n2:\n\tsll $10, $9, 1\n\tsra $10, $10, 4\n\tsh $10, 0(%0)\n\tsh $10, 16(%0)"
                     :
                     : "r"(m), "r"(angle)
                     : "$8", "$9", "$10", "memory");
}

static inline void gte_SetRotMatrix(Matrix *m) {
    __asm__ volatile("lw $12, 0(%0)\n\tlw $13, 4(%0)\n\tctc2 $12, $0\n\tctc2 $13, $1\n\t"
                     "lw $12, 8(%0)\n\tlw $13, 12(%0)\n\tlw $14, 16(%0)\n\tctc2 $12, $2\n\tctc2 $13, $3\n\tctc2 $14, $4"
                     :
                     : "r"(m)
                     : "$12", "$13", "$14");
}

static inline void gte_ldv0(SVector *v) {
    __asm__ volatile("lwc2 $0, 0(%0)\n\tlwc2 $1, 4(%0)" : : "r"(v));
}

static inline void gte_rtv0(void) {
    __asm__ volatile("nop\n\tnop\n\tcop2 0x0486012");
}

static inline void gte_stsv(SVector *v) {
    __asm__ volatile("mfc2 $12, $9\n\tmfc2 $13, $10\n\tmfc2 $14, $11\n\tsh $12, 0(%0)\n\tsh $13, 2(%0)\n\tsh $14, 4(%0)"
                     :
                     : "r"(v)
                     : "$12", "$13", "$14", "memory");
}

static inline int round_fixed(int x) {
    return x >= 0 ? (x + 2048 >= 0 ? (x + 2048) >> 12 : -(-(x + 2048) >> 12))
                  : (x - 2048 >= 0 ? (x - 2048) >> 12 : -(-(x - 2048) >> 12));
}

static inline int aspect(int v) {
    int k = 6553;
    return round_fixed(v * k);
}

void func_80055890(short x, short y, int angle, unsigned char *color) {
    POLY_G3 *poly;
    Matrix m;
    SVector in[3];
    SVector out[3];
    SVector *src;
    SVector *dst;
    Matrix *mp;
    int i;
    unsigned long *ot;

    poly = func_80068EE8(sizeof(POLY_G3));
    if (poly == 0) {
        return;
    }
    ((unsigned char *)poly)[3] = 6;
    poly->code = 0x30;
    poly->r0 = 250;
    poly->g0 = 250;
    poly->b0 = 250;
    poly->r1 = color[0];
    poly->g1 = color[1];
    poly->b1 = color[2];
    poly->r2 = color[0];
    poly->g2 = color[1];
    poly->b2 = color[2];
    if (color[3] < 255) {
        poly->code |= 2;
    }
    matrix_clear_y(&m);
    matrix_sin_y(&m, angle);
    matrix_cos_y(&m, angle);
    in[0].vx = 0;
    in[0].vy = 0;
    in[0].vz = 3;
    in[1].vx = -3;
    in[1].vy = 0;
    in[1].vz = -3;
    in[2].vx = 3;
    in[2].vy = 0;
    in[2].vz = -3;
    for (i = 0, mp = &m, dst = out, src = in; i < 3; i++) {
        gte_SetRotMatrix(mp);
        gte_ldv0(src);
        gte_rtv0();
        gte_stsv(dst);
        dst++;
        src++;
    }
    out[0].vx = aspect(out[0].vx);
    out[1].vx = aspect(out[1].vx);
    out[2].vx = aspect(out[2].vx);
    out[0].vx += x;
    out[0].vz += y;
    out[1].vx += x;
    out[1].vz += y;
    out[2].vx += x;
    out[2].vz += y;
    poly->x0 = out[0].vx;
    poly->y0 = out[0].vz;
    poly->x1 = out[1].vx;
    poly->y1 = out[1].vz;
    poly->x2 = out[2].vx;
    poly->y2 = out[2].vz;
    ot = D_800D5B8C[D_800A48B4].ot;
    ((P_TAG *)poly)->addr = ((P_TAG *)ot)->addr;
    ((P_TAG *)ot)->addr = (unsigned long)poly;
    func_8007F7E8(poly + 1);
}
