typedef struct SVECTOR {
    short vx;
    short vy;
    short vz;
    short pad;
} SVECTOR;
typedef struct VECTOR {
    int vx;
    int vy;
    int vz;
} VECTOR;
typedef struct MATRIX {
    short m[3][3];
    short pad;
    int t[3];
} MATRIX;
typedef struct Pos2 {
    int x;
    int z;
} Pos2;
typedef struct Object {
    char pad00[0x2C];
    int min_x;
    int min_z;
    int max_x;
    int max_z;
    char pad3C[0x48 - 0x3C];
} Object;
typedef struct Scene {
    char pad00[0x20];
    Object *objects;
} Scene;
extern Scene *D_800D2FE4;
extern int *D_800D2E00;
int func_80020138(Pos2 *);
void func_8008AAD0(VECTOR *, VECTOR *);

static inline void gte_SetRotMatrix(MATRIX *m) {
    __asm__ volatile("lw $12, 0(%0)\n\tlw $13, 4(%0)\n\tctc2 $12, $0\n\tctc2 $13, $1\n\tlw $12, 8(%0)\n\t"
                     "lw $13, 12(%0)\n\tlw $14, 16(%0)\n\tctc2 $12, $2\n\tctc2 $13, $3\n\tctc2 $14, $4"
                     :
                     : "r"(m)
                     : "$12", "$13", "$14");
}

static inline void gte_ldv0(SVECTOR *v) {
    __asm__ volatile("lwc2 $0, 0(%0)\n\tlwc2 $1, 4(%0)" : : "r"(v));
}

static inline void gte_ldv1(SVECTOR *v) {
    __asm__ volatile("lwc2 $2, 0(%0)\n\tlwc2 $3, 4(%0)" : : "r"(v));
}

static inline void gte_ldv2(SVECTOR *v) {
    __asm__ volatile("lwc2 $4, 0(%0)\n\tlwc2 $5, 4(%0)" : : "r"(v));
}

static inline void gte_rtv0(void) {
    __asm__ volatile("nop\n\tnop\n\tcop2 0x486012");
}

static inline void gte_rtv1(void) {
    __asm__ volatile("nop\n\tnop\n\tcop2 0x48E012");
}

static inline void gte_rtv2(void) {
    __asm__ volatile("nop\n\tnop\n\tcop2 0x496012");
}

static inline void gte_stsv(SVECTOR *v) {
    __asm__ volatile("mfc2 $12, $9\n\tmfc2 $13, $10\n\tmfc2 $14, $11\n\tsh $12, 0(%0)\n\tsh $13, 2(%0)\n\tsh $14, 4(%0)"
                     :
                     : "r"(v)
                     : "$12", "$13", "$14", "memory");
}

static inline void normalize2(Pos2 *in, Pos2 *v) {
    VECTOR t;
    int shift;
    int zero;

    shift = func_80020138(in);
    if (shift != 0) {
        t.vx = in->x >> shift;
        t.vy = 0;
        t.vz = in->z >> shift;
    } else {
        t.vx = in->x;
        t.vy = 0;
        t.vz = in->z;
    }
    func_8008AAD0(&t, &t);
    v->x = t.vx;
    v->z = t.vz;
    zero = v->x == 0 && v->z == 0;
    if (zero) {
        v->z = 4096;
    }
}

static inline void set_axis(SVECTOR *a, int x, int z) {
    a->vx = x;
    a->vy = z;
}

