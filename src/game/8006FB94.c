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
    char pad14[2];
    short rx;
    short ry;
    short rz;
    char pad1C[3];
    unsigned char visible;
    short radius;
    char pad22[2];
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char mode;
} Sprite;

void func_8006FB94(Source *src, Sprite *sprite, Bytes8 *color) {
    int scale;

    sprite->color = *color;
    sprite->rx = 0;
    sprite->ry = 0;
    sprite->rz = 0;
    scale = src->size * 6;
    sprite->scale_x = scale;
    sprite->scale_y = scale;
    sprite->radius = src->size / 64;
    sprite->r = 64;
    sprite->g = 64;
    sprite->b = 64;
    sprite->visible = 1;
    sprite->mode = 5;
}
