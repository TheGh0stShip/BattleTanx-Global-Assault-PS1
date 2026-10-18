extern short func_80057420(char *, unsigned short, int);
extern short func_80057C30(char *, unsigned short, short, short, int, int, int);

short func_80057A0C(int value, unsigned short font, short x, short y, int scale, int color, unsigned short align, int flags) {
    char buf[24];
    char *p = buf;
    int div;
    short offset;

    if (value < 0) {
        *p++ = '-';
        value = -value;
    }
    div = 1000000000;
    while (value / div == 0) {
        div /= 10;
        if (div <= 0) {
            break;
        }
    }
    if (div == 0) {
        *p++ = '0';
    } else {
        while (div > 0) {
            short digit = value / div;

            *p++ = digit + '0';
            value -= digit * div;
            div /= 10;
        }
    }
    *p = 0;
    switch (align) {
    case 1:
        offset = func_80057420(buf, font, scale);
        break;
    case 2:
        offset = func_80057420(buf, font, scale) >> 1;
        break;
    case 0:
    default:
        offset = 0;
        break;
    }
    return func_80057C30(buf, font, x - offset, y, scale, color, flags);
}
