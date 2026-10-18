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
    char pad1C[2];
    signed char spin;
    unsigned char visible;
    short radius;
    short drift;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char mode;
} Sprite;

extern unsigned int func_80086C84(void);

void func_8006FCA4(Source *src, Sprite *sprite, Bytes8 *color) {
    int scale;
    int shade;

    sprite->color = *color;
    sprite->rx = ((int)(func_80086C84() >> 16) * 129 >> 16) - 64;
    sprite->ry = -96;
    sprite->rz = ((int)(func_80086C84() >> 16) * 129 >> 16) - 64;
    sprite->angle = func_80086C84() >> 16;
    sprite->spin = ((int)(func_80086C84() >> 16) * 257 >> 16) - 128;
    scale = 0x7FFFFFFF;
    sprite->scale_x = scale;
    sprite->scale_y = scale;
    sprite->radius = ((int)(func_80086C84() >> 16) * 5 >> 16) + 28;
    sprite->drift = 0;
    shade = ((int)(func_80086C84() >> 16) * 17 >> 16) + 80;
    sprite->b = shade;
    sprite->g = shade;
    sprite->r = shade;
    sprite->visible = 0;
    sprite->mode = 6;
}
