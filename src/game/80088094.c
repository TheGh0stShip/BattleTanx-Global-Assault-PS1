typedef struct CardWrite {
    char pad0[4];
    volatile unsigned char active;
    unsigned char busy;
    unsigned char open;
    char pad7;
    unsigned char verify;
    char pad9[35];
    int channel;
    int port;
    unsigned int limit;
    char pad38[4];
    char sector_buf[128];
    unsigned int sector;
    unsigned int offset;
    char *start;
    char *src;
    unsigned int chunk;
    unsigned int done;
    unsigned int total;
    char *buf;
    unsigned int len;
    unsigned int retries;
    int read_callback;
    int callback;
} CardWrite;

extern CardWrite D_800EE588;
extern void func_800871E0(void);
extern unsigned int func_80086FC4(int);
extern void func_80087134(int);
extern void *func_8008A7BC(void *, void *, unsigned int);
extern void func_80096008(void (*)(int, int));
extern int func_80095494(char *, int, unsigned int);
extern void func_80087F28(int, int);

int func_80088094(int port, char *dst, unsigned int size, int callback) {
    CardWrite *card = &D_800EE588;
    int ok = 0;
    unsigned int offset;
    unsigned int n;
    unsigned int len;

    if (card->active) {
        func_800871E0();
    }
    if (card->open != 0 && port == card->port && (func_80086FC4(card->channel) & 3) == 3) {
        offset = card->offset;
        card->start = dst;
        card->src = dst;
        card->done = 0;
        card->total = size;
        card->read_callback = callback;
        card->active = 1;
        if (offset != 0) {
            n = 128 - offset;
            if (size < n) {
                n = size;
            }
            func_8008A7BC(dst, D_800EE588.sector_buf + offset, n);
            dst += n;
            card->src = dst;
            card->done = n;
            card->offset += n;
            size -= n;
            if (card->offset >= 128) {
                card->offset = 0;
                card->sector += 128;
            }
        }
        if (size == 0) {
            func_80087134(1);
            ok = 1;
        } else if (D_800EE588.sector + D_800EE588.offset + size > D_800EE588.limit) {
            func_80087134(0);
        } else {
            if (size < 128) {
                len = 128;
                dst = D_800EE588.sector_buf;
                D_800EE588.chunk = size;
            } else {
                len = size & ~127;
                D_800EE588.chunk = len;
            }
            D_800EE588.buf = dst;
            D_800EE588.len = len;
            D_800EE588.retries = 0;
            func_80096008(func_80087F28);
            if (func_80095494(dst, D_800EE588.sector, len)) {
                ok = 1;
            } else {
                func_80087134(0);
            }
        }
    }
    return ok;
}
