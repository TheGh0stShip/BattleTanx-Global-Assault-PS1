typedef struct FileSys {
    int handle;
    char root[128];
    int root_len;
} FileSys;

extern FileSys D_800EC200;
extern char *func_8008DA04(char *, char *);

void func_8007E974(char *dst, char *src) {
    int len = 0;

    if (src[1] != ':') {
        len = D_800EC200.root_len;
        if (len != 0) {
            func_8008DA04(dst, D_800EC200.root);
            if (dst[len - 1] != '\\' && dst[len - 1] != '/') {
                dst[len] = '\\';
                len++;
            }
            if (*src == '\\' || *src == '/') {
                src++;
            }
        }
    }
    func_8008DA04(dst + len, src);
}
