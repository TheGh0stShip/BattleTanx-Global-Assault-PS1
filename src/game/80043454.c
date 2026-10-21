typedef struct {
    short m[3][3];
    int t[3];
} MATRIX;
typedef struct {
    int x;
    int y;
    int z;
} VECTOR;
typedef struct {
    char pad0[8];
    int x;
    int y;
    int z;
    char pad14[0x2C - 0x14];
    unsigned short yaw;
    char pad2E[0x68 - 0x2E];
    unsigned short pitch;
    unsigned short roll;
    char pad6C[0x6E - 0x6C];
    unsigned short turret;
    char pad70[0x9C - 0x70];
    int kind;
    char padA0[0x21C - 0xA0];
    unsigned short barrel_pitch;
    char pad21E[0x224 - 0x21E];
    unsigned short barrel_roll;
    char pad226[0x27E - 0x226];
    unsigned short sub_turret;
    VECTOR offset;
    char pad28C[0x2BC - 0x28C];
    MATRIX matrix;
} Body;

void func_8008A4E4(MATRIX *, int);
void func_8008A4B8(MATRIX *, int);
void func_8008A48C(MATRIX *, int);
void func_8008A53C(MATRIX *, MATRIX *);
void func_8008A5B4(MATRIX *, MATRIX *);
void func_8008A65C(MATRIX *, VECTOR *, VECTOR *);
void func_8008A62C(MATRIX *, int, int, int);

static inline int table_sine_flat(int angle) {
    register int quadrant asm("$8");
    register int index asm("$9");

    __asm__ volatile("");
    quadrant = angle & 0x4000;
    __asm__ volatile("");
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
    __asm__ volatile("");
    index = turned & 0x3fff;
    __asm__ volatile("beqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\tandi $9, $9, 0x3ffe\n\t"
                     "lui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\tandi $8, %2, 0x8000\n\t"
                     "beqz $8, .+12\n\tnop\n\tneg $9, $9"
                     : "+r"(quadrant), "+r"(index)
                     : "r"(turned));
    return index;
}

static inline void rot_matrix_z(MATRIX *m, int angle) {
    register int one asm("$8");
    register int value asm("$10");

    __asm__ volatile("");
    one = 4096;
    m->m[2][2] = one;
    m->m[0][2] = 0;
    m->m[1][2] = 0;
    *(int *)&m->m[2][0] = 0;
    m->t[0] = 0;
    m->t[1] = 0;
    m->t[2] = 0;
    value = table_sine_flat(angle) << 1;
    __asm__ volatile("" : "+r"(value));
    value >>= 4;
    m->m[1][0] = value;
    __asm__ volatile("neg $10, $10" : "+r"(value));
    m->m[0][1] = value;
    value = table_cosine_flat(angle) << 1;
    __asm__ volatile("" : "+r"(value));
    value >>= 4;
    m->m[0][0] = value;
    m->m[1][1] = value;
    __asm__ volatile("");
}

void func_80043454(Body *body) {
    VECTOR offset;
    MATRIX turret;
    MATRIX sub;
    MATRIX barrel;
    register MATRIX *m asm("$16");
    register int one asm("$8");
    register int value asm("$10");
    register int pitch asm("$11");
    register int quadrant asm("$8");
    register int index asm("$9");
    MATRIX *rot;
    register MATRIX *first asm("$4");

    m = &body->matrix;
    pitch = body->pitch;
    __asm__ volatile("" : "+r"(m));
    one = 4096;
    *(int *)&m->m[0][0] = one;
    *(int *)&m->m[0][2] = 0;
    m->m[2][0] = 0;
    m->t[0] = 0;
    m->t[1] = 0;
    m->t[2] = 0;
    __asm__ volatile("");
    quadrant = pitch & 0x4000;
    __asm__ volatile("");
    index = pitch & 0x3fff;
    __asm__ volatile("beqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\tandi $9, $9, 0x3ffe\n\t"
                     "lui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\tandi $8, %2, 0x8000\n\t"
                     "beqz $8, .+12\n\tnop\n\tneg $9, $9"
                     : "+r"(quadrant), "+r"(index)
                     : "r"(pitch));
    value = index << 1;
    __asm__ volatile("" : "+r"(value));
    value >>= 4;
    m->m[2][1] = value;
    __asm__ volatile("neg $10, $10" : "+r"(value));
    m->m[1][2] = value;
    value = pitch + 0x4000;
    __asm__ volatile("" : "+r"(value));
    quadrant = value & 0x4000;
    __asm__ volatile("");
    index = value & 0x3fff;
    __asm__ volatile("beqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\tandi $9, $9, 0x3ffe\n\t"
                     "lui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\tandi $8, %2, 0x8000\n\t"
                     "beqz $8, .+12\n\tnop\n\tneg $9, $9"
                     : "+r"(quadrant), "+r"(index)
                     : "r"(value));
    value = index << 1;
    __asm__ volatile("" : "+r"(value));
    value >>= 4;
    m->m[1][1] = value;
    m->m[2][2] = value;
    func_8008A4E4(m, body->roll);
    func_8008A4B8(m, body->yaw);
    if (body->kind != 2 && body->turret != 0) {
        rot = &turret;
        __asm__ volatile("" : "+r"(rot));
        rot_matrix_z(rot, body->turret);
        func_8008A53C(m, rot);
    }
    m = &body->matrix;
    __asm__ volatile("" : "+r"(m));
    func_8008A65C(m, &body->offset, &offset);
    if (body->kind == 3 && body->sub_turret != 0) {
        rot = &sub;
        __asm__ volatile("" : "+r"(rot));
        rot_matrix_z(rot, body->sub_turret);
        func_8008A53C(m, rot);
    }
    m = &barrel;
    __asm__ volatile("" : "+r"(m));
    one = 4096;
    *(int *)&m->m[0][0] = one;
    *(int *)&m->m[0][2] = 0;
    *(int *)&m->m[1][1] = one;
    *(int *)&m->m[2][0] = 0;
    *(int *)&m->m[2][2] = one;
    m->t[0] = 0;
    m->t[1] = 0;
    m->t[2] = 0;
    func_8008A48C(m, body->barrel_pitch);
    func_8008A4E4(m, body->barrel_roll);
    first = m;
    m = &body->matrix;
    func_8008A5B4(first, m);
    func_8008A62C(m, body->x + offset.x, body->y + offset.y, body->z + offset.z);
}
