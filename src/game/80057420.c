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

static inline short advance(unsigned short *width, int scale) {
    if (D_800DDB9C.width == 512) {
        return round_fixed(fixed_mul(scale, fixed_mul(6553, *width << 12)));
    }
    return round_fixed(fixed_mul(scale, *width << 12));
}

static inline int scaled_hires(int width, int scale) {
    return round_fixed(fixed_mul(scale, fixed_mul(6553, width << 12)));
}

static inline int scaled(int width, int scale) {
    return round_fixed(fixed_mul(scale, width << 12));
}

short func_80057420(unsigned char *str, unsigned short font, int scale) {
    Font *f = &D_800E46C0[font];
    short total = 0;
    unsigned char *text = str;
    unsigned short index;

    while (*text != 0) {
        if (D_800A5FEC != 0) {
            index = func_80056A40(*text);
            if (index != 0xFFFF && f->glyphs[index].w != 0) {
                if (D_800DDB9C.width == 512) {
                    total += scaled_hires(f->space, scale);
                } else {
                    total += scaled(f->space, scale);
                }
            }
            text++;
        } else if (*text == ' ') {
            total += advance(&f->blank, scale);
            text++;
        } else {
            index = func_80056A40(*text++);
            if (index != 0xFFFF && f->glyphs[index].w != 0) {
                total += advance(&f->glyphs[index].w, scale);
            }
        }
    }
    return total;
}
