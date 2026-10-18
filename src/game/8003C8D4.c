typedef struct { int pad[3]; int size; char rest[56]; } File;
typedef struct { char pad[0x1C]; int count; } Level;
extern int D_800A48DC;
extern void *D_800DDDEC;
extern void *D_800DDDF0;
extern char D_800BEA74[];
extern char D_800BEA7C[];
extern char *D_800A48E0[];
extern int D_800D3028;
extern void *D_800D3258;
extern void *D_800E53F4;
extern void *D_800A48D8;
extern void *D_800A48D4;
extern Level *D_800D2FE4;
extern void *D_800D2E00;
extern void func_80068F9C(void *);
extern void *func_80068DA4(int);
extern void func_8008DA04(char *, char *);
extern void func_8008D954(char *, char *);
extern void func_80082424(File *, char *);
extern int func_80082854(File *, void *, int);
extern void func_800826A0(File *);
extern void func_80023020(void);
extern void func_80024648(void);
extern void func_8005A914(void);
extern void func_8003BDB4(void);

static inline void read_file(char *path, void *buf)
{
    File file;
    int size;
    int n;

    do {
        func_80082424(&file, path);
        size = file.size;
        n = func_80082854(&file, buf, size);
        func_800826A0(&file);
    } while (n != size);
}

void func_8003C8D4(void)
{
    char path[104];
    void *buf;

    if (D_800A48DC != 0) {
        if (D_800DDDEC != 0) {
            func_80068F9C(D_800DDDEC);
        }
        D_800DDDEC = 0;
        func_8008DA04(path, D_800BEA74);
        func_8008D954(path, D_800A48E0[D_800D3028]);
        func_8008D954(path, D_800BEA7C);
        buf = D_800DDDF0;
        read_file(path, buf);
        func_80023020();
        func_80024648();
        func_8005A914();
    } else {
        func_8003BDB4();
        D_800D3258 = func_80068DA4(0x10000);
        func_80023020();
        func_80024648();
        D_800E53F4 = func_80068DA4(0x19000);
        func_8005A914();
        func_80068F9C(D_800A48D8);
        func_80068F9C(D_800A48D4);
        D_800D2E00 = func_80068DA4(D_800D2FE4->count * 4);
    }
}
