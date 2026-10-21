typedef struct {
    unsigned short u;
    unsigned short v;
    unsigned short w;
} Glyph;
typedef struct {
    unsigned short height;
    unsigned short space;
    char pad4[4];
    Glyph *glyphs;
    void *image;
} Font;
extern Font D_800E46C0[];
extern unsigned short D_800A5FEC;
extern short D_800DDC58;
extern unsigned short func_80056A40(unsigned char);
extern void func_80056550(void *, short, short, short, short, short, short, int, int, int);

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

static inline short advance(int width, int scale) {
    if (D_800DDC58 == 512) {
        return round_fixed(fixed_mul(scale, fixed_mul(6553, width << 12)));
    }
    return round_fixed(fixed_mul(scale, width << 12));
}

short func_80056B70(unsigned char c, unsigned short font, short x, short y, int scale, int color, int flags) {
    Font *f = &D_800E46C0[font];
    unsigned short index;
    Glyph *g;
    unsigned short u;
    unsigned short v;
    unsigned short w;
    short right;
    short bottom;

    if (c == ' ') {
        return advance(D_800A5FEC != 0 ? f->space : f->glyphs->w, scale);
    }
    index = func_80056A40(c);
    if (index == 0xFFFF || (w = f->glyphs[index].w) == 0) {
        return 0;
    }
    g = &f->glyphs[index];
    u = g->u;
    v = g->v;
    right = u + w;
    bottom = v + f->height;
    func_80056550(f->image, x, y, u, v, right, bottom, scale, color, flags);
    return advance(D_800A5FEC != 0 ? f->space : f->glyphs[index].w, scale);
}
