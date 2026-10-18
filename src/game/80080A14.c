typedef struct {
    short x;
    short y;
    short w;
    short h;
} RECT;

unsigned long func_80080A14(RECT *tw) {
    unsigned long pat[4];

    if (tw != 0) {
        pat[0] = (tw->x & 0xFF) >> 3;
        pat[2] = (-tw->w & 0xFF) >> 3;
        pat[1] = (tw->y & 0xFF) >> 3;
        pat[3] = (-tw->h & 0xFF) >> 3;
        return 0xE2000000 | (pat[1] << 15) | (pat[0] << 10) | (pat[3] << 5) | pat[2];
    }
    return 0;
}
