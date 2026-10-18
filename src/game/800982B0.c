extern void func_80097FE4(char *, char *);
extern char *func_80098028(char *);
extern char *func_80098098(char *, int *);

typedef struct {
    unsigned int sector;
    int size;
} Entry800982B0;

extern Entry800982B0 *func_8009825C(Entry800982B0 *, int);
extern Entry800982B0 *D_800EF0EC;

int func_800982B0(char *path, unsigned int *pos, int *size) {
    char buf[136];
    int len;
    char *p;
    Entry800982B0 *e;
    int found = 0;

    func_80097FE4(path, buf);
    p = func_80098028(buf);
    e = D_800EF0EC;
    if (e != 0) {
    loop:
        if (*p != 0) {
            p = func_80098098(p, &len);
            e = func_8009825C(e, len);
            if (e != 0) {
                goto loop;
            }
        }
        if (e != 0 && e->size >= 0) {
            *pos = e->sector << 11;
            *size = e->size & 0x7FFFFFFF;
            found = 1;
        }
    }
    return found;
}
