typedef struct GridConfig {
    char pad00[6];
    unsigned char scale_x;
    unsigned char scale_z;
} GridConfig;
typedef struct Grid {
    short x0;
    short z0;
    short width;
    short depth;
    unsigned short cols;
    unsigned short rows;
    unsigned short *cells;
    int scale_x;
    int scale_z;
    GridConfig *config;
} Grid;
typedef struct LevelBounds {
    char pad00[0xC];
    unsigned short x0;
    unsigned short z0;
    unsigned short x1;
    unsigned short z1;
} LevelBounds;
extern Grid D_800C6290;
extern int D_800A48DC;
extern GridConfig D_800E49A0;
extern LevelBounds *D_800D2FE4;
extern unsigned char D_800D2DFC;
extern int D_800D2DF8;
extern int D_800C60F4;
extern unsigned char D_800C62AC;
unsigned short *func_80024700(int);

static inline int imul(int a, int b) {
    return a * b;
}

void func_80015A80(int x0, int z0, int x1, int z1) {
    Grid *g = &D_800C6290;
    GridConfig *config;
    unsigned short count;
    unsigned short i;
    unsigned short *cell;
    int scale;
    unsigned short dx;
    unsigned short dz;

    x1 -= x0;
    g->cols = ((unsigned short)x1 >> 10) + 1;
    z1 -= z0;
    g->rows = ((unsigned short)z1 >> 10) + 1;
    count = g->cols * (g->rows << 2) + 1;
    D_800C6290.x0 = x0;
    g->z0 = z0;
    g->width = x1;
    g->depth = z1;
    if (D_800A48DC == 0) {
        g->cells = func_80024700(count * 2);
    }
    cell = g->cells;
    for (i = 0; i < count; i++) {
        *cell++ = 0xFFFF;
    }
    do {
        config = &D_800E49A0;
        dx = (unsigned short)(D_800D2FE4->x1 - D_800D2FE4->x0);
        scale = imul(config->scale_x, 6553) / dx;
        dz = (unsigned short)(D_800D2FE4->z1 - D_800D2FE4->z0);
        g->config = config;
        g->scale_x = scale;
        D_800D2DFC = g->config->scale_x;
        D_800C62AC = g->config->scale_z;
        D_800D2DF8 = dx;
        D_800C60F4 = dz;
        g->scale_z = (g->config->scale_z << 12) / dz;
    } while (0);
}
