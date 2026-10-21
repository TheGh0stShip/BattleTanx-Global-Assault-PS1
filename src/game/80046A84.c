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
    short vx;
    short vy;
    short vz;
    short pad;
} SVECTOR;
typedef struct {
    char pad0[0xE];
    short height;
    char pad10[0xD0 - 0x10];
} VehicleInfo;
typedef struct {
    char pad0[0xA4];
    unsigned char team;
} Owner;
typedef struct {
    char pad0[8];
    Vector pos;
    char pad14[0x30 - 0x14];
    unsigned short heading;
    char pad32[0x68 - 0x32];
    unsigned short pitch;
    unsigned short roll;
    char pad6C[0x9C - 0x6C];
    int vehicle;
    char padA0[4];
    void *active;
    char padA8[0x208 - 0xA8];
    Owner *owner;
    char pad20C[0x2BC - 0x20C];
    MATRIX matrix;
    MATRIX turret;
    char pad2FC[0x308 - 0x2FC];
    char hull_model[0x3E8 - 0x308];
    int turret_model;
    char pad3EC[0x52C - 0x3EC];
    char sound[0x584 - 0x52C];
    int hidden;
    char pad588[0x594 - 0x588];
    int frame;
} Tank;
typedef struct {
    char pad0[8];
    Tank *tank;
} Holder;

extern int D_800D2FE0;
extern unsigned char D_800D3035;
typedef struct {
    char pad0[0x114];
} Waypoint;
extern Waypoint D_800E3E68[];
extern VehicleInfo D_800A4EF4[];
void func_8007A3CC(void *);
void func_800467C4(Tank *);
void func_8003370C(void *, Vector *, int, int);
void func_8008A53C(MATRIX *, MATRIX *);
void func_8006A19C(void *, Vector *, MATRIX *, int);
void func_80040EE8(Vector *, Tank *, Vector *);

static inline Owner *waypoint_get(int index) {
    if (index == 127) {
        return 0;
    }
    return (Owner *)&D_800E3E68[index];
}

void func_80046A84(Holder *holder) {
    register Tank *t asm("$17");
    register int heading asm("$17");
    register int one asm("$8");
    register int quadrant asm("$8");
    register int index asm("$9");
    register int value asm("$10");
    register MATRIX *rot asm("$5");
    SVECTOR angles;
    Vector offset;
    Vector at;
    MATRIX m;
    MATRIX turn;
    MATRIX spare;
    unsigned char team;
    char *hull;
    int *turret_model;

    t = holder->tank;
    if (t == 0 || t->frame == D_800D2FE0) {
        return;
    }
    team = t->owner->team;
    func_8007A3CC(t->sound);
    func_800467C4(t);
    angles.vx = t->pitch;
    angles.vz = t->roll;
    hull = t->hull_model;
    turret_model = &t->turret_model;
    if (t->active != 0) {
        if (t->owner != waypoint_get(D_800D3035)) {
            at.x = t->pos.x;
            at.y = t->pos.y + D_800A4EF4[t->vehicle].height + 0x82000;
            switch (t->vehicle) {
            case 2:
            case 14:
                at.y += 0x50000;
                break;
            case 1:
            case 5:
            case 12:
                at.y -= 0x1E000;
                break;
            case 10:
                at.y += 0x1E000;
                break;
            }
            at.z = t->pos.z;
            func_8003370C(t->active, &at, (D_800D2FE0 << 9) & 0xFE00, 0);
        }
    }
    if (t->hidden == 1) {
        return;
    }
    m = t->matrix;
    offset.x = t->matrix.t[0];
    offset.y = t->matrix.t[1];
    offset.z = t->matrix.t[2];
    func_8008A53C(&m, &t->turret);
    if (*turret_model != 0) {
        func_8006A19C(turret_model, &offset, &m, team);
    }
    offset.x = 0;
    offset.y = 0;
    offset.z = 0;
    func_80040EE8(&offset, t, &offset);
    rot = &turn;
    heading = t->heading;
    __asm__ volatile("" : "+r"(rot));
    one = 4096;
    *(int *)&rot->m[1][1] = one;
    rot->m[0][1] = 0;
    rot->m[1][0] = 0;
    rot->m[2][1] = 0;
    rot->t[0] = 0;
    rot->t[1] = 0;
    rot->t[2] = 0;
    __asm__ volatile("");
    quadrant = heading & 0x4000;
    __asm__ volatile("");
    index = heading & 0x3fff;
    __asm__ volatile("beqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\tandi $9, $9, 0x3ffe\n\t"
                     "lui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\tandi $8, %2, 0x8000\n\t"
                     "beqz $8, .+12\n\tnop\n\tneg $9, $9"
                     : "+r"(quadrant), "+r"(index)
                     : "r"(heading));
    value = index << 1;
    __asm__ volatile("" : "+r"(value));
    value >>= 4;
    rot->m[0][2] = value;
    __asm__ volatile("neg $10, $10" : "+r"(value));
    rot->m[2][0] = value;
    value = heading + 0x4000;
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
    rot->m[0][0] = value;
    rot->m[2][2] = value;
    __asm__ volatile("");
    func_8008A53C(&m, rot);
    func_8006A19C(hull, &offset, &m, team);
}
