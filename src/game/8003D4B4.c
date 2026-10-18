typedef struct { char pad[8]; unsigned short w; unsigned short h; } Img;
typedef struct {
    int f0;
    int f4;
    int mode;
    int fC;
    int f10;
    int f14;
    unsigned short *clut;
    int size;
    Img *src;
    Img *dst;
} Conv;
typedef struct { short f0; unsigned short flags; char pad[16]; } Tex;
extern Tex *func_80068DA4(int);
extern void func_8008BC74(Tex *, int, int, int, int, int, int);

Tex *func_8003D4B4(unsigned int count, Conv *conv)
{
    Tex *texs;
    Tex *t;
    unsigned int i;

    texs = func_80068DA4(count * sizeof(Tex));
    for (i = 0; i < count; i++) {
        func_8008BC74(&texs[i], conv[i].src->w, conv[i].src->h, conv[i].dst->w, conv[i].dst->h, conv[i].mode, 0);
        if (conv[i].mode != 2 && conv[i].clut[0] == 0) {
            texs[i].flags |= 0x8000;
        }
        if (conv[i].f14 == 0) {
            texs[i].flags |= 0x4000;
        }
    }
    return texs;
}
