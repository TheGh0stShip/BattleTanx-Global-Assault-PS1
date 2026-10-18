typedef struct Bytes8 {
    unsigned char b[8];
} Bytes8;

typedef struct Source {
    char pad[0x1C];
    int size;
} Source;

typedef struct Sprite {
    int pad0;
    int scale_x;
    int scale_y;
    Bytes8 color;
    short angle;
    short rx;
    short ry;
    short rz;
    char pad1C[3];
    unsigned char visible;
    short radius;
    short drift;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char mode;
} Sprite;

extern unsigned int func_80086C84(void);

void func_8006F890(Source *src, Sprite *sprite, Bytes8 *color) {
    int scale;

    sprite->color = *color;
    sprite->rx = 0;
    sprite->ry = 0;
    sprite->rz = 0;
    sprite->angle = func_80086C84() >> 16;
    scale = 0x10000;
    sprite->scale_x = scale;
    sprite->scale_y = scale;
    sprite->radius = src->size * 304 / 4096;
    sprite->drift = -8;
    sprite->r = 255;
    sprite->g = 255;
    sprite->b = 255;
    sprite->visible = 1;
    sprite->mode = 0;
}
