typedef struct {
    int x0;
    int z0;
    int x1;
    int z1;
} Rect;

typedef struct {
    int x0;
    int z0;
    int x1;
    int z1;
    int x2;
    int z2;
} Tri;

typedef struct {
    char pad0[0x2C];
    Rect box;
    char pad3C[0x48 - 0x3C];
} Item;

typedef struct {
    char pad0[0x1C];
    int count;
    Item *items;
} Level;

extern Rect D_800D2E04;
extern int *D_800D2E00;
extern Level *D_800D2FE4;

static inline int overlaps(Rect *b, Rect *r) {
    int hit = 0;

    if ((b->x1 >> 12) >= r->x0 && r->x1 >= (b->x0 >> 12) && (b->z1 >> 12) >= r->z0) {
        hit = r->z1 >= (b->z0 >> 12);
    }
    return hit;
}

int func_8001F6D4(Tri *t) {
    Rect *bounds = &D_800D2E04;
    Rect *r;
    Item *items;
    int found;
    int i;

    bounds->x1 = (t->x2 > t->x0 ? (t->x2 > t->x1 ? t->x2 : t->x1) : (t->x0 > t->x1 ? t->x0 : t->x1));
    bounds->x0 = (t->x2 < t->x0 ? (t->x2 < t->x1 ? t->x2 : t->x1) : (t->x0 < t->x1 ? t->x0 : t->x1));
    bounds->z1 = (t->z2 > t->z0 ? (t->z2 > t->z1 ? t->z2 : t->z1) : (t->z0 > t->z1 ? t->z0 : t->z1));
    bounds->z0 = (t->z2 < t->z0 ? (t->z2 < t->z1 ? t->z2 : t->z1) : (t->z0 < t->z1 ? t->z0 : t->z1));
    found = 0;
    r = &D_800D2E04;
    items = D_800D2FE4->items;
    for (i = D_800D2FE4->count - 1; i >= 0; i--) {
        if (overlaps(&items[i].box, r)) {
            D_800D2E00[found] = i;
            found++;
        }
    }
    return found;
}
