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

void func_8006F954(Source *src, Sprite *sprite, Bytes8 *color) {
    int scale;
    int random;

    sprite->color = *color;
    sprite->rx = 0;
    sprite->ry = 0;
    sprite->rz = 0;
    sprite->angle = 0;
    scale = 0x1E000;
    sprite->scale_x = scale;
    sprite->scale_y = scale;
    random = func_80086C84() >> 16;
    sprite->radius = (((random * 129) >> 16) + 128) * src->size / 4096;
    sprite->r = 128;
    sprite->g = 128;
    sprite->b = 128;
    sprite->visible = 1;
    sprite->mode = 3;
}
