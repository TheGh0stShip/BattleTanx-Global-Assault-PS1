typedef struct {
    short m[3][3];
    int t[3];
} MATRIX;
typedef struct {
    short vx;
    short vy;
    short vz;
    short pad;
} SVECTOR;
void func_8008AA48(void *, int, int);

static inline void gte_SetRotMatrix(MATRIX *m) {
    __asm__ volatile("lw $12, 0(%0)\n\tlw $13, 4(%0)\n\tctc2 $12, $0\n\tctc2 $13, $1\n\t"
                     "lw $12, 8(%0)\n\tlw $13, 12(%0)\n\tlw $14, 16(%0)\n\tctc2 $12, $2\n\tctc2 $13, $3\n\tctc2 $14, $4"
                     :
                     : "r"(m)
                     : "$12", "$13", "$14");
}

static inline void gte_ldv0(SVECTOR *v) {
    __asm__ volatile("lwc2 $0, 0(%0)\n\tlwc2 $1, 4(%0)" : : "r"(v));
}

static inline void gte_rtv0(void) {
    __asm__ volatile("nop\n\tnop\n\tcop2 0x0486012");
}

static inline void gte_stsv(SVECTOR *v) {
    __asm__ volatile("mfc2 $12, $9\n\tmfc2 $13, $10\n\tmfc2 $14, $11\n\tsh $12, 0(%0)\n\tsh $13, 2(%0)\n\tsh $14, 4(%0)"
                     :
                     : "r"(v)
                     : "$12", "$13", "$14", "memory");
}

void func_800249A0(short *rect, short *bounds, int angle, MATRIX *matrix) {
    register MATRIX *m asm("$19");
    SVECTOR corner[4];
    SVECTOR turned[4];
    register int one asm("$8");
    register int quadrant asm("$8");
    register int index asm("$9");
    register int value asm("$10");
    register int a asm("$6");
    SVECTOR *src;
    register SVECTOR *dst asm("$17");
    int i;

    m = matrix;
    a = angle;
    __asm__ volatile("" : "+r"(m));
    one = 4096;
    *(int *)&m->m[1][1] = one;
    m->m[0][1] = 0;
    m->m[1][0] = 0;
    m->m[2][1] = 0;
    m->t[0] = 0;
    m->t[1] = 0;
    m->t[2] = 0;
    __asm__ volatile("");
    quadrant = a & 0x4000;
    index = a & 0x3fff;
    __asm__ volatile("beqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\tandi $9, $9, 0x3ffe\n\t"
                     "lui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\tandi $8, %2, 0x8000\n\t"
                     "beqz $8, .+12\n\tnop\n\tneg $9, $9"
                     : "+r"(quadrant), "+r"(index)
                     : "r"(a));
    value = index << 1;
    __asm__ volatile("" : "+r"(value));
    value >>= 4;
    m->m[0][2] = value;
    __asm__ volatile("neg $10, $10" : "+r"(value));
    m->m[2][0] = value;
    value = a + 0x4000;
    __asm__ volatile("" : "+r"(value));
    quadrant = value & 0x4000;
    index = value & 0x3fff;
    __asm__ volatile("beqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\tandi $9, $9, 0x3ffe\n\t"
                     "lui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\tandi $8, %2, 0x8000\n\t"
                     "beqz $8, .+12\n\tnop\n\tneg $9, $9"
                     : "+r"(quadrant), "+r"(index)
                     : "r"(value));
    value = index << 1;
    __asm__ volatile("" : "+r"(value));
    value >>= 4;
    m->m[0][0] = value;
    m->m[2][2] = value;
    __asm__ volatile("");

    func_8008AA48(corner, 0, sizeof(corner));
    dst = turned;
    func_8008AA48(dst, 0, sizeof(turned));
    corner[0].vx = rect[0];
    corner[0].vy = 0;
    corner[0].vz = rect[1];
    corner[1].vx = rect[0];
    corner[1].vy = 0;
    corner[1].vz = rect[3];
    corner[2].vx = rect[2];
    corner[2].vy = 0;
    corner[2].vz = rect[3];
    corner[3].vx = rect[2];
    corner[3].vy = 0;
    corner[3].vz = rect[1];
    i = 0;
    src = corner;
    for (; i < 4; i++) {
        gte_SetRotMatrix(m);
        gte_ldv0(src);
        gte_rtv0();
        gte_stsv(dst);
        dst++;
        src++;
    }
    bounds[0] = turned[0].vx;
    bounds[2] = turned[0].vx;
    bounds[1] = turned[0].vz;
    bounds[3] = turned[0].vz;
    for (i = 1; i < 4; i++) {
        if (turned[i].vx < bounds[0]) {
            bounds[0] = turned[i].vx;
        } else if (bounds[2] < turned[i].vx) {
            bounds[2] = turned[i].vx;
        }
        if (turned[i].vz < bounds[1]) {
            bounds[1] = turned[i].vz;
        } else if (bounds[3] < turned[i].vz) {
            bounds[3] = turned[i].vz;
        }
    }
}
