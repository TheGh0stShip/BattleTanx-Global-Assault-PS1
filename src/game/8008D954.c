extern int func_80090184(char *);

char *func_8008D954(char *dst, char *src) {
    char *start;
    char *end;
    int c;

    if (dst == 0) {
        return 0;
    }
    if (src == 0) {
        return 0;
    }
    end = dst + func_80090184(dst);
    if (end != src + func_80090184(src)) {
        start = dst;
        while (*(signed char *)dst++ != 0) {
        }
        dst--;
        do {
            c = *(unsigned char *)src++;
            *dst++ = c;
        } while (c != 0);
        return start;
    }
    return 0;
}
