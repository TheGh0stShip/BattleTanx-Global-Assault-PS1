typedef struct {
    int x;
    int z;
} Pos2;
typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    char pad0[0x10];
    short cx;
    short cz;
    char pad14[2];
    short x0;
    short x1;
    short z0;
    short z1;
    char pad1E[0x24 - 0x1E];
    unsigned short angle;
    char pad26[0x28 - 0x26];
} Zone;
extern Zone D_800C62B0[];
void func_800167D0(Pos2 *, int, Pos2 *);
int func_8001AE4C(Pos2 *);
void func_8008AAD0(Vector *, Vector *);

static inline int is_zero2(int x, int z) {
    return x == 0 && z == 0;
}

static inline int sine_lookup(int angle) {
    int value;

    __asm__ volatile("andi $8, %1, 0x4000\n\tandi $9, %1, 0x3fff\n\tbeqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\n\tandi $9, $9, 0x3ffe\n\t.set noat\n\tlui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\t.set at\n\tandi $8, %1, 0x8000\n\tbeqz $8, 2f\n\tnop\n\tneg $9, $9\n2:\n\tsll %0, $9, 1"
                     : "=r"(value)
                     : "r"(angle)
                     : "$8", "$9");
    return value;
}

static inline int cosine_lookup(int angle) {
    int value;

    __asm__ volatile("addiu $10, %1, 0x4000\n\tandi $8, $10, 0x4000\n\tandi $9, $10, 0x3fff\n\tbeqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\n\tandi $9, $9, 0x3ffe\n\t.set noat\n\tlui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\t.set at\n\tandi $8, $10, 0x8000\n\tbeqz $8, 2f\n\tnop\n\tneg $9, $9\n2:\n\tsll %0, $9, 1"
                     : "=r"(value)
                     : "r"(angle)
                     : "$8", "$9", "$10");
    return value;
}


void func_800169A8(int x, int z, unsigned short index, Pos2 *out) {
    Zone *zone;
    Pos2 p;
    Pos2 r;
    Vector v;
    short w;
    short h;
    int s;
    int c;
    unsigned short count;
    int shift;
    int mx;
    int mz;
    unsigned short angle;

    zone = &D_800C62B0[index];
    p.x = (short)(x - zone->cx) << 14;
    p.z = (short)(z - zone->cz) << 14;
    func_800167D0(&p, zone->angle, &r);
    w = zone->x1 - zone->x0;
    h = zone->z1 - zone->z0;
    if (w < 2 && h < 2) {
        h = 2;
        w = 2;
    }
    out->z = 0;
    out->x = 0;
    count = 0;
    angle = zone->angle;
    if (angle == 0) {
        s = 0;
        c = 4096;
    } else {
        s = sine_lookup(angle) >> 4;
        c = cosine_lookup(angle) >> 4;
    }
    if (h >= 2) {
        if (r.x <= zone->x0 << 14) {
            count++;
            out->x -= c;
            out->z += s;
        } else if (r.x >= zone->x1 << 14) {
            count++;
            out->x += c;
            out->z -= s;
        }
    }
    if (w >= 2) {
        if (r.z <= zone->z0 << 14) {
            count++;
            out->x -= s;
            out->z -= c;
        } else if (r.z >= zone->z1 << 14) {
            count++;
            out->x += s;
            out->z += c;
        }
    }
    if (out->x == 0 && out->z == 0) {
        mx = ((zone->x1 - zone->x0) >> 1) << 14;
        mz = ((zone->z1 - zone->z0) >> 1) << 14;
        if (r.x < mx) {
            count++;
            out->x = -c;
            out->z += s;
        } else if (mx < r.x) {
            count++;
            out->x = c;
            out->z -= s;
        }
        if (r.z < mz) {
            count++;
            out->x -= s;
            out->z -= c;
        } else if (mz < r.z) {
            count++;
            out->x += s;
            out->z += c;
        }
    }
    if (count >= 2) {
        shift = func_8001AE4C(out);
        if (shift != 0) {
            v.x = out->x >> shift;
            v.y = 0;
            v.z = out->z >> shift;
        } else {
            v.x = out->x;
            v.y = 0;
            v.z = out->z;
        }
        func_8008AAD0(&v, &v);
        out->x = v.x;
        out->z = v.z;
        if (is_zero2(out->x, out->z)) {
            out->z = 4096;
        }
    }
}
