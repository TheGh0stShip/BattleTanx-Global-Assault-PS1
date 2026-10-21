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
typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    char pad0[4];
    SVECTOR lo;
    SVECTOR hi;
    char pad14[0x20 - 0x14];
    Vector origin;
} Bounds;
typedef struct {
    char pad0[8];
    Bounds *bounds;
} Model;
typedef struct {
    char pad0[2];
    unsigned short model;
    unsigned short part1;
    unsigned short part2;
    unsigned char type;
    unsigned char team;
    unsigned short part3;
} Spec;
typedef struct {
    char pad0[8];
    Bounds *bounds;
    Model *part1;
    Model *part2;
    Model *part3;
    Vector lo;
    Vector hi;
    unsigned short cell;
    unsigned short angle;
    unsigned char solid;
    unsigned char team;
    unsigned char type;
    char pad37;
    int health;
} Prop;

extern Prop *func_800237D0(int, int);
extern Model *func_80026300(void *, unsigned short);
extern Bounds *func_8002618C(void *, Model *, Vector *, unsigned short, int, int, int);
extern unsigned short func_800162F0(Prop *, int, int, int, int, int, int, int, int, int, int, int);
extern void func_8008A63C(MATRIX *, SVECTOR *, SVECTOR *);

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

static inline short to_cell(int value) {
    return fixed_to_int(value) >> 2;
}

void func_80034E60(Spec *spec, void *context, Vector *pos, int rot) {
    register int angle asm("$21");
    register int quadrant asm("$8");
    register int index asm("$9");
    Prop *prop;
    Model *model;
    MATRIX m;
    SVECTOR lo;
    SVECTOR hi;
    register MATRIX *mp asm("$16");
    register int one asm("$8");
    register int value asm("$10");

    angle = rot;
    prop = func_800237D0(24, 60);
    if (prop == 0) {
        return;
    }
    model = func_80026300(context, spec->model);
    prop->part1 = func_80026300(context, spec->part1);
    prop->part2 = func_80026300(context, spec->part2);
    prop->part3 = func_80026300(context, spec->part3);
    prop->bounds = func_8002618C(context, model, pos, angle, 0, 240, 0);
    prop->cell = func_800162F0(prop, to_cell(pos->x), to_cell(pos->z), 0, model->bounds->lo.vx,
                               model->bounds->hi.vx, model->bounds->lo.vz, model->bounds->hi.vz,
                               to_cell(pos->y), (short)(to_cell(pos->y) + 100), (unsigned short)angle,
                               (spec->type == 2 || spec->type == 3 || spec->type == 6) ? 2 : 0x8000);
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
    func_8008A63C(mp, &model->bounds->lo, &lo);
    func_8008A63C(mp, &model->bounds->hi, &hi);
    prop->lo.x = prop->bounds->origin.x + (lo.vx << 14);
    prop->lo.y = prop->bounds->origin.y + (lo.vy << 14);
    prop->lo.z = prop->bounds->origin.z + (lo.vz << 14);
    prop->hi.x = prop->bounds->origin.x + (hi.vx << 14);
    prop->hi.y = prop->bounds->origin.y + (hi.vy << 14);
    prop->hi.z = prop->bounds->origin.z + (hi.vz << 14);
    prop->angle = angle;
    if (spec->type == 1 || spec->type == 6) {
        prop->solid = 1;
    } else {
        prop->solid = 0;
    }
    prop->team = spec->team;
    prop->type = spec->type;
    prop->health = 150;
}
