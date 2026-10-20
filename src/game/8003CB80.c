typedef struct Texture {
    int width;
    int height;
    unsigned int mode;
    int *pixels;
    int size;
    int clut_count;
    int *clut;
    int clut_size;
    void *image;
    void *clut_image;
} Texture;

typedef char Texture_size[(sizeof(Texture) == 40) ? 1 : -1];

extern void func_8003CA54(Texture *);

void func_8003CB80(int **cursor, Texture *texture_arg, unsigned int magic) {
    register Texture *texture asm("$4") = texture_arg;
    int *words = *cursor;
    register int width asm("$8") = *words++;
    int height;
    register unsigned int mode asm("$5");

    texture->width = width;
    height = *words++;
    texture->height = height;
    {
        unsigned int raw_mode = *words++;
        texture->pixels = words;
        mode = raw_mode;
        asm("" : "+r"(mode));
        texture->mode = raw_mode;
    }
    switch (mode) {
    case 0:
        texture->size = (width / 2) * height;
        words += (unsigned int)texture->size >> 2;
        if (magic == 0x4C415033U)
            texture->clut_count = *words++;
        else
            texture->clut_count = 1;
        {
            register int elements asm("$3") = *(volatile int *)&texture->clut_count;
            register int bytes asm("$2") = *(volatile int *)&texture->clut_count;
            asm("" : : "r"(width));
            texture->clut = words;
            words += elements << 3;
            texture->clut_size = bytes << 5;
        }
        break;
    case 1:
        texture->size = width * height;
        words += (unsigned int)texture->size >> 2;
        if (magic == 0x4C415033U)
            texture->clut_count = *words++;
        else
            texture->clut_count = 1;
        {
            register int elements asm("$3") = *(volatile int *)&texture->clut_count;
            register int bytes asm("$2") = *(volatile int *)&texture->clut_count;
            asm("" : : "r"(width));
            texture->clut = words;
            words += elements << 7;
            texture->clut_size = bytes << 9;
        }
        break;
    case 2:
        {
            register int size asm("$3") = width * (height << 1);
            texture->clut_count = 0;
            texture->clut_size = 0;
            words += (unsigned int)size >> 2;
            texture->size = size;
        }
        break;
    }
    *cursor = words;
    if (texture->size != 0)
        func_8003CA54(texture);
}
