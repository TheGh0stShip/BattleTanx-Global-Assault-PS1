extern short func_80057420(unsigned char *, unsigned short, int);
extern int func_80056B70(unsigned char, unsigned short, short, short, int, int, int);

void func_80057D60(unsigned char *text, unsigned short font, int x, short y, int scale, int color, int flags) {
    int left;
    int offset;

    left = x - (func_80057420(text, font, scale) >> 1);
    offset = 0;
    while (*text != 0) {
        x = func_80056B70(*text++, font, left + offset, y, scale, color, flags);
        offset += x;
    }
}
