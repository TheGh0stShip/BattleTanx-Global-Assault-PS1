typedef struct {
    unsigned short height;
    unsigned short space;
    unsigned short blank;
    char pad6[2];
    void *glyphs;
    void *image;
} Font;
extern Font D_800E46C0[];
extern unsigned char D_800E4740;
extern short D_800E4744;
extern short func_80056B70(unsigned char, unsigned short, short, short, int, int, int);
extern unsigned char func_800229F8(void);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int round_fixed(int x) {
    return x >= 0 ? (x + 2048 >= 0 ? (x + 2048) >> 12 : -(-(x + 2048) >> 12))
                  : (x - 2048 >= 0 ? (x - 2048) >> 12 : -(-(x - 2048) >> 12));
}

int func_800577B4(unsigned char *str, unsigned short font, short x, int scale, int color, int flags) {
    short y = 0;
    unsigned char *text = str;
    Font *f = &D_800E46C0[font];
    unsigned char line_height;
    short width;
    short ypos;

    line_height = round_fixed(fixed_mul(color, f->height << 12));
    for (;;) {
        ypos = D_800E4744 + y;
        width = 0;
        while (*text != '\n' && *text != 0) {
            width += func_80056B70(*text++, font, x + width, ypos, scale, color, flags);
        }
        y += line_height;
        if (*text == 0) {
            if (D_800E4744 < -y) {
                return 1;
            }
            if (D_800E4744 < 35 && D_800E4740 < 180) {
                D_800E4740++;
                break;
            }
            if (func_800229F8() == 0) {
                D_800E4744--;
            }
            break;
        }
        text++;
    }
    return 0;
}
