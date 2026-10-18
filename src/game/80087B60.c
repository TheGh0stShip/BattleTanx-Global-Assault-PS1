typedef struct CardWrite {
    char pad0[5];
    unsigned char busy;
    char pad6[54];
    char sector_buf[128];
    int sector;
    unsigned int offset;
    int pad0C4;
    char *src;
    unsigned int chunk;
    unsigned int done;
    unsigned int total;
    char *buf;
    unsigned int len;
    unsigned int retries;
} CardWrite;

extern CardWrite D_800EE588;
extern void *func_8008A7BC(void *, void *, unsigned int);
extern void *func_8008AA48(void *, int, unsigned int);
extern int func_80095684(char *, int, unsigned int);
extern void func_80087134(int);

void func_80087B60(int event, int status) {
    int finish = 1;
    CardWrite *card = &D_800EE588;
    int ok = 0;
    unsigned int remaining;
    char *buf;
    unsigned int len;

    if (card->busy == 0 && event == 6) {
        if (status == 0) {
            card->src += card->chunk;
            card->done += card->chunk;
            if (card->chunk & 0x7F) {
                card->offset += card->chunk;
                if (card->offset == 128) {
                    card->offset = 0;
                    card->sector += 128;
                }
            } else {
                card->sector += card->chunk;
            }
            card = &D_800EE588;
            remaining = card->total - card->done;
            if (remaining == 0) {
                ok = 1;
            } else {
                if (remaining >= 128) {
                    card->chunk = remaining & ~127;
                    buf = card->src;
                    len = card->chunk;
                } else {
                    buf = card->sector_buf;
                    len = 128;
                    card->chunk = remaining;
                    func_8008A7BC(buf + card->offset, card->src, remaining);
                    func_8008AA48(buf + remaining, 0, len - remaining);
                }
                D_800EE588.buf = buf;
                D_800EE588.len = len;
                D_800EE588.retries = 0;
                if (func_80095684(buf, D_800EE588.sector, len)) {
                    finish = 0;
                }
            }
        } else if (status - 1 < 2U) {
            if (card->retries < 5) {
                card->retries++;
                if (func_80095684(card->buf, card->sector, card->len)) {
                    finish = 0;
                }
            }
        }
    }
    if (finish) {
        func_80087134(ok);
    }
}
