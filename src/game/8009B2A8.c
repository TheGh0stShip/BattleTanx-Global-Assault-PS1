typedef struct {
    const unsigned char *str;
    char *ap;
    unsigned char ch;
    unsigned char saved_ch;
    int pos;
    int saved_pos;
    const unsigned char *saved_str;
    unsigned char buf[256];
} FormatState;

extern FormatState D_800EF19C;
extern int func_8008AFB0(unsigned char *dst, const unsigned char *fmt, ...);
extern unsigned char *func_8008DA04(unsigned char *dst, const unsigned char *src);
extern int func_80090184(const unsigned char *s);

int func_8009B2A8(unsigned char *out, unsigned int size, int stop_at_newline,
                  const unsigned char *fmt, char *ap)
{
    unsigned int n;
    int done;
    int in_spec;
    unsigned char spec[50];
    unsigned int len;
    int type;
    int is_short;
    int is_long;
    int expanded;

    if (fmt != 0 || ap != 0) {
        D_800EF19C.str = fmt;
        D_800EF19C.ap = ap;
        D_800EF19C.ch = fmt[0];
        D_800EF19C.pos = 1;
        D_800EF19C.saved_str = 0;
    }
    n = 0;
    if (D_800EF19C.ch == 0) {
        goto end;
    }
    do {
        done = 0;
        in_spec = 0;
        while (n < size - 1 && D_800EF19C.ch != 0 && !done && !in_spec) {
            unsigned char c = D_800EF19C.ch;
            if (c != '%' || D_800EF19C.saved_str != 0) {
                if (c == '\n' && stop_at_newline) {
                    done = 1;
                }
                out[n] = D_800EF19C.ch;
                n++;
                D_800EF19C.ch = D_800EF19C.str[D_800EF19C.pos++];
            } else if (D_800EF19C.str[D_800EF19C.pos] == c) {
                out[n] = c;
                n++;
                D_800EF19C.pos++;
                D_800EF19C.ch = D_800EF19C.str[D_800EF19C.pos++];
            } else {
                in_spec = 1;
            }
        }
        type = 0;
        out[n] = 0;
        spec[0] = 0;
        if (in_spec) {
            is_short = 0;
            is_long = 0;
            spec[0] = D_800EF19C.ch;
            len = 1;
            D_800EF19C.ch = D_800EF19C.str[D_800EF19C.pos++];
            {
                unsigned char *q = spec;

                while ((D_800EF19C.ch == '-' || D_800EF19C.ch == '+' || D_800EF19C.ch == '0'
                        || D_800EF19C.ch == ' ' || D_800EF19C.ch == '#') && len < 50) {
                    q[len] = D_800EF19C.ch;
                    len++;
                    D_800EF19C.ch = D_800EF19C.str[D_800EF19C.pos++];
                }
            }
            while (D_800EF19C.ch >= '0' && D_800EF19C.ch <= '9' && len < 50) {
                spec[len] = D_800EF19C.ch;
                len++;
                D_800EF19C.ch = D_800EF19C.str[D_800EF19C.pos++];
            }
            if (D_800EF19C.ch == '.' && len < 50) {
                unsigned char *q = spec;
                q[len] = D_800EF19C.ch;
                len++;
                D_800EF19C.ch = D_800EF19C.str[D_800EF19C.pos++];
                while (D_800EF19C.ch >= '0' && D_800EF19C.ch <= '9' && len < 50) {
                    q[len] = D_800EF19C.ch;
                    len++;
                    D_800EF19C.ch = D_800EF19C.str[D_800EF19C.pos++];
                }
            }
            if (len < 50) {
                if (D_800EF19C.ch == 'h') {
                    is_short = 1;
                    spec[len] = D_800EF19C.ch;
                    len++;
                    D_800EF19C.ch = D_800EF19C.str[D_800EF19C.pos++];
                } else if (D_800EF19C.ch == 'l' || D_800EF19C.ch == 'L') {
                    is_long = 1;
                    spec[len] = D_800EF19C.ch;
                    len++;
                    D_800EF19C.ch = D_800EF19C.str[D_800EF19C.pos++];
                }
            }
            switch (D_800EF19C.ch) {
            case 'c': case 'C':
                type = 1;
                break;
            case 'd': case 'i': case 'o': case 'u': case 'x': case 'X':
                if (is_short) type = 2;
                else if (is_long) type = 4;
                else type = 3;
                break;
            case 'f':
                is_short = 1;
            case 'e': case 'E': case 'g': case 'G':
                if (is_short) type = 5;
                else if (is_long) type = 7;
                else type = 6;
                break;
            case 'n': case 'p':
                type = 8;
                break;
            case 's': case 'S':
                type = 9;
                break;
            }
            if (D_800EF19C.ch != 0 && len < 50) {
                spec[len] = D_800EF19C.ch;
                len++;
                D_800EF19C.ch = D_800EF19C.str[D_800EF19C.pos++];
            }
            spec[len] = 0;
        }
        expanded = 0;
        switch (type) {
        case 1:
                        expanded = *(unsigned char *)((D_800EF19C.ap += 4) - 4);
            expanded = func_8008AFB0(D_800EF19C.buf, spec, expanded);
            break;
        case 2:
            expanded = *(short *)((D_800EF19C.ap += 4) - 4);
            expanded = func_8008AFB0(D_800EF19C.buf, spec, expanded);
            break;
        case 3: case 4: case 8:
            expanded = *(int *)((D_800EF19C.ap += 4) - 4);
            expanded = func_8008AFB0(D_800EF19C.buf, spec, expanded);
            break;
        case 9: {
            const unsigned char *s = *(const unsigned char **)((D_800EF19C.ap += 4) - 4);
            if (s != 0) {
                D_800EF19C.saved_str = D_800EF19C.str;
                D_800EF19C.str = s;
                D_800EF19C.saved_ch = D_800EF19C.ch;
                D_800EF19C.saved_pos = D_800EF19C.pos;
                D_800EF19C.ch = s[0];
                D_800EF19C.pos = 1;
            }
            break;
        }
        case 5: case 6: case 7:
            func_8008DA04(out + n, spec);
            n += func_80090184(out + n);
            func_8008DA04(out + n, (const unsigned char *)"<double types not supported>");
            n += func_80090184(out + n);
            break;
        case 0:
        default:
            if (in_spec) {
                func_8008DA04(out + n, spec);
                n += func_80090184(out + n);
            }
            break;
        }
        if (expanded != 0) {
            D_800EF19C.saved_str = D_800EF19C.str;
            D_800EF19C.str = D_800EF19C.buf;
            D_800EF19C.saved_ch = D_800EF19C.ch;
            D_800EF19C.saved_pos = D_800EF19C.pos;
            D_800EF19C.pos = 1;
            D_800EF19C.ch = D_800EF19C.buf[0];
        } else if (D_800EF19C.ch == 0 && D_800EF19C.saved_str != 0) {
            D_800EF19C.str = D_800EF19C.saved_str;
            D_800EF19C.saved_str = 0;
            D_800EF19C.ch = D_800EF19C.saved_ch;
            D_800EF19C.pos = D_800EF19C.saved_pos;
        }
    } while (!done && n < size - 1 && D_800EF19C.ch != 0);
end:
    out[n] = 0;
    return n;
}
