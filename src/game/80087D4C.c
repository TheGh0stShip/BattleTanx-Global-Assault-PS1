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
    char padE4[4];
    int callback;
} CardWrite;

extern CardWrite D_800EE588;
extern void func_800871E0(void);
extern unsigned int func_80086FC4(int);
extern void func_80087D10(char *, unsigned int);
extern void func_80087134(int);
extern void *func_8008A7BC(void *, void *, unsigned int);
extern void *func_8008AA48(void *, int, unsigned int);
extern void func_80096008(void (*)(int, int));
extern int func_80095684(char *, int, unsigned int);
extern void func_80087B60(int, int);

int func_80087D4C(int port, char *src, unsigned int size, int callback) {
    CardWrite *card = &D_800EE588;
    int ok = 0;
    char *buf;
    unsigned int len;
    unsigned int pad;

    if (card->active) {
        func_800871E0();
    }
    if (card->open != 0 && port == card->port && (func_80086FC4(card->channel) & 3) == 3) {
        if (card->verify) {
            func_80087D10(src, size);
        }
        card->start = src;
        card->src = src;
        card->done = 0;
        card->total = size;
        card->callback = callback;
        card->active = 1;
        if (size == 0) {
            func_80087134(1);
            ok = 1;
        } else if (card->sector + card->offset + size > card->limit) {
            func_80087134(0);
        } else {
            if (card->offset != 0 || size < 128) {
                len = 128;
                card->chunk = len - card->offset;
                buf = card->sector_buf;
                if (size < card->chunk) {
                    card->chunk = size;
                }
                func_8008A7BC(buf + card->offset, src, card->chunk);
                pad = len - (card->offset + card->chunk);
                if (pad != 0) {
                    func_8008AA48((card->offset + card->chunk) + buf, 0, pad);
                }
            } else {
                buf = src;
                len = size & ~127;
                card->chunk = len;
            }
            D_800EE588.buf = buf;
            D_800EE588.len = len;
            D_800EE588.retries = 0;
            func_80096008(func_80087B60);
            if (func_80095684(buf, D_800EE588.sector, len)) {
                ok = 1;
            } else {
                func_80087134(0);
            }
        }
    }
    return ok;
}
