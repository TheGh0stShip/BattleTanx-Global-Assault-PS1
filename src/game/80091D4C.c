typedef struct DispRect {
    short x;
    short y;
    short w;
    short h;
} DispRect;

typedef struct DispEnv {
    DispRect disp;
    DispRect screen;
    unsigned char isinter;
    unsigned char isrgb24;
    unsigned char pad0;
    unsigned char pad1;
} DispEnv;

typedef struct StrokeFont {
    unsigned int first;
    unsigned int last;
    int width;
    int height;
    unsigned char *data;
    unsigned short offsets[1];
} StrokeFont;

typedef struct TextCursor {
    int x;
    int y;
    unsigned int *tag;
} TextCursor;

extern TextCursor D_800EEE64;
extern StrokeFont D_800C55C0;
extern DispEnv *func_8008040C(DispEnv *env);
extern unsigned int *func_8007F7D8(void);
extern int func_8007F7F4(void);
extern void func_8007F7E8(void *next);
extern void func_8007FA74(int mode);
extern void func_8007FE4C(unsigned int *packet);

void func_80091D4C(unsigned int *ot, int x, int y, int color, int box, unsigned char *str) {
    unsigned int buf[18];
    DispEnv env;
    int start_x;
    int use_ot;
    int screen_w;
    int screen_h;
    unsigned int *base;
    unsigned int *start;
    unsigned int *tag;
    unsigned int *p;
    int count;
    int words;
    unsigned char c;
    unsigned char *glyph;
    int strokes;
    int points;
    int size;
    unsigned int code;
    unsigned int term;
    int width;
    int lines;
    int len;
    int top;
    unsigned char *s;
    StrokeFont *font;
    unsigned int b;
    int px;
    int py;

    font = &D_800C55C0;
    if (str == 0 || *str == 0) {
        return;
    }
    if (x == -1) {
        x = D_800EEE64.x;
    }
    if (y == -1) {
        y = D_800EEE64.y;
    }
    start_x = x;
    func_8008040C(&env);
    screen_w = env.disp.w;
    screen_h = env.disp.h;
    if (ot == 0) {
        words = sizeof(buf);
        start = buf;
        use_ot = 0;
    } else {
        start = func_8007F7D8();
        words = func_8007F7F4();
        use_ot = 1;
    }
    base = start;
    words >>= 2;
    if (words < 2) {
        return;
    }
    tag = start;
    p = tag + 1;
    count = 0;
    words -= 2;
    if (box != 0) {
        width = count;
        len = count;
        lines = count;
        for (s = str; *s != 0; s++) {
            if (*s == '\n') {
                if (width < len) {
                    width = len;
                }
                lines++;
                len = 0;
            } else {
                len++;
            }
        }
        if (lines == 0) {
            lines = 1;
        }
        if (width < len) {
            width = len;
        }
        len = width * ((unsigned int)(font->width * screen_w) / 320);
        lines *= (unsigned int)(font->height * screen_h) / 240;
        if (words >= 6) {
            *p++ = 0xE1000100;
            *p++ = 0x2A000000;
            len = x - -len;
            words -= 6;
            count += 6;
            top = y - 1;
            *p++ = (top << 16) + (x - 1);
            *p++ = (top << 16) + len;
            top += lines;
            *p++ = (top << 16) + (x - 1);
            *p++ = (top << 16) + len;
        }
    }
    while ((c = *str++) != 0) {
        if (c == '\n') {
            x = start_x;
            y += (unsigned int)(font->height * screen_h) / 240;
            continue;
        }
        if (c >= font->first && c <= font->last) {
            glyph = font->data + font->offsets[c - font->first];
            strokes = *glyph++;
            while (--strokes != -1) {
                points = *glyph++;
                if (points == 1) {
                    size = 2;
                    code = 0x68000000;
                    term = 0;
                } else if (points == 2) {
                    size = 3;
                    code = 0x40000000;
                    term = 0;
                } else {
                    size = points + 2;
                    code = 0x48000000;
                    term = 0x55555555;
                }
                if ((unsigned int)(16 - count) < size) {
                    *tag = (count << 24) + ((unsigned int)p & 0xFFFFFF);
                    if (use_ot) {
                        if (words != 0) {
                            tag = p;
                            p = tag + 1;
                            words--;
                            count = 0;
                        }
                    } else {
                        *p = 0xFFFFFF;
                        func_8007FA74(0);
                        func_8007FE4C(buf);
                        tag = buf;
                        p = buf + 1;
                        words = 16;
                        count = 0;
                    }
                }
                if ((unsigned int)words < size) {
                    continue;
                }
                *p++ = code + color;
                while (points-- != 0) {
                    b = *glyph++;
                    px = (int)((b >> 4) * screen_w) / 320;
                    py = (int)((b & 0xF) * screen_h) / 240;
                    *p++ = ((y + py) << 16) + ((x + px) & 0xFFFF);
                }
                if (term != 0) {
                    *p++ = term;
                }
                words -= size;
                count += size;
            }
        }
        x += (unsigned int)(font->width * screen_w) / 320;
    }
    *tag = (count << 24) + ((unsigned int)p & 0xFFFFFF);
    *p = 0xFFFFFF;
    if (!use_ot) {
        func_8007FA74(0);
        func_8007FE4C(buf);
        tag = 0;
    } else {
        *tag = (*tag & 0xFF000000) | (*ot & 0xFFFFFF);
        *ot = (*ot & 0xFF000000) | ((unsigned int)base & 0xFFFFFF);
        func_8007F7E8(p);
    }
    D_800EEE64.tag = tag;
    D_800EEE64.x = x;
    D_800EEE64.y = y;
}
