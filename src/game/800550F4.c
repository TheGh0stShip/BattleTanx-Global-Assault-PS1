typedef struct {
    short vx;
    short vy;
    short vz;
    short pad;
} SVECTOR;
typedef struct {
    unsigned long tag;
    unsigned char r0;
    unsigned char g0;
    unsigned char b0;
    unsigned char code;
    short x0;
    short y0;
    short x1;
    short y1;
    short x2;
    short y2;
} POLY_F3;
typedef struct {
    unsigned addr : 24;
    unsigned len : 8;
} P_TAG;
typedef struct {
    unsigned long ot[0x4008 / 4];
} OrderingTable;
extern OrderingTable D_800D5B8C[];
extern int D_800A48B4;
extern void *func_80068EE8(int);

void func_800550F4(short x, short y, unsigned char *color) {
    SVECTOR shape[3];
    SVECTOR pt[3];
    POLY_F3 *poly;
    unsigned long *ot;
    SVECTOR *base = shape;

    shape[0].vx = 0;
    shape[0].vy = 0;
    shape[0].vz = 3;
    shape[1].vx = -6;
    shape[1].vy = 0;
    shape[1].vz = -3;
    shape[2].vx = 6;
    shape[2].vy = 0;
    shape[2].vz = -3;
    poly = func_80068EE8(sizeof(POLY_F3));
    if (poly == 0) {
        return;
    }
    ((unsigned char *)poly)[3] = 4;
    poly->code = 0x20;
    poly->r0 = color[0];
    poly->g0 = color[1];
    poly->b0 = color[2];
    if (color[3] < 255) {
        poly->code |= 2;
    }
    pt[0].vx = shape[0].vx + x;
    pt[1].vx = shape[1].vx + x;
    pt[2].vx = shape[2].vx + x;
    pt[0].vz = base->vz + y;
    pt[1].vz = shape[1].vz + y;
    pt[2].vz = shape[2].vz + y;
    poly->x0 = pt[0].vx;
    poly->y0 = pt[0].vz;
    poly->x1 = pt[1].vx;
    poly->y1 = pt[1].vz;
    poly->x2 = pt[2].vx;
    poly->y2 = pt[2].vz;
    ot = D_800D5B8C[D_800A48B4].ot;
    ((P_TAG *)poly)->addr = ((P_TAG *)ot)->addr;
    ((P_TAG *)ot)->addr = (unsigned long)poly;
}
