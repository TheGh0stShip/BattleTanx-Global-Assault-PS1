extern int func_800A1134(char *, int);

unsigned char *func_80098098(unsigned char *p, int *hash) {
    char name[16];
    unsigned int n;
    unsigned char c;

    c = *p;
    if (c == '\\' || c == '/') {
        c = *++p;
    }
    n = 0;
    while (c != 0 && c != '.' && c != '\\' && c != '/') {
        name[n++] = c;
        c = *++p;
        if (n >= 8) {
            break;
        }
    }
    while (c != 0 && c != '.' && c != '\\' && c != '/') {
        c = *++p;
    }
    if (n < 12) {
        while (c != 0 && c != '\\' && c != '/') {
            name[n++] = c;
            c = *++p;
            if (n >= 12) {
                break;
            }
        }
    }
    name[n] = 0;
    while (c != 0 && c != '\\' && c != '/') {
        c = *++p;
    }
    *hash = func_800A1134(name, 1);
    return p;
}
