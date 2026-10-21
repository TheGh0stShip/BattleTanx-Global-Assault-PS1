typedef struct {
    short m[3][3];
    int t[3];
} MATRIX;
typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    char pad0[4];
    int count;
    int style;
    char pad0C[0x18 - 0xC];
    char parts[1];
} ModelInfo;
typedef struct {
    ModelInfo *info;
} Model;
typedef struct Piece Piece;
struct Piece {
    char pad0[8];
    Piece *next;
    short ox;
    short oy;
    short oz;
    char pad12[2];
    Vector pos;
    Vector vel;
    short rx;
    unsigned short ry;
    short rz;
    short spin_x;
    short spin_y;
    short spin_z;
};
typedef struct {
    char pad0[8];
    Model *model;
    int count;
    Vector pos;
    Piece *pieces;
    int scale;
} Debris;

extern Debris *func_800237D0(int, int);
extern Piece *func_80022BD4(void);
extern void func_8002382C(Piece *);
extern void *func_8007374C(short *, void *, int, char *);
extern void func_8008A65C(MATRIX *, Vector *, Vector *);
extern unsigned int func_80086C84(void);
extern void func_80072C50(int, Vector *, Vector *, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_800738D4(Model *model, Vector *pos, int angle, short *push) {
    Debris *debris;
    ModelInfo *info;
    Piece *piece;
    Piece **link;
    void *prev;
    char *parts;
    int count;
    unsigned short heading;
    int style;
    int i;
    Vector local;
    MATRIX m;
    register MATRIX *mp asm("$2");
    register int one asm("$8");
    register int quadrant asm("$8");
    register int index asm("$9");
    register int value asm("$10");

    piece = 0;
    prev = piece;
    debris = func_800237D0(70, 36);
    heading = angle;
    if (debris == 0) {
        return;
    }
    debris->model = model;
    debris->pos = *pos;
    debris->scale = 0x50000;
    info = model->info;
    __asm__ volatile("");
    count = info->count;
    parts = info->parts;
    style = info->style;
    debris->count = count;
    __asm__ volatile("");
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
    quadrant = angle & 0x4000;
    __asm__ volatile("");
    index = angle & 0x3fff;
    __asm__ volatile("beqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\tandi $9, $9, 0x3ffe\n\t"
                     "lui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\tandi $8, %2, 0x8000\n\t"
                     "beqz $8, .+12\n\tnop\n\tneg $9, $9"
                     : "+r"(quadrant), "+r"(index)
                     : "r"(angle));
    value = index << 1;
    __asm__ volatile("" : "+r"(value));
    value >>= 4;
    mp->m[0][2] = value;
    __asm__ volatile("neg $10, $10" : "+r"(value));
    mp->m[2][0] = value;
    value = angle + 0x4000;
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
    mp->m[0][0] = value;
    mp->m[2][2] = value;
    __asm__ volatile("");

    i = 0;
    __asm__("" : "+r"(i));
    link = &debris->pieces;
    for (; i < count; i++) {
        piece = func_80022BD4();
        if (piece == 0) {
            break;
        }
        *link = piece;
        link = &piece->next;
    }
    *link = 0;
    if (i < count) {
        for (piece = debris->pieces; piece != 0; piece = piece->next) {
            func_8002382C(piece);
        }
        debris->pieces = 0;
        return;
    }
    piece = debris->pieces;
    do {
        prev = func_8007374C(&piece->ox, prev, style, parts);
        local.x = piece->ox << 12;
        local.y = piece->oy << 12;
        local.z = piece->oz << 12;
        func_8008A65C(&m, &local, &piece->pos);
        piece->pos.x += pos->x;
        piece->pos.y += pos->y;
        piece->pos.z += pos->z;
        piece->vel.x = fixed_mul(func_80086C84() >> 20, 0x18001) - 0xC000;
        piece->vel.z = fixed_mul(func_80086C84() >> 20, 0x18001) - 0xC000;
        piece->vel.y = fixed_mul(func_80086C84() >> 20, 0x12001);
        piece->vel.x += fixed_mul(0xC000, push[0]);
        piece->vel.z += fixed_mul(0xC000, push[2]);
        piece->vel.y += fixed_mul(0x12000, push[1]);
        if (((func_80086C84() >> 16) & 7) == 7) {
            func_80072C50(0, &piece->pos, &piece->vel, fixed_mul(func_80086C84() >> 20, 2049) + 6144);
        }
        piece->rx = 0;
        piece->ry = heading;
        piece->rz = 0;
        piece->spin_x = 0;
        piece->spin_y = fixed_mul(func_80086C84() >> 20, 2049) - 1024;
        piece->spin_z = fixed_mul(func_80086C84() >> 20, 1025) - 512;
        piece = piece->next;
    } while (piece != 0);
}
