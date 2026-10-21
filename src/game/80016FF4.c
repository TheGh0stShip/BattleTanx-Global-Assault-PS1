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


void func_80016FF4(Zone *zone, Pos2 *out) {
    int s;
    int c;
    int ns;

    s = sine_lookup(zone->angle) >> 4;
    c = cosine_lookup(zone->angle) >> 4;
    out[0].x = (c * zone->x0 + s * zone->z0 + (zone->cx << 12)) << 2;
    ns = -s;
    out[0].z = (ns * zone->x0 + c * zone->z0 + (zone->cz << 12)) << 2;
    out[1].x = (c * zone->x0 + s * zone->z1 + (zone->cx << 12)) << 2;
    out[1].z = (ns * zone->x0 + c * zone->z1 + (zone->cz << 12)) << 2;
    out[2].x = (c * zone->x1 + s * zone->z1 + (zone->cx << 12)) << 2;
    out[2].z = (ns * zone->x1 + c * zone->z1 + (zone->cz << 12)) << 2;
    out[3].x = (c * zone->x1 + s * zone->z0 + (zone->cx << 12)) << 2;
    out[3].z = (ns * zone->x1 + c * zone->z0 + (zone->cz << 12)) << 2;
}
