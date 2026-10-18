typedef struct {
    unsigned long tag;
    unsigned char r0;
    unsigned char g0;
    unsigned char b0;
    unsigned char code;
    short x0;
    short y0;
    short w;
    short h;
} TILE;
typedef struct {
    unsigned long tag;
    unsigned long code[1];
} DR_MODE;
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

void func_80054F8C(int x, int y, int w, int h, unsigned char *color) {
    DR_MODE *mode;
    TILE *tile;
    unsigned long *ot;

    mode = func_80068EE8(sizeof(DR_MODE));
    ((unsigned char *)mode)[3] = 1;
    mode->code[0] = 0xE1000200;
    tile = func_80068EE8(sizeof(TILE));
    if (tile == 0) {
        return;
    }
    ((unsigned char *)tile)[3] = 3;
    tile->code = 0x60;
    tile->r0 = color[0];
    tile->g0 = color[1];
    tile->b0 = color[2];
    tile->x0 = x;
    tile->y0 = y;
    tile->w = w;
    tile->h = h;
    if (color[3] < 255) {
        tile->code |= 2;
    }
    ot = D_800D5B8C[D_800A48B4].ot;
    ((P_TAG *)tile)->addr = ((P_TAG *)ot)->addr;
    ((P_TAG *)ot)->addr = (unsigned long)tile;
    ((P_TAG *)mode)->addr = ((P_TAG *)ot)->addr;
    ((P_TAG *)ot)->addr = (unsigned long)mode;
}
