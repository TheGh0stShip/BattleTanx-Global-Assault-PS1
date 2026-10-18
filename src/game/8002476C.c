typedef struct {
    short x0;
    short y0;
    short x1;
    short y1;
} Rect;

extern char *D_800D2FE4;

int func_8002476C(short x, short y) {
    Rect *r = (Rect *)(D_800D2FE4 + 0x14);

    if (x >= r->x0 && x <= r->x1 && y >= r->y0 && y <= r->y1) {
        return 1;
    }
    return 0;
}
