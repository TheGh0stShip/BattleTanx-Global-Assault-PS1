typedef struct { int pad[3]; int size; char rest[56]; } File;
typedef struct { char pad[8]; unsigned short x; unsigned short y; } Img;
typedef struct {
    int w;
    int h;
    int mode;
    int *data;
    unsigned int size;
    int clut_count;
    int *clut;
    int clut_size;
    Img *image;
    Img *clut_image;
} Conv;
typedef struct { short tpage; short clut; unsigned char u0; unsigned char v0; unsigned char u1; unsigned char v1; unsigned char u2; unsigned char v2; unsigned char u3; unsigned char v3; } TexQuad;
extern char D_800BF090[];
extern void func_8008DA04(char *, char *);
extern void func_8008D954(char *, char *);
extern void func_80082424(File *, char *);
extern int *func_80068F34(int);
extern void func_80068F9C(void *);
extern int func_80082854(File *, void *, int);
extern void func_800826A0(File *);
extern void func_8003CB80(int **, Conv *, int);
extern short func_8008DA54(int, int, int, int);
extern short func_8008DA90(int, int);
extern void *func_80068DA4(int);

static inline int *load_file(File *file, char *path)
{
    int size;
    int *buf;

    func_80082424(file, path);
    size = file->size;
    buf = func_80068F34(size);
    func_80082854(file, buf, size);
    func_800826A0(file);
    return buf;
}

static inline void build_path(char *path, char *name)
{
    func_8008DA04(path, name);
    func_8008D954(path, D_800BF090);
}

static inline void set_quad(TexQuad *t, int mode, short tx, short ty, int cx, int cy,
                            unsigned short u, int v, unsigned char w, unsigned char h)
{
    unsigned char u0, u1, v1;
    t->tpage = func_8008DA54(mode, 0, tx, ty);
    t->clut = func_8008DA90(cx, cy);
    u0 = (u & 0x3F) << (2 - mode);
    u1 = u0 + w - 1;
    v1 = v + h - 1;
    t->u0 = u0;
    t->v0 = v;
    t->u1 = u1;
    t->v1 = v;
    t->u2 = u0;
    t->v2 = v1;
    t->u3 = u1;
    t->v3 = v1;
}

TexQuad *func_8003CCE8(char *name)
{
    Conv conv;
    char path[64];
    File file;
    int *cursor;
    unsigned int count;
    TexQuad *out;
    TexQuad *result;
    int *base;
    int magic;
    unsigned int i;

    build_path(path, name);
    base = load_file(&file, path);
    cursor = base;
    magic = *cursor++;
    count = *cursor++;
    result = func_80068DA4(count * sizeof(TexQuad));
    out = result;
    for (i = 0; i < count; i++) {
        func_8003CB80(&cursor, &conv, magic);
        set_quad(out, conv.mode, conv.image->x, conv.image->y, conv.clut_image->x, conv.clut_image->y,
                 conv.image->x, conv.image->y, conv.w, conv.h);
        out++;
    }
    func_80068F9C(base);
    return result;
}
