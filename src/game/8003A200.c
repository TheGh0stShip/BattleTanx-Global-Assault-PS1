typedef struct { short x; short y; short w; short h; } Rect;
typedef struct { Rect clip; short ofs[2]; Rect tw; unsigned short tpage; unsigned char dtd; unsigned char dfe; unsigned char isbg; unsigned char r0; unsigned char g0; unsigned char b0; int dr_env[16]; } DrawEnv;
typedef struct { Rect disp; Rect screen; unsigned char isinter; unsigned char isrgb24; unsigned char pad0; unsigned char pad1; } DispEnv;
typedef struct { DrawEnv draw[2]; DispEnv disp; DrawEnv base; } Screen;
extern Screen D_800DDB9C[2];
extern int D_800C60CC;
extern int D_800A48A8;
extern int D_800A48AC;
extern int D_800A48B0;
extern short D_800D5B88;
extern Rect D_800BE7D4;
extern void func_8008BAD8(DispEnv *, int, int, int, int);
extern void func_8008BA24(DrawEnv *, int, int, int, int);
extern void func_8007FA74(int);
extern void func_8007FBF8(Rect *, int, int, int);
extern void func_8008B91C(int, int);
extern void func_8008B93C(int);
extern void func_8008B968(int, int);
extern void func_8008B9A4(int);

void func_8003A200(unsigned int mode)
{
    short w;
    short h;
    short half;
    short width;
    Rect rect;

    w = 512;
    h = 240;
    if (D_800C60CC == 1) {
        func_8008BAD8(&D_800DDB9C[0].disp, 512, 256, 512, 240);
        func_8008BAD8(&D_800DDB9C[1].disp, 0, 256, 512, 240);
        func_8008BA24(&D_800DDB9C[0].base, 0, 256, 512, 240);
        func_8008BA24(&D_800DDB9C[1].base, 512, 256, 512, 240);
    }
    switch (mode) {
    case 5:
        w = 320;
        func_8008BAD8(&D_800DDB9C[0].disp, 320, 256, 320, 240);
        func_8008BAD8(&D_800DDB9C[1].disp, 0, 256, 320, 240);
        func_8008BA24(&D_800DDB9C[0].base, 0, 256, 320, 240);
        func_8008BA24(&D_800DDB9C[1].base, 320, 256, 320, 240);
        D_800DDB9C[0].draw[0] = D_800DDB9C[0].base;
        D_800DDB9C[1].draw[0] = D_800DDB9C[1].base;
        rect = D_800BE7D4;
        func_8007FA74(0);
        func_8007FBF8(&rect, 0, 0, 0);
        break;
    case 1:
        D_800DDB9C[0].draw[0] = D_800DDB9C[0].base;
        D_800DDB9C[1].draw[0] = D_800DDB9C[1].base;
        break;
    case 2:
        width = D_800DDB9C[0].disp.disp.w;
        w = D_800DDB9C[0].disp.disp.w;
        half = D_800DDB9C[0].disp.disp.h / 2;
        h = half;
        func_8008BA24(&D_800DDB9C[0].draw[0], 0, 256, width, half);
        func_8008BA24(&D_800DDB9C[0].draw[1], 0, 256 + half, width, half);
        func_8008BA24(&D_800DDB9C[1].draw[0], 512, 256, width, half);
        func_8008BA24(&D_800DDB9C[1].draw[1], 512, 256 + half, width, half);
        break;
    }
    D_800A48AC = 0;
    D_800A48B0 = 1;
    func_8008B91C(w / 2, h / 2);
    func_8008B93C(600);
    func_8008B968(0, D_800D5B88);
    func_8008B9A4(512);
    D_800A48A8 = mode;
}
