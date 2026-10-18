typedef struct { int pad[3]; int size; char rest[56]; } File;
typedef struct { char pad[0x44]; int level; } Game;
extern Game D_800D2FE4;
extern int D_800D3028;
extern char *D_800A48E0[];
extern char *D_800A49F8[];
extern char D_800BEA54[];
extern char D_800BEA64[];
extern char D_800BEA74[];
extern char D_800BEA7C[];
extern int D_800E49A0;
extern int D_800DDDF8;
extern int D_800DE0CC;
extern int *D_800AAF34;
extern int D_800ADA04;
extern void *D_800DDDF0;
extern void func_8008DA04(char *, char *);
extern void func_8008D954(char *, char *);
extern void func_8003CEDC(char *, int *);
extern int func_8003CCE8(char *);
extern void func_8003D5B8(void);
extern void func_80082424(File *, char *);
extern void *func_80068DA4(int);
extern int func_80082854(File *, void *, int);
extern void func_800826A0(File *);

static inline void *load_file(char *path)
{
    File file;
    int size;
    void *buf;

    func_80082424(&file, path);
    size = file.size;
    buf = func_80068DA4(size);
    func_80082854(&file, buf, size);
    func_800826A0(&file);
    return buf;
}

int func_8003BDB4(void)
{
    File unused;
    char path[104];

    func_8008DA04(path, D_800BEA54);
    func_8008D954(path, D_800A48E0[D_800D2FE4.level]);
    func_8003CEDC(path, &D_800E49A0);
    D_800ADA04 = func_8003CCE8(D_800BEA64);
    func_8008DA04(path, D_800BEA74);
    func_8008D954(path, D_800A48E0[D_800D2FE4.level]);
    func_8003CEDC(path, &D_800DDDF8);
    if (D_800A49F8[D_800D2FE4.level] != 0) {
        func_8008DA04(path, D_800BEA74);
        func_8008D954(path, D_800A49F8[D_800D2FE4.level]);
        func_8003CEDC(path, &D_800DE0CC);
        D_800AAF34 = &D_800DE0CC;
    } else {
        D_800AAF34 = 0;
    }
    func_8003D5B8();
    func_8008DA04(path, D_800BEA74);
    func_8008D954(path, D_800A48E0[D_800D3028]);
    func_8008D954(path, D_800BEA7C);
    D_800DDDF0 = load_file(path);
    return 1;
}
