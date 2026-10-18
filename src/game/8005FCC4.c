typedef struct Point16 {
    short x;
    short y;
} Point16;

typedef struct Layout {
    Point16 pos;
    char pad[0x58];
} Layout;

typedef struct Coords {
    short pad;
    short x;
    short y;
} Coords;

extern int D_800A48AC;
extern int D_800A48B0;
typedef struct Screen {
    Layout entries[3];
    char pad[0x14];
} Screen;

extern Screen D_800DDB9C[];
extern int D_800AACF8;
extern void func_8007FCE8(void *, int, int);
extern void func_8007FA74(int);

void func_8005FCC4(int unused, Coords *offset) {
    Screen *screen;
    Layout *layout;

    screen = &D_800DDB9C[D_800A48B0];
    layout = &screen->entries[D_800A48AC];
    func_8007FCE8(&D_800AACF8, layout->pos.x + offset->x, layout->pos.y + offset->y);
    func_8007FA74(0);
}
