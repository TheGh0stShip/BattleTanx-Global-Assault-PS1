typedef struct {
    void *fn[6];
    void (*sync)(int);
} GpuOps;

extern unsigned char D_800B0C62;
extern int (*D_800B0C5C)(char *, ...);
extern GpuOps *D_800B0C58;
extern volatile int *D_800B0D38;
extern volatile int *D_800B0D44;
extern int D_800B0D6C;
extern int D_800B0D70;
extern char D_800C4C6C[];

extern int func_80088870(int);
extern int func_80081B5C(void);
extern void func_80094450(int, void (*)(void));
extern void func_80081E3C(void);

int func_80081D40(int arg)
{
    if (D_800B0C62 >= 2) {
        D_800B0C5C(D_800C4C6C, arg);
    }
    D_800B0D6C = func_80088870(-1) + 240;
    D_800B0D70 = 0;
    while ((*D_800B0D44 & 0x01000000) || !(*D_800B0D38 & 0x04000000)) {
        if (func_80081B5C()) {
            return -1;
        }
    }
    func_80094450(2, func_80081E3C);
    D_800B0C58->sync(arg);
    return 0;
}
