typedef struct {
    unsigned int sector;
    unsigned int size;
    int hash;
} DirEntry;

typedef struct {
    DirEntry *root;
    DirEntry *cur;
    DirEntry *end;
} DirTable;

extern DirTable D_800EF0EC;
extern int func_80097720(void *buf, int sector, int count);
extern void func_800977E0(unsigned char *rec);
extern DirEntry *func_8009796C(unsigned int sector);
extern void *func_8008A7BC(void *dst, void *src, int n);
extern void *func_8008A884(void *dst, void *src, int n);

int func_80097AA0(unsigned char *buf, int flat)
{
    unsigned char tmp[72];
    DirEntry *dir;
    int sector;
    unsigned int size;
    DirEntry *first;
    unsigned int carry;
    unsigned char *cur;
    unsigned char *rec;
    unsigned int pos;
    unsigned int off;
    unsigned int len;
    unsigned int n;
    unsigned int split;
    int count;
    int ok;
    int done;

    ok = 1;
    dir = D_800EF0EC.root;
    while (ok && dir < D_800EF0EC.cur) {
        carry = 0;
        size = dir->size & 0x3FFFFFFF;
        pos = 0;
        cur = buf;
        sector = dir->sector;
        split = pos;
        first = D_800EF0EC.cur;
        done = size == 0;
        while (ok && !done) {
            count = 4;
            if (size - pos < 0x2000) {
                count = (size - pos + 0x7FF) >> 11;
            }
            ok = func_80097720(buf, sector, count);
            sector += count;
            off = 0;
            if (!ok) {
                break;
            }
            if (cur != buf) {
                func_8008A7BC(tmp + split, buf, carry);
            }
            do {
                len = cur[off];
                if (len != 0) {
                    if (cur[off + 33] >= 2) {
                        if (D_800EF0EC.cur < D_800EF0EC.end) {
                            func_800977E0(cur + off);
                            if (!flat && (unsigned int)(buf - (unsigned char *)D_800EF0EC.cur) < 13) {
                                func_8008A884(buf + 0x1000, buf, 0x2000);
                                if (cur == buf) {
                                    cur = buf + 0x1000;
                                }
                                buf += 0x1000;
                            }
                        } else {
                            ok = 0;
                        }
                    }
                    off += len;
                    pos += len;
                } else {
                    off = (off | 0x7FF) + 1;
                    pos = (pos | 0x7FF) + 1;
                }
                rec = cur + off;
                if (pos >= size) {
                    done = 1;
                } else if (cur != buf) {
                    off = carry;
                    cur = buf;
                } else if (off < 0x2000) {
                    n = *rec;
                    if (off + n > 0x2000) {
                        split = 0x2000 - off;
                        carry = n - split;
                        func_8008A7BC(tmp, rec, split);
                        cur = tmp;
                    }
                }
            } while (ok && !done && off < 0x2000 && cur == buf);
        }
        size = ((unsigned int)D_800EF0EC.cur - (unsigned int)first) | 0x80000000;
        dir->sector = (unsigned int)first;
        dir->size = size;
        dir = func_8009796C(sector);
    }
    return ok;
}
