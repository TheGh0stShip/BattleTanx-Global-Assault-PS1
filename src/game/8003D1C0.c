typedef struct {
    int w;
    int h;
    unsigned int mode;
    void *data;
    int size;
    int clut_count;
    void *clut;
    int clut_size;
    void *image;
    void *clut_image;
} Conv;
extern int D_800A48D4;
extern int D_800DE050;
extern int D_800DE05C;
extern int D_800DE060;
extern int D_800DE064;
extern void *func_8008D3B8(int, int, int, int, int);
extern void func_8008D8F4(void *, void *, int);

static inline void load_image(Conv *c)
{
    if (c->w != 0 && c->h != 0) {
        c->image = func_8008D3B8(D_800A48D4, c->w, c->h, c->mode, 12);
        if (c->image == 0) {
            D_800DE050 += c->size;
        }
        if (c->image != 0) {
            D_800DE060 += c->size;
            func_8008D8F4(c->image, c->data, 1);
        }
    }
}

static inline void load_clut(Conv *c)
{
    int clut_w;

    clut_w = c->mode == 1 ? 256 : (c->mode == 0 ? 16 : 0);
    if (clut_w != 0) {
        c->clut_image = func_8008D3B8(D_800A48D4, clut_w, c->clut_count, 2, 40);
        if (c->clut_image == 0) {
            D_800DE064 += c->clut_size;
        }
        if (c->clut_image != 0) {
            D_800DE05C += c->clut_size;
            func_8008D8F4(c->clut_image, c->clut, 1);
        }
    }
}

void func_8003D1C0(unsigned int count_a, Conv *a, unsigned int count_b, Conv *b)
{
    unsigned int i;

    for (i = 0; i < count_b; i++) {
        load_image(&b[i]);
    }
    for (i = 0; i < count_a; i++) {
        load_image(&a[i]);
    }
    for (i = 0; i < count_a; i++) {
        load_clut(&a[i]);
    }
    for (i = 0; i < count_b; i++) {
        load_clut(&b[i]);
    }
}
