typedef struct {
    int x0;
    int y0;
    int x1;
    int y1;
} Rect;
typedef struct {
    char pad0[0x14];
    unsigned short bounds[4];
} Map;
typedef struct {
    int x;
    int y;
} Point;
typedef struct {
    char pad0[8];
    int x;
    int y;
    int z;
} Object;
extern Map *D_800D2FE4;

static inline Rect map_bounds(void) {
    Rect r;
    unsigned short *b = D_800D2FE4->bounds;

    r.x0 = (short)(b[0] + 100) << 14;
    r.y0 = (short)(b[1] + 100) << 14;
    r.x1 = (short)(b[2] - 100) << 14;
    r.y1 = (short)(b[3] - 100) << 14;
    return r;
}

void func_8004332C(Object *obj, Point *origin, Point *size) {
    Rect r;
    int d;

    do { } while (0);
    r = map_bounds();

    origin->x = obj->x - 0xC80000;
    origin->y = obj->z - 0xC80000;
    size->x = 0x1900000;
    size->y = 0x1900000;
    d = r.x0 - origin->x;
    if (d > 0) {
        origin->x += d;
    } else {
        d = r.x1 - 0x1900000;
        d -= origin->x;
        if (d < 0) {
            origin->x += d;
        }
    }
    d = r.y0 - origin->y;
    if (d > 0) {
        origin->y += d;
    } else {
        d = r.y1 - (origin->y + 0x1900000);
        if (d < 0) {
            origin->y += d;
        }
    }
}
