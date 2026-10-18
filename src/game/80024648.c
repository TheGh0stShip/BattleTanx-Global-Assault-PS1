typedef struct {
    int pad0;
    int y;
    int x;
} Screen;

typedef struct {
    Screen *screen;
    char pad4[0x40];
    int mode;
} Globals;

typedef struct {
    short x;
    short y;
} Point;

extern Globals D_800D2FE4;
extern Point D_800A4398[];
extern int D_800A4750;
extern void func_80022A90(int *);
extern int func_80068F34(int);
extern void func_8002A30C(void);
extern int func_8002429C(int *, int, int);
extern void func_80068F9C(int);

void func_80024648(void) {
    int buffer;
    int scratch;

    func_80022A90(&buffer);
    scratch = func_80068F34(57);
    func_8002A30C();
    if (func_8002429C(&buffer, scratch, 57) >= 0) {
        D_800A4750 = 0;
        func_80068F9C(buffer);
        func_80068F9C(scratch);
        D_800D2FE4.screen->x = D_800A4398[D_800D2FE4.mode].y;
        D_800D2FE4.screen->y = D_800A4398[D_800D2FE4.mode].x;
    }
}
