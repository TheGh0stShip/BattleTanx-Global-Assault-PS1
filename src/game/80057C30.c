extern int func_80056B70(int, unsigned short, short, short, int, int, int);

short func_80057C30(unsigned char *text, unsigned short font, short x, short y, int a, int b, int c) {
    int width = 0;
    unsigned char *p = text;

    while (*p != 0) {
        width += func_80056B70(*p++, font, x + width, y, a, b, c);
    }
    return width;
}
