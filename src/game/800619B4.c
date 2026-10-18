typedef struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Color;

typedef struct Rgb {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Rgb;

typedef struct Blip {
    short x;
    short z;
    unsigned short sprite;
    unsigned short flags;
} Blip;

typedef struct MapInfo {
    char pad00[6];
    unsigned char width;
    unsigned char height;
} MapInfo;

typedef struct Radar {
    char pad00[16];
    int scale_x;
    int scale_z;
    MapInfo *map;
} Radar;

typedef struct Center {
    char pad00[12];
    short x;
    short z;
} Center;

typedef struct Panel {
    char pad00[22];
    unsigned short x;
    unsigned short y;
} Panel;

typedef struct Offset {
    short pad00;
    short x;
    short y;
} Offset;

extern Color D_800BFE30;
extern unsigned short D_800ABA5C;
extern int D_800ABA64;
extern Rgb D_800ABA6C[];
extern Blip D_800E4BFC[];
extern Radar D_800C6290;
extern Center *D_800D2FE4;
extern void func_80055890(short x, short y, int sprite, Color *color);
extern void func_80054F8C(short x, short y, int w, int h, Color *color);
extern void func_80055C80(MapInfo *map, int x, int y, Color *color);

static inline int round_fixed(int v) {
    return v >= 0 ? (v + 2048 >= 0 ? (v + 2048) >> 12 : -(-(v + 2048) >> 12))
                  : (v - 2048 >= 0 ? (v - 2048) >> 12 : -(-(v - 2048) >> 12));
}

void func_800619B4(Panel *panel, Offset *offset) {
    Color frame;
    Color color;
    unsigned short i;
    short dx;
    short dz;
    short x;
    short y;
    Blip *blip;
    Radar *radar;

    radar = &D_800C6290;
    frame = D_800BFE30;
    for (i = 0; i < D_800ABA5C; i++) {
        dx = round_fixed(radar->scale_x * (D_800E4BFC[i].x - D_800D2FE4->x));
        dz = round_fixed(radar->scale_z * (D_800E4BFC[i].z - D_800D2FE4->z));
        blip = &D_800E4BFC[i];
        if ((blip->flags & 0x100) && D_800ABA64 > 0) {
            continue;
        }
        {
            short unit = 6553;

            if (dx < 0 || dx >= radar->map->width * unit) {
                continue;
            }
        }
        if (dz < 0 || dz >= radar->map->height) {
            continue;
        }
        x = dx + (panel->x + offset->x);
        y = dz + (panel->y + offset->y);
        color.r = D_800ABA6C[blip->flags & 0xF].r;
        color.g = D_800ABA6C[blip->flags & 0xF].g;
        color.b = D_800ABA6C[blip->flags & 0xF].b;
        color.a = 255;
        if (blip->flags & 0x8000) {
            func_80055890(x, y, blip->sprite, &color);
        } else if (blip->flags & 0x4000) {
            func_80054F8C(x - 1, y - 1, 3, 3, &color);
        } else {
            func_80054F8C(x, y, 2, 2, &color);
        }
    }
    func_80055C80(radar->map, offset->x, offset->y, &frame);
    D_800ABA5C = 0;
}
