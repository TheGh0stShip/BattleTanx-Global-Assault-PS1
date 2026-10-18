typedef struct Image {
    char pad[6];
    unsigned char width;
    unsigned char height;
} Image;

typedef struct Screen {
    char pad[0x18];
    Image *image;
} Screen;

typedef struct Pos {
    short pad;
    short x;
    short y;
} Pos;

typedef struct Group {
    int pad;
    Pos *pos;
} Group;

typedef struct Entry {
    unsigned char kind;
    char pad1;
    short x;
    int pad2;
    int *value;
    char pad3[0x14];
} Entry;

extern Screen D_800C6290;
extern signed char D_800A606C;
extern Group D_800AAEB8;
typedef struct Menu {
    int pad;
    Entry *entries;
} Menu;

extern Menu D_800AB118;
extern int D_800AAF14;
extern short D_800ABA5C;
extern void func_80059550(void *, void *, int);

void func_80061E38(void) {
    Screen *screen;
    Entry *entry;

    screen = &D_800C6290;
    if (D_800A606C == 1) {
        D_800AAEB8.pos->x = 30;
        D_800AAEB8.pos->y = 208 - screen->image->height;
        for (entry = D_800AB118.entries; entry->kind != 0; entry++) {
            if (entry->value == &D_800AAF14) {
                entry->x = screen->image->width + 25;
                break;
            }
        }
    } else if (D_800A606C == 2) {
        D_800AAEB8.pos->x = 30;
        D_800AAEB8.pos->y = 120 - screen->image->height / 2;
    } else {
        D_800AAEB8.pos->x = 160 - screen->image->width / 2;
        D_800AAEB8.pos->y = 120 - screen->image->height / 2;
    }
    D_800ABA5C = 0;
    func_80059550(&D_800AAEB8, 0, 1);
}
