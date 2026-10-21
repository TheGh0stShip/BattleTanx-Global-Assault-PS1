typedef struct {
    short m[3][3];
    int t[3];
} MATRIX;
typedef struct {
    short x;
    short y;
    short z;
} SVec3;
typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    char pad0[0x1C];
    SVec3 rot;
    char pad22[0x30 - 0x22];
    Vector pos;
    Vector up;
} Camera;
void func_8008A62C(MATRIX *, int, int, int);
void func_800150A4(SVec3 *);
void func_80015090(Vector *);
void func_800150C4(Camera *, unsigned short);
void func_800150CC(Camera *, Vector *, MATRIX *);
void func_8001578C(Camera *);

static inline void gte_SetRotMatrix(MATRIX *m) {
    __asm__ volatile("lw $12, 0(%0)\n\tlw $13, 4(%0)\n\tctc2 $12, $0\n\tctc2 $13, $1\n\t"
                     "lw $12, 8(%0)\n\tlw $13, 12(%0)\n\tlw $14, 16(%0)\n\tctc2 $12, $2\n\tctc2 $13, $3\n\tctc2 $14, $4"
                     :
                     : "r"(m)
                     : "$12", "$13", "$14");
}

static inline void gte_rtv0(void) {
    __asm__ volatile("nop\n\tnop\n\tcop2 0x041E012");
}

void func_80014E2C(Camera *cam, Vector *target, int angle) {
    MATRIX m;
    Vector *up;
    SVec3 *rot;
    register Vector *pos asm("$17");

    register MATRIX *mp asm("$18");
    register int one asm("$8");
    register int quadrant asm("$8");
    register int index asm("$9");
    register int turned asm("$10");
    register int a asm("$6");
    register int sn asm("$10");
    register int cs asm("$10");

    a = angle;
    mp = &m;
    __asm__ volatile("" : "+r"(mp));
    one = 4096;
    *(int *)&mp->m[1][1] = one;
    mp->m[0][1] = 0;
    mp->m[1][0] = 0;
    mp->m[2][1] = 0;
    mp->t[0] = 0;
    mp->t[1] = 0;
    mp->t[2] = 0;
    __asm__ volatile("");
    quadrant = a & 0x4000;
    index = a & 0x3fff;
    __asm__ volatile("beqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\tandi $9, $9, 0x3ffe\n\t"
                     "lui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\tandi $8, %2, 0x8000\n\t"
                     "beqz $8, .+12\n\tnop\n\tneg $9, $9"
                     : "+r"(quadrant), "+r"(index)
                     : "r"(a));
    sn = index << 1;
    __asm__ volatile("" : "+r"(sn));
    sn >>= 4;
    mp->m[0][2] = sn;
    __asm__ volatile("neg $10, $10" : "+r"(sn));
    mp->m[2][0] = sn;
    turned = a + 0x4000;
    __asm__ volatile("" : "+r"(turned));
    quadrant = turned & 0x4000;
    index = turned & 0x3fff;
    __asm__ volatile("beqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\tandi $9, $9, 0x3ffe\n\t"
                     "lui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\tandi $8, %2, 0x8000\n\t"
                     "beqz $8, .+12\n\tnop\n\tneg $9, $9"
                     : "+r"(quadrant), "+r"(index)
                     : "r"(turned));
    cs = index << 1;
    __asm__ volatile("" : "+r"(cs));
    cs >>= 4;
    mp->m[0][0] = cs;
    mp->m[2][2] = cs;
    func_8008A62C(mp, target->x, target->y, target->z);
    rot = &cam->rot;
    pos = &cam->pos;
    gte_SetRotMatrix(mp);
    func_800150A4(rot);
    gte_rtv0();
    func_80015090(pos);
    {
        int *t = m.t;
        pos->x += t[0];
        pos->y += t[1];
        pos->z += t[2];
    }
    up = &cam->up;
    up->x = 0;
    up->y = 4096;
    up->z = 0;
    func_800150C4(cam, angle);
    func_800150CC(cam, target, mp);
    func_8001578C(cam);
}
