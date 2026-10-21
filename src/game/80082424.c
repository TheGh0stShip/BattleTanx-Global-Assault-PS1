typedef struct Request Request;

typedef struct RequestTable {
    char pad000[0x144];
    char **search;
    char path[0x80];
} RequestTable;

extern RequestTable D_800EDC9C;
extern int func_800822EC(Request *, char *);
extern int func_80090184(char *);
extern void func_8008DA04(char *, char *);

int func_80082424(Request *r, char *name) {
    int ok = 0;
    int i;
    int len;
    char *dir;
    int dir_sep;
    int name_sep;
    char c;

    if (D_800EDC9C.search == 0 || D_800EDC9C.search[0] == 0) {
        ok = func_800822EC(r, name);
    } else {
        i = 0;
        do {
            dir = D_800EDC9C.search[i];
            if (dir == 0) {
                goto done;
            }
            len = func_80090184(dir);
            if (len > 0) {
                func_8008DA04(D_800EDC9C.path, dir);
                c = dir[len - 1];
                if (c != ':') {
                    dir_sep = (c == '\\' || c == '/');
                    name_sep = (name[0] == '\\' || name[0] == '/');
                    if (dir_sep) {
                        if (name_sep) {
                            len--;
                        }
                    } else if (!name_sep) {
                        D_800EDC9C.path[len] = '\\';
                        len++;
                    }
                }
            }
            func_8008DA04(D_800EDC9C.path + len, name);
            ok = func_800822EC(r, D_800EDC9C.path);
            i++;
        } while (ok == 0);
    }
done:
    return ok;
}
