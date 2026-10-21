extern int func_800A1134(char *, int);

typedef struct {
    unsigned int sector;
    unsigned int size;
    int hash;
} Entry800977E0;

typedef struct {
    Entry800977E0 *root;
    Entry800977E0 *cur;
    Entry800977E0 *end;
} Dir800977E0;
extern Dir800977E0 D_800EF0EC;

void func_800977E0(unsigned char *rec) {
    Entry800977E0 *e = D_800EF0EC.cur;
    char name[16];
    unsigned char *p;
    unsigned int size;
    unsigned int len;
    unsigned int i;
    unsigned int base;
    unsigned int ext;
    int dot;
    unsigned char c;

    if (e + 1 < D_800EF0EC.end) {
        size = rec[2] | (rec[3] << 8) | (rec[4] << 16) | (rec[5] << 24);
        e->sector = size;
        size = rec[10] | (rec[11] << 8) | (rec[12] << 16) | (rec[13] << 24);
        if (rec[25] & 2) {
            size |= 0xC0000000;
        }
        p = rec + 33;
        ext = 0;
        dot = ext;
        i = ext;
        e->size = size;
        len = rec[32];
        base = ext;
        if (len != 0) {
            do {
                c = *p++;
                if (c == 0 || c == ';') {
                    i = len;
                } else if (c == '.') {
                    dot = 1;
                    name[base] = c;
                    base += dot;
                } else if (!dot) {
                    if (base < 8) {
                        name[base] = c;
                        base++;
                    }
                } else if (ext < 3) {
                    do {
                        name[base + ext] = c;
                        ext++;
                    } while (0);
                }
                i++;
            } while (i < len);
        }
        name[base + ext] = 0;
        e->hash = func_800A1134(name, 1);
        D_800EF0EC.cur = e + 1;
    }
}
