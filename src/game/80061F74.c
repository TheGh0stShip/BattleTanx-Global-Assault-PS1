typedef struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Color;

typedef struct Rgb {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Rgb;

typedef struct Blip {
    short x;
    short y;
    unsigned short flags;
    short pad;
} Blip;

typedef struct BlipList {
    Blip blips[42];
} BlipList;

extern int D_800ABA64;
extern int D_800E47F4;
extern signed char D_800A606C;
extern char D_800AB2B8[];
extern unsigned char D_800ABA60[];
extern BlipList D_800E4D70[];
extern Rgb D_800ABA6C[];
extern void func_800550F4(int, int, Color *);
extern void func_800552A4(int, int, Color *);

static inline unsigned short screen_player(char *menu) {
    if (D_800A606C == 1) {
        return 0;
    }
    if (D_800A606C == 2) {
        return menu != D_800AB2B8;
    }
    return 0;
}

void func_80061F74(char *menu) {
    int player;
    int p;
    unsigned char i;
    Color color;
    Blip *blip;

    D_800ABA64 -= D_800E47F4;
    if (D_800ABA64 < -0xA000) {
        D_800ABA64 += 0x14000;
    }
    p = screen_player(menu);
    if (D_800ABA60[p] != 0) {
        player = p;
        for (i = 0; i < D_800ABA60[player]; i++) {
            blip = (Blip *)((char *)D_800E4D70 + (i * 8 + player * 336));
            __asm__("" : "=r"(player) : "0"(player));
            if ((blip->flags & 0x100) && D_800ABA64 > 0) {
                continue;
            }
            color.r = D_800ABA6C[blip->flags & 0xF].r;
            color.g = D_800ABA6C[blip->flags & 0xF].g;
            color.b = D_800ABA6C[blip->flags & 0xF].b;
            color.a = 254;
            switch (blip->flags & 0xF0) {
            case 0:
                func_800550F4(blip->x, blip->y, &color);
                break;
            case 16:
            case 32:
                func_800552A4(blip->x, blip->y, &color);
                break;
            }
        }
    }
}
