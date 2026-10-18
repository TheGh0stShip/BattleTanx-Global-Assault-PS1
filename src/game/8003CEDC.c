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
typedef struct { short tpage; short clut; unsigned char u; unsigned char v; unsigned char w; unsigned char h; } TexInfo;
typedef struct { int *cursor; unsigned int count; int *base; int magic; } Reader;
extern char D_800BF090[];
extern int D_800DE0D4;
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
extern void func_8008BC74(int *, int, int, int, int, int, int);

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

static inline int read_word(Reader *r)
{
    return *r->cursor++;
}

static inline void set_tex(TexInfo *t, int mode, short tx, short ty, int cx, int cy,
                           unsigned short u, unsigned short v, unsigned char w, unsigned char h)
{
    t->tpage = func_8008DA54(mode, 0, tx, ty);
    t->clut = func_8008DA90(cx, cy);
    t->u = (u & 0x3F) << (2 - mode);
    t->v = v;
    t->w = w;
    t->h = h;
}

TexInfo *func_8003CEDC(char *name, TexInfo *out)
{
    Conv conv;
    char path[64];
    File file;
    int *cursor;
    unsigned int count;
    int *base;
    int magic;
    unsigned int i;

    build_path(path, name);
    base = load_file(&file, path);
    cursor = base;
    magic = *cursor++;
    count = *cursor++;
    for (i = 0; i < count; i++) {
        func_8003CB80(&cursor, &conv, magic);
        set_tex(out, conv.mode, conv.image->x, conv.image->y, conv.clut_image->x, conv.clut_image->y,
                conv.image->x, conv.image->y, conv.w, conv.h);
        out++;
    }
    func_8008BC74(&D_800DE0D4, conv.image->x, conv.image->y, conv.clut_image->x, conv.clut_image->y, conv.mode, 0);
    func_80068F9C(base);
    return out;
}
