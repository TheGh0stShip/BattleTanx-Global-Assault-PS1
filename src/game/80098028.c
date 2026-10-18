extern unsigned char func_80094A78(int);

unsigned char *func_80098028(unsigned char *path) {
    if (func_80094A78(path[0]) == 'C' && func_80094A78(path[1]) == 'D' && path[2] == ':') {
        path += 3;
    }
    return path;
}
