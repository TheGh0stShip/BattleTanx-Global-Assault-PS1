typedef struct {
    short m[3][3];
    int t[3];
} MATRIX;
typedef struct {
    unsigned short vx;
    unsigned short vy;
    unsigned short vz;
} Angles;
void func_8008A4B8(MATRIX *, int);
void func_8008A48C(MATRIX *, int);
void func_80015924(MATRIX *);

static inline int table_sine_flat(int angle) {
    register int quadrant asm("$8");
    register int index asm("$9");

    __asm__ volatile("");
    quadrant = angle & 0x4000;
    index = angle & 0x3fff;
    __asm__ volatile("beqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\tandi $9, $9, 0x3ffe\n\t"
                     "lui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\tandi $8, %2, 0x8000\n\t"
                     "beqz $8, .+12\n\tnop\n\tneg $9, $9"
                     : "+r"(quadrant), "+r"(index)
                     : "r"(angle));
    return index;
}

static inline int table_cosine_flat(int angle) {
    register int quadrant asm("$8");
    register int index asm("$9");
    register int turned asm("$10");

    turned = angle + 0x4000;
    __asm__ volatile("" : "+r"(turned));
    quadrant = turned & 0x4000;
    index = turned & 0x3fff;
    __asm__ volatile("beqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\tandi $9, $9, 0x3ffe\n\t"
                     "lui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\tandi $8, %2, 0x8000\n\t"
                     "beqz $8, .+12\n\tnop\n\tneg $9, $9"
                     : "+r"(quadrant), "+r"(index)
                     : "r"(turned));
    return index;
}

void func_80015808(MATRIX *matrix, Angles *rot) {
    register MATRIX *m asm("$17");
    int angle;

    register int one asm("$8");
    register int s asm("$10");
    register int c asm("$10");

    m = matrix;
    angle = -rot->vz;
    __asm__ volatile("");
    one = 4096;
    m->m[2][2] = one;
    m->m[0][2] = 0;
    m->m[1][2] = 0;
    *(int *)&m->m[2][0] = 0;
    m->t[0] = 0;
    m->t[1] = 0;
    m->t[2] = 0;
    s = table_sine_flat(angle) << 1;
    __asm__ volatile("" : "+r"(s));
    s >>= 4;
    m->m[1][0] = s;
    __asm__ volatile("neg $10, $10" : "+r"(s));
    m->m[0][1] = s;
    c = table_cosine_flat(angle) << 1;
    __asm__ volatile("" : "+r"(c));
    c >>= 4;
    m->m[0][0] = c;
    m->m[1][1] = c;
    func_8008A4B8(m, (unsigned short)-rot->vy);
    func_8008A48C(m, (unsigned short)-rot->vx);
    func_80015924(m);
}
