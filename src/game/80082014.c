typedef struct {
    char pad[0x3C];
    char cwd[0x80];
    int cwd_len;
} PathState;
extern PathState D_800EDC9C;
extern char *func_8008DA04(char *dst, char *src);

char *func_80082014(char *dst, char *path) {
    int n = 0;
    char c0 = path[0];
    char c1 = path[1];

    if (c0 != '\\' && c0 != '/' && c1 != ':') {
        n = D_800EDC9C.cwd_len;
        if (n != 0) {
            func_8008DA04(dst, D_800EDC9C.cwd);
            if (dst[n - 1] != '\\' && dst[n - 1] != '/') {
                dst[n++] = '\\';
            }
        }
    }
    return func_8008DA04(dst + n, path);
}
