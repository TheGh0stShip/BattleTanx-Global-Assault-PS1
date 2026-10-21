extern unsigned char D_800B6B31[];
extern void func_8009F89C();
extern void func_8009F998();
extern void *func_8008A974(const void *s, int c, int n);
extern int func_80090184(const char *s);

int func_8009D0AC(int unused, unsigned char *fmt0, char *ap)
{
    unsigned char *fmt;
    int ch;
    int c;
    int wnext;
    int pnext;
    int n;
    signed char *cp;
    int flags;
    int ret;
    int dprec;
    int prec;
    int sign;
    int fpprec;
    unsigned long ulval;
    int base;
    int width;
    int fieldsz;
    int realsz;
    int size;
    char *xdigs;
    signed char buf[40];

    if (fmt0 == 0) {
        return 0;
    }
    fmt = fmt0;
    xdigs = "0123456789abcdef";
    ret = 0;
    for (;; fmt++) {
        c = *fmt;
        if (c == '\0') {
            func_8009F998();
            return ret;
        }
        flags = 0;
        if (c != '%') {
            func_8009F89C(c);
            continue;
        }
        prec = -1;
        sign = 0;
        dprec = 0;
        fpprec = 0;
        width = 0;
rflag:
        ch = *++fmt;
        switch (ch) {
        case ' ':
            if (!sign) {
                sign = ' ';
            }
            goto rflag;
        case '#':
            flags |= 0x08;
            goto rflag;
        case '*':
            width = (ap += 4, *(int *)(ap - 4));
            if (width >= 0) {
                goto rflag;
            }
            width = -width;
        case '-':
            flags |= 0x10;
            goto rflag;
        case '+':
            sign = '+';
            goto rflag;
        case '.':
            ch = *++fmt;
            if (ch == '*') {
                n = (ap += 4, *(int *)(ap - 4));
                prec = n;
            } else {
                n = 0;
                if ((unsigned)ch < 128) {
digit:
                    if (D_800B6B31[c = *fmt] & 4) {
                        n = 10 * n + (c - '0');
                        pnext = *++fmt;
                        if ((unsigned)pnext < 128) {
                            goto digit;
                        }
                    }
                }
                fmt--;
            }
            prec = n < 0 ? -1 : n;
            goto rflag;
        case '0':
            flags |= 0x20;
            goto rflag;
        case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            n = 0;
            do {
                n = 10 * n + (*fmt - '0');
                wnext = *++fmt;
            } while ((unsigned)wnext < 128 && ({ __asm__("" : : : "memory"); D_800B6B31[*fmt] & 4; }));
            width = n;
            fmt--;
            goto rflag;
        case 'L':
            flags |= 0x02;
            goto rflag;
        case 'h':
            flags |= 0x04;
            goto rflag;
        case 'l':
            flags |= 0x01;
            goto rflag;
        case 'c':
            *(cp = buf) = (ap += 4, *(int *)(ap - 4));
            size = 1;
            sign = 0;
            goto print;
        case 'D':
            flags |= 0x01;
        case 'd':
        case 'i':
            if (flags & 0x01) {
                ulval = (ap += 4, *(long *)(ap - 4));
            } else if (flags & 0x04) {
                ulval = (ap += 4, *(short *)(ap - 4));
            } else {
                ulval = (ap += 4, *(int *)(ap - 4));
            }
            if ((long)ulval < 0) {
                ulval = -ulval;
                sign = '-';
            }
            base = 10;
            goto number;
        case 'n':
            if (flags & 0x01) {
                *(ap += 4, *(long **)(ap - 4)) = ret;
            } else if (flags & 0x04) {
                *(ap += 4, *(short **)(ap - 4)) = ret;
            } else {
                *(ap += 4, *(int **)(ap - 4)) = ret;
            }
            continue;
        case 'O':
            flags |= 0x01;
        case 'o':
            if (flags & 0x01) {
                ulval = (ap += 4, *(long *)(ap - 4));
            } else if (flags & 0x04) {
                ulval = (ap += 4, *(short *)(ap - 4));
            } else {
                ulval = (ap += 4, *(int *)(ap - 4));
            }
            base = 8;
            sign = 0;
            goto number;
        case 'p':
            ulval = (ap += 4, *(int *)(ap - 4));
            base = 16;
            sign = 0;
            goto number;
        case 's':
            cp = (ap += 4, *(signed char **)(ap - 4));
            if (cp == 0) {
                cp = (signed char *)"(null)";
            }
            if (prec >= 0) {
                signed char *p = func_8008A974(cp, 0, prec);

                if (p != 0) {
                    size = p - cp;
                    if (size > prec) {
                        size = prec;
                    }
                } else {
                    size = prec;
                }
            } else {
                size = func_80090184((char *)cp);
            }
            sign = 0;
            goto print;
        case 'U':
            flags |= 0x01;
        case 'u':
            if (flags & 0x01) {
                ulval = (ap += 4, *(long *)(ap - 4));
            } else if (flags & 0x04) {
                ulval = (ap += 4, *(short *)(ap - 4));
            } else {
                ulval = (ap += 4, *(int *)(ap - 4));
            }
            base = 10;
            sign = 0;
            goto number;
        case 'X':
            xdigs = "0123456789ABCDEF";
        case 'x':
            if (flags & 0x01) {
                ulval = (ap += 4, *(long *)(ap - 4));
            } else if (flags & 0x04) {
                ulval = (ap += 4, *(short *)(ap - 4));
            } else {
                ulval = (ap += 4, *(int *)(ap - 4));
            }
            base = 16;
            if ((flags & 0x08) && ulval != 0) {
                flags |= 0x40;
            }
            sign = 0;
number:
            if ((dprec = prec) >= 0) {
                flags &= ~0x20;
            }
            cp = buf + sizeof(buf);
            if (ulval != 0 || prec != 0) {
                do {
                    *--cp = xdigs[ulval % base];
                    ulval /= base;
                } while (ulval != 0);
                xdigs = "0123456789abcdef";
                if ((flags & 0x08) && base == 8 && *cp != '0') {
                    *--cp = '0';
                }
            }
            size = buf + sizeof(buf) - cp;
print:
            fieldsz = size + fpprec;
            if (sign) {
                fieldsz++;
            }
            if (flags & 0x40) {
                fieldsz += 2;
            }
            realsz = dprec;
            if (realsz < fieldsz) {
                realsz = fieldsz;
            }

            if (!(flags & (0x10 | 0x20)) && width) {
                for (n = realsz; n < width; n++) {
                    func_8009F89C(' ');
                }
            }
            if ((c = sign) != 0) {
                func_8009F89C(c);
            }
            if (flags & 0x40) {
                func_8009F89C('0');
                func_8009F89C((signed char)*fmt);
            }
            if ((flags & (0x10 | 0x20)) == 0x20) {
                for (n = realsz; n < width; n++) {
                    func_8009F89C('0');
                }
            }
            for (n = fieldsz; n < dprec; n++) {
                func_8009F89C('0');
            }
            for (n = size - 1; n >= 0; n--) {
                func_8009F89C(*cp++);
            }
            while (--fpprec >= 0) {
                func_8009F89C('0');
            }
            if (flags & 0x10) {
                for (n = realsz; n < width; n++) {
                    func_8009F89C(' ');
                }
            }
            ret += realsz > width ? realsz : width;
            break;
        case '\0':
            func_8009F998();
            return ret;
        default:
            ret++;
            func_8009F89C((signed char)*fmt);
            break;
        }
    }
}
