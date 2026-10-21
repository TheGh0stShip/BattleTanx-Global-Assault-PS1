typedef struct {
    unsigned short u;
    unsigned short v;
    unsigned short w;
} Glyph;
typedef struct {
    unsigned short height;
    unsigned short space;
    unsigned short blank;
    char pad6[2];
    Glyph *glyphs;
    void *image;
} Font;
extern Font D_800E46C0[];
extern unsigned short D_800A5FEC;
typedef struct {
    char pad0[0xBC];
    short width;
} Video;
extern Video D_800DDB9C;
extern unsigned short func_80056A40(unsigned char);
extern void func_80056550(void *, short, short, short, short, short, short, int, int, int);
extern int func_80056B70(unsigned char, unsigned short, short, short, int, int, int);

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

int func_80056E48(unsigned char *text, unsigned short font, short x, short y0, int scale_x, int scale_y,
                  unsigned short width, unsigned short align, short max_chars, int color) {
    Font *f = &D_800E46C0[font];
    unsigned char *line = text;
    short y = y0;
    short shown = 0;
    short count;
    short brk;
    short adv;
    short brk_w;
    short total;
    unsigned short newline;
    short draw;
    short pos;
    unsigned short i;
    unsigned short index;

    while (*text != 0) {
        count = 0;
        brk = 0;
        adv = 0;
        brk_w = 0;
        total = 0;
        while (*text == ' ') {
            text++;
            line++;
            shown++;
        }
        newline = 0;
        if (total < width) {
            __asm__("" : "+r"(newline));
            do {
                if (*text == 0 || (max_chars >= 0 && shown + count >= max_chars)) {
                    brk = count;
                    brk_w = total;
                    break;
                }
                if (*text == ' ') {
                    brk = count;
                    brk_w = total;
                    if (D_800DDB9C.width == 512) {
                        adv = round_fixed(fixed_mul(scale_x, fixed_mul(6553, f->blank << 12)));
                    } else {
                        adv = round_fixed(fixed_mul(scale_x, f->blank << 12));
                    }
                    total += adv;
                } else if (*text == 10 || *text == '<') {
                    brk = count;
                    brk_w = total;
                    newline = 1;
                    break;
                } else {
                    index = func_80056A40(*text);
                    if (index != 0xFFFF && f->glyphs[index].w != 0) {
                        if (D_800DDB9C.width == 512) {
                            adv = round_fixed(fixed_mul(scale_x, fixed_mul(6553, f->blank << 12)));
                        } else {
                            adv = round_fixed(fixed_mul(scale_x, f->blank << 12));
                        }
                        total += adv;
                    }
                }
                text++;
                count++;
            } while (total < width);
        }
        draw = brk;
        if (brk == 0) {
            draw = count - 1;
            if (draw < 0) {
                text++;
                if (newline == 0) {
                    return 0;
                }
                line++;
                y += round_fixed(fixed_mul(scale_y, f->height << 12));
                continue;
            }
            brk_w = total - adv;
        }
        switch (align) {
        case 0:
            pos = x;
            break;
        case 1:
            pos = x + (width - brk_w);
            break;
        case 2:
        default:
            pos = x + ((width - brk_w) >> 1);
            break;
        }
        for (i = 0; i < draw; i++) {
            pos += func_80056B70(*line++, font, pos, y, scale_x, scale_y, color);
        }
        shown += draw;
        if (*text == 0 && total < width) {
            return 1;
        }
        if (brk != 0) {
            line++;
            shown++;
        }
        if (max_chars >= 0 && max_chars < shown) {
            return 0;
        }
        text = line;
        y += round_fixed(fixed_mul(scale_y, f->height << 12));
    }
    return 1;
}
