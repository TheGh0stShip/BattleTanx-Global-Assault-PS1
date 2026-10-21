typedef struct {
    unsigned short tpage;
    unsigned short clut;
    unsigned char u;
    unsigned char v;
    unsigned char w;
    unsigned char h;
} Image;

typedef struct {
    short x;
    short y;
    short w;
    short h;
} SpriteRect;

typedef struct {
    int unk0;
    unsigned short frame;
    short pad6;
    Image **images;
    SpriteRect *rects;
} Sprite;

void func_80056160(Image *img, short x, short y, int scale_x, int scale_y, unsigned char *color);
void func_80056550(Image *img, short x, short y, short left, short top, short right, short bottom,
                   int scale_x, int scale_y, unsigned char *color);

void func_80056914(Sprite *sprite, short x, short y, int scale_x, int scale_y, unsigned char *color)
{
    Image **images;
    Image *image;

    if (sprite->rects == 0) {
        images = sprite->images;
        image = images[sprite->frame];
        func_80056160(image, x, y, scale_x, scale_y, color);
    } else {
        SpriteRect *rect;

        images = sprite->images;
        rect = &sprite->rects[sprite->frame];
        image = images[0];
        func_80056550(image, x, y, rect->x, rect->y, rect->x + rect->w, rect->y + rect->h,
                      scale_x, scale_y, color);
    }
}
