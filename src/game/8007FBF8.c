typedef struct {
    short x;
    short y;
    short w;
    short h;
} RECT;
typedef struct {
    char pad[8];
    int (*addque2)(void *func, void *param, int len, unsigned long arg);
    void *clr;
} GpuDriver;
extern GpuDriver *D_800B0C58;
extern char D_800C4C00[];
extern void func_8007FADC(char *name, RECT *rect);

int func_8007FBF8(RECT *rect, unsigned char r, unsigned char g, unsigned char b) {
    func_8007FADC(D_800C4C00, rect);
    return D_800B0C58->addque2(D_800B0C58->clr, rect, 8, (b << 16) | (g << 8) | r);
}
