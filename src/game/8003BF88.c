typedef struct { int pad[3]; int size; char rest[56]; } File;
typedef struct { int offset; int f4; char *data; } Entry;
typedef struct { int f0; unsigned int count; Entry entries[1]; } Pack;
extern char D_800BEA84[];
extern void func_8008DA04(char *, char *);
extern void func_8008D954(char *, char *);
extern void func_80082424(File *, char *);
extern Pack *func_80068DA4(int);
extern void func_80082854(File *, Pack *, int);
extern void func_800826A0(File *);

static inline Pack *load_file(char *path)
{
    File file;
    int size;
    Pack *pack;

    func_80082424(&file, path);
    size = file.size;
    pack = func_80068DA4(size);
    func_80082854(&file, pack, size);
    func_800826A0(&file);
    return pack;
}

Entry *func_8003BF88(char *name, unsigned int *count_out)
{
    char path[64];
    Pack *pack;
    Entry *entries;
    char *base;
    unsigned int count;
    unsigned int i;

    func_8008DA04(path, name);
    func_8008D954(path, D_800BEA84);
    pack = load_file(path);
    count = pack->count;
    entries = pack->entries;
    base = (char *)(entries + count);
    *count_out = count;
    for (i = 0; i < count; i++) {
        if (entries[i].offset != -1) {
            entries[i].data = base + entries[i].offset;
            entries[i].offset = (int)(entries[i].data + 36);
            entries[i].f4 = 0;
        } else {
            entries[i].data = 0;
            entries[i].offset = 0;
            entries[i].f4 = 0;
        }
    }
    return entries;
}
