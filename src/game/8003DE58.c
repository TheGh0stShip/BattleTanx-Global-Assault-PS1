typedef struct File {
    int fields00[3];
    int size;
    unsigned char fields10[56];
} File;

typedef char File_size[(sizeof(File) == 72) ? 1 : -1];

extern char D_800BEA74[];
extern char D_800BEA94[];
extern char *D_800A48E0[];
extern int D_800D3028;
extern void func_8008DA04(char *, char *);
extern void func_8008D954(char *, char *);
extern void func_80082424(File *, char *);
extern void *func_80068F34(int);
extern int func_80082854(File *, void *, int);
extern void func_800826A0(File *);

static inline void *load_file(char *path) {
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

void *func_8003DE58(void) {
    char path[104];

    func_8008DA04(path, D_800BEA74);
    func_8008D954(path, D_800A48E0[D_800D3028]);
    func_8008D954(path, D_800BEA94);
    return load_file(path);
}
