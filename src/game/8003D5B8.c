typedef struct { int pad[3]; int size; char rest[56]; } File;
typedef struct { int offset; int *f4; char *data; } Entry;
typedef struct { int pad0; char *f4; } Blob;
typedef struct { int width; int height; int type; int *pixels; unsigned int size; char pad[20]; } Image;
typedef struct { int pad0; unsigned int count; int data[1]; } ImageFile;

extern char D_800BEA74[];
extern char D_800BEA8C[];
extern char D_800BF098[];
extern char D_800BF0A4[];
extern char D_800BF0B0[];
extern char D_800BF0B8[];
extern char D_800BF0C0[];
extern char *D_800A48E0[];
typedef struct { char pad[68]; int level; } World;
extern World D_800D2FE4;
extern unsigned int D_800A4B10;
extern Entry *D_800A4B14;
extern unsigned int D_800A4B18;
extern Entry *D_800A4B1C;
extern Entry *D_800D2E14[];
extern void func_8008DA04(char *, char *);
extern void func_8008D954(char *, char *);
extern void func_80082424(File *, char *);
extern void *func_80068F34(int);
extern void *func_80068DA4(int);
extern void func_80082854(File *, void *, int);
extern void func_800826A0(File *);
extern Image *func_8003D0CC(void *);
extern void func_8003D1C0(char *, Image *, char *, Image *);
extern char *func_8003D4B4(char *, Image *);
extern void func_80068F9C(void *);
extern Entry *func_8003BF88(char *, unsigned int *);

static inline void *load_file(char *path)
{
    File file;
    int size;
    void *data;

    func_80082424(&file, path);
    size = file.size;
    data = func_80068F34(size);
    func_80082854(&file, data, size);
    func_800826A0(&file);
    return data;
}

static inline int *load_pack(char *path)
{
    File file;
    int size;
    int *data;

    func_80082424(&file, path);
    size = file.size;
    data = func_80068DA4(size);
    func_80082854(&file, data, size);
    func_800826A0(&file);
    return data;
}

static inline void parse_image(Image *out_arg, int **cursor)
{
    register Image *out asm("$4") = out_arg;
    int *p;
    int width;
    int height;
    unsigned int type;

    p = *cursor;
    width = *p++;
    out->width = width;
    height = *p++;
    out->height = height;
    type = *p++;
    out->pixels = p;
    out->type = type;
    switch (type) {
    case 0:
        out->size = (width / 2) * height;
        p += out->size >> 2;
        break;
    case 1:
        out->size = width * height;
        p += out->size >> 2;
        break;
    case 2:
        out->size = width * (height << 1);
        p += out->size >> 2;
        break;
    }
    *cursor = p;
}

static inline void parse_images(Image *out, ImageFile *file)
{
    int *cursor;
    unsigned int count;
    unsigned int i;
    register Image *o asm("$4");

    cursor = (int *)&file->count;
    count = *cursor++;
    i = 0;
    if (i < count) {
        o = out;
        do {
            parse_image(o, &cursor);
            o++;
            i++;
        } while (i < count);
    }
}

static inline void relocate(char *name, Entry **dst, Entry *entries, char *base)
{
    char path[64];
    int *p;
    int count;
    int i;
    int n;
    int j;

    *dst = entries;
    func_8008DA04(path, name);
    func_8008D954(path, D_800BEA8C);
    p = load_pack(path);
    p++;
    count = *p++;
    for (i = 0; i < count; i++) {
        entries[i].f4 = p;
        p++;
        n = *p++;
        if (n != 0) {
            for (j = 0; j < n; j++) {
                *p = (int)(base + *p * 20);
                p++;
            }
        } else {
            entries[i].f4 = 0;
        }
    }
}

void func_8003D5B8(void)
{
    char path[104];
    Blob *plt_a;
    ImageFile *img_a;
    Blob *plt_b;
    ImageFile *img_b;
    char *pal_a;
    char *pal_b;
    Image *images_a;
    Image *images_b;
    char *base_a;
    char *base_b;
    Entry *entries;
    int i;

    func_8008DA04(path, D_800BEA74);
    func_8008D954(path, D_800BF098);
    plt_a = load_file(path);
    pal_a = plt_a->f4;
    func_8008DA04(path, D_800BEA74);
    func_8008D954(path, D_800BF0A4);
    img_a = load_file(path);
    func_8008DA04(path, D_800BEA74);
    func_8008D954(path, D_800A48E0[D_800D2FE4.level]);
    func_8008D954(path, D_800BF0B0);
    plt_b = load_file(path);
    pal_b = plt_b->f4;
    func_8008DA04(path, D_800BEA74);
    func_8008D954(path, D_800A48E0[D_800D2FE4.level]);
    func_8008D954(path, D_800BF0B8);
    img_b = load_file(path);
    images_a = func_8003D0CC(plt_a);
    images_b = func_8003D0CC(plt_b);
    parse_images(images_a, img_a);
    parse_images(images_b, img_b);
    func_8003D1C0(pal_a, images_a, pal_b, images_b);
    base_a = func_8003D4B4(pal_a, images_a);
    base_b = func_8003D4B4(pal_b, images_b);
    func_80068F9C(img_a);
    func_80068F9C(plt_a);
    func_80068F9C(images_a);
    func_80068F9C(img_b);
    func_80068F9C(plt_b);
    func_80068F9C(images_b);

    func_8008DA04(path, D_800BF0C0);
    relocate(path, &D_800A4B1C, func_8003BF88(path, &D_800A4B18), base_a);
    for (i = 0; i < 107; i++) {
        if (D_800A4B1C[i].offset != 0 && i < D_800A4B18) {
            D_800D2E14[i] = &D_800A4B1C[i];
        } else {
            D_800D2E14[i] = 0;
        }
    }

    func_8008DA04(path, D_800BEA74);
    func_8008D954(path, D_800A48E0[D_800D2FE4.level]);
    relocate(path, &D_800A4B14, func_8003BF88(path, &D_800A4B10), base_b);
}
