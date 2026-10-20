typedef struct File {
    int fields00[3];
    int size;
    unsigned char fields10[56];
} File;

typedef struct Image {
    unsigned char fields00[8];
    unsigned short x;
    unsigned short y;
} Image;

typedef struct Texture {
    int width;
    int height;
    unsigned int mode;
    int *pixels;
    int size;
    int clut_count;
    int *clut;
    int clut_size;
    Image *image;
    Image *clut_image;
} Texture;

typedef struct Quad {
    short page;
    short clut;
    unsigned char u0;
    unsigned char v0;
    unsigned char u1;
    unsigned char v1;
    unsigned char u2;
    unsigned char v2;
    unsigned char u3;
    unsigned char v3;
} Quad;

typedef struct Reader {
    int *cursor;
    unsigned int count;
    Quad *current;
    Quad *output;
    int *file;
    unsigned int magic;
} Reader;

typedef char File_size[(sizeof(File) == 72) ? 1 : -1];
typedef char Texture_size[(sizeof(Texture) == 40) ? 1 : -1];
typedef char Quad_size[(sizeof(Quad) == 12) ? 1 : -1];
typedef char Reader_size[(sizeof(Reader) == 24) ? 1 : -1];

extern char D_800BF090[];
extern void func_8008DA04(char *, char *);
extern void func_8008D954(char *, char *);
extern void func_80082424(File *, char *);
extern int *func_80068F34(int);
extern Quad *func_80068DA4(unsigned int);
extern void func_80082854(File *, void *, int);
extern void func_800826A0(File *);
extern void func_80068F9C(void *);
extern void func_8003CB80(int **, Texture *, unsigned int);
extern short func_8008DA54(int, int, int, int);
extern short func_8008DA90(int, int);

static inline void build_path(char *path, char *name) {
    func_8008DA04(path, name);
    func_8008D954(path, D_800BF090);
}

static inline int *load_file(File *file, char *path) {
    int size;
    int *data;

    func_80082424(file, path);
    size = file->size;
    data = func_80068F34(size);
    func_80082854(file, data, size);
    func_800826A0(file);
    return data;
}

static inline void set_quad(Quad *quad, int mode, unsigned short x, short y,
                           int clut_x, int clut_y, unsigned short u,
                           unsigned short v, unsigned char width,
                           unsigned char height) {
    unsigned int first_u;
    unsigned int last_u;
    unsigned int last_v;

    quad->page = func_8008DA54(mode, 0, x, y);
    quad->clut = func_8008DA90(clut_x, clut_y);
    first_u = (u & 0x3F) << (2 - mode);
    last_u = first_u + width - 1;
    last_v = v + height - 1;
    quad->u0 = first_u;
    quad->v0 = v;
    quad->u1 = last_u;
    quad->v1 = v;
    quad->u2 = first_u;
    quad->v2 = last_v;
    quad->u3 = last_u;
    quad->v3 = last_v;
}

Quad *func_8003CCE8(char *name) {
    Texture texture;
    char path[64];
    File file;
    Reader reader;
    unsigned int i;

    build_path(path, name);
    reader.file = load_file(&file, path);
    reader.cursor = reader.file;
    reader.magic = *reader.cursor++;
    reader.count = *reader.cursor++;
    reader.output = func_80068DA4(reader.count * sizeof(Quad));
    reader.current = reader.output;
    for (i = 0; i < reader.count; i++) {
        func_8003CB80(&reader.cursor, &texture, reader.magic);
        set_quad(reader.current, texture.mode, texture.image->x,
                 (short)texture.image->y, texture.clut_image->x,
                 texture.clut_image->y, texture.image->x, texture.image->y,
                 texture.width, texture.height);
        reader.current++;
    }
    func_80068F9C(reader.file);
    return reader.output;
}