static inline int to_int(int v) {
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

int func_8001F8D8(int count, Pos2 *tri) {
    SVECTOR edge[3];
    SVECTOR rel[4];
    SVECTOR off[4];
    MATRIX m;
    SVECTOR out[4];
    int cross[4];
    Pos2 dir[3];
    SVECTOR unit[3];
    SVECTOR axis[3];
    Object *objects = D_800D2FE4->objects;
    int kept = 0;
    int i;
    int ax;
    int az;
    int bx;
    int bz;
    Object *o;

    edge[0].vx = tri[0].z - tri[2].z;
    edge[0].vz = tri[2].x - tri[0].x;
    edge[1].vx = tri[2].z - tri[1].z;
    edge[1].vz = tri[1].x - tri[2].x;
    edge[2].vx = tri[1].z - tri[0].z;
    edge[2].vz = tri[0].x - tri[1].x;
    dir[0].x = edge[0].vx << 12;
    dir[0].z = edge[0].vz << 12;
    normalize2(&dir[0], (Pos2 *)&unit[0]);
    set_axis(&axis[0], unit[0].vx, unit[0].vz);
    dir[1].x = edge[1].vx << 12;
    dir[1].z = edge[1].vz << 12;
    normalize2(&dir[1], (Pos2 *)&unit[1]);
    set_axis(&axis[1], unit[1].vx, unit[1].vz);
    dir[2].x = edge[2].vx << 12;
    dir[2].z = edge[2].vz << 12;
    normalize2(&dir[2], (Pos2 *)&unit[2]);
    set_axis(&axis[2], unit[2].vx, unit[2].vz);
    m.m[0][0] = axis[0].vx;
    m.m[0][1] = 0;
    m.m[0][2] = axis[0].vy;
    m.m[1][0] = axis[1].vx;
    m.m[1][1] = 0;
    m.m[1][2] = axis[1].vy;
    gte_SetRotMatrix(&m);
    ax = tri[2].x;
    az = tri[2].z;
    bx = tri[0].x;
    bz = tri[0].z;
    for (i = 0; i < count; i++) {
        o = &objects[D_800D2E00[i]];
        rel[0].vx = to_int(o->max_x) - ax;
        rel[0].vz = to_int(o->max_z) - az;
        rel[1].vx = to_int(o->min_x) - ax;
        rel[1].vz = to_int(o->max_z) - az;
        rel[2].vx = to_int(o->min_x) - ax;
        rel[2].vz = to_int(o->min_z) - az;
        rel[3].vx = to_int(o->max_x) - ax;
        rel[3].vz = to_int(o->min_z) - az;
        off[0].vx = to_int(o->max_x) - bx;
        off[0].vz = to_int(o->max_z) - bz;
        off[1].vx = to_int(o->min_x) - bx;
        off[1].vz = to_int(o->max_z) - bz;
        off[2].vx = to_int(o->min_x) - bx;
        off[2].vz = to_int(o->min_z) - bz;
        off[3].vx = to_int(o->max_x) - bx;
        off[3].vz = to_int(o->min_z) - bz;
        gte_ldv0(&rel[0]);
        gte_rtv0();
        cross[0] = off[0].vx * axis[2].vx + off[0].vz * axis[2].vy;
        gte_ldv1(&rel[1]);
        gte_stsv(&out[0]);
        gte_rtv1();
        cross[1] = off[1].vx * axis[2].vx + off[1].vz * axis[2].vy;
        gte_ldv2(&rel[2]);
        gte_stsv(&out[1]);
        gte_rtv2();
        cross[2] = off[2].vx * axis[2].vx + off[2].vz * axis[2].vy;
        gte_ldv0(&rel[3]);
        gte_stsv(&out[2]);
        gte_rtv0();
        cross[3] = off[3].vx * axis[2].vx + off[3].vz * axis[2].vy;
        gte_stsv(&out[3]);
        if (out[0].vx > 0 && out[1].vx > 0 && out[2].vx > 0 && out[3].vx > 0) {
            continue;
        }
        if (out[0].vy > 0 && out[1].vy > 0 && out[2].vy > 0 && out[3].vy > 0) {
            continue;
        }
        if (cross[0] > 0 && cross[1] > 0 && cross[2] > 0 && cross[3] > 0) {
            continue;
        }
        D_800D2E00[kept++] = D_800D2E00[i];
    }
    return kept;
}
