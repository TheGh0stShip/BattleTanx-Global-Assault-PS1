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

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
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


static inline int zone_invalid(unsigned short index) {
    return index > 1300;
}

int func_8001A9B4(unsigned short index, unsigned short side, int margin, Pos2 *p0, Pos2 *p1) {
    Zone *zone;
    Pos2 q[2];
    int s;
    int c;
    int ns;

    if (zone_invalid(index)) {
        return 1;
    }
    zone = &D_800C62B0[index];
    switch (side) {
    case 1:
        {
            int a = (short)(zone->x0 - margin) << 14;
            int b = (short)(zone->z1 + margin) << 14;
            q[0].x = a;
            q[0].z = b;
            q[1].x = (short)(zone->x1 + margin) << 14;
            q[1].z = b;
        }
        break;
    case 2:
        {
            int a = (short)(zone->x1 + margin) << 14;
            int b = (short)(zone->z0 - margin) << 14;
            q[0].x = a;
            q[0].z = b;
            q[1].x = (short)(zone->x0 - margin) << 14;
            q[1].z = b;
        }
        break;
    case 4:
        {
            int a = (short)(zone->x0 - margin) << 14;
            int b = (short)(zone->z0 - margin) << 14;
            q[0].x = a;
            q[0].z = b;
            q[1].z = (short)(zone->z1 + margin) << 14;
            q[1].x = a;
        }
        break;
    case 3:
        {
            int a = (short)(zone->x1 + margin) << 14;
            int b = (short)(zone->z1 + margin) << 14;
            q[0].x = a;
            q[0].z = b;
            q[1].z = (short)(zone->z0 - margin) << 14;
            q[1].x = a;
        }
        break;
    default:
        return 1;
    }
    if (zone->angle == 0) {
        p0->x = q[0].x + (zone->cx << 14);
        p0->z = q[0].z + (zone->cz << 14);
        p1->x = q[1].x + (zone->cx << 14);
        p1->z = q[1].z + (zone->cz << 14);
        return 0;
    }
    s = sine_lookup(zone->angle) >> 4;
    c = cosine_lookup(zone->angle) >> 4;
    {
        int base = zone->cx << 14;
        int z = q[0].z;
        int x = q[0].x;
        p0->x = base + (fixed_mul(x, c) + fixed_mul(z, s));
    }
    ns = -s;
    {
        int base = zone->cz << 14;
        int z = q[0].z;
        int x = q[0].x;
        p0->z = base + (fixed_mul(x, ns) + fixed_mul(z, c));
    }
    {
        int base = zone->cx << 14;
        int z = q[1].z;
        int x = q[1].x;
        p1->x = base + (fixed_mul(x, c) + fixed_mul(z, s));
    }
    {
        int base = zone->cz << 14;
        int z = q[1].z;
        int x = q[1].x;
        p1->z = base + (fixed_mul(x, ns) + fixed_mul(z, c));
    }
    return 0;
}
