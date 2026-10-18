typedef struct {
    short x0;
    short y0;
    short x1;
    short y1;
} Rect;

extern char *D_800D2FE4;

int func_800248CC(short x, short y) {
    Rect *r = (Rect *)(D_800D2FE4 + 0xC);

    if (x >= r->x0 && x <= r->x1 && y >= r->y0 && y <= r->y1) {
        return 1;
    }
    return 0;
}
