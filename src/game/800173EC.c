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
int func_8001AE4C(Pos2 *);
void func_8008AAD0(Vector *, Vector *);
void func_80016EE0(Zone *, Zone *, Zone *);
unsigned short func_80017260(Zone *, Zone *);

static inline int is_zero_pos(Pos2 *p) {
    return p->x == 0 && p->z == 0;
}

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


int func_800173EC(unsigned short index_a, unsigned short index_b, Pos2 *out, short *side) {
    register Zone *a asm("$16");
    Zone *b;
    Zone rel;
    Vector v;
    unsigned short angle;
    int s;
    int c;
    unsigned short count;
    int shift;

    a = &D_800C62B0[index_a];
    b = &D_800C62B0[index_b];
    func_80016EE0(a, b, &rel);
    if (func_80017260(a, &rel) != 0) {
        return 0;
    }
    func_80016EE0(b, a, &rel);
    if (func_80017260(b, &rel) != 0) {
        return 0;
    }
    angle = b->angle;
    s = sine_lookup(angle) >> 4;
    c = cosine_lookup(angle) >> 4;
    count = 0;
    out->x = 0;
    out->z = 0;
    *side = 0;
    if (rel.cx < b->x0) {
        count = 1;
        out->x = -c;
        out->z = s;
        *side = 4;
    } else if (b->x1 < rel.cx) {
        count = 1;
        out->z = -s;
        out->x = c;
        *side = 3;
    }
    if (rel.cz < b->z0) {
        count++;
        out->x -= s;
        out->z -= c;
        *side = 2;
    } else if (b->z1 < rel.cz) {
        count++;
        out->x += s;
        out->z += c;
        *side = 1;
    }
    if (is_zero_pos(out)) {
        if (rel.cx < 0) {
            count++;
            out->x = -c;
            out->z = s;
            *side = 4;
        } else if (rel.cx > 0) {
            count++;
            out->z = -s;
            out->x = c;
            *side = 3;
        }
        if (rel.cz < 0) {
            count++;
            out->x -= s;
            out->z -= c;
            *side = 2;
        } else if (rel.cz > 0) {
            count++;
            out->x += s;
            out->z += c;
            *side = 1;
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
    return 1;
}
