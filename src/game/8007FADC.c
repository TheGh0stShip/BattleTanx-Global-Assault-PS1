typedef struct {
    short x;
    short y;
    short w;
    short h;
} RECT;

typedef struct {
    unsigned char level;
    char pad1;
    short width;
    short height;
} GpuDebug;

extern GpuDebug D_800B0C62;
extern int (*D_800B0C5C)(char *, ...);
extern char D_800C4BDC[];
extern char D_800C4BE8[];
extern char D_800C4BFC[];

void func_8007FADC(char *name, RECT *r) {
    switch (D_800B0C62.level) {
    case 1:
        if (r->w > D_800B0C62.width || r->w + r->x > D_800B0C62.width || r->y > D_800B0C62.height ||
            r->y + r->h > D_800B0C62.height || r->w <= 0 || r->x < 0 || r->y < 0 || r->h <= 0) {
            D_800B0C5C(D_800C4BDC, name);
            D_800B0C5C(D_800C4BE8, r->x, r->y, r->w, r->h);
        }
        break;
    case 2:
        D_800B0C5C(D_800C4BFC, name);
        D_800B0C5C(D_800C4BE8, r->x, r->y, r->w, r->h);
        break;
    }
}
