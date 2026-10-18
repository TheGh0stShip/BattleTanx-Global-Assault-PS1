typedef struct CardIo {
    char pad00[5];
    unsigned char busy;
    char pad06[2];
    unsigned char notify;
    char pad09[0x33];
    char buffer[0x80];
    char *src;
    int last;
    int user;
    char *dst;
    unsigned int chunk;
    int done;
    int total;
    char *io_buf;
    int io_len;
    unsigned int retries;
} CardIo;

extern CardIo D_800EE588;
extern void func_8008A7BC(void *, void *, unsigned int);
extern int func_80095494(char *, char *, int);
extern void func_80087D10(int, int);
extern void func_80087134(int);

void func_80087F28(int event, int code) {
    int fail = 1;
    int finished = 0;
    char *dst;
    unsigned int chunk;
    int rest;

    if (D_800EE588.busy == 0 && event == 5) {
        if (code == 0) {
            dst = D_800EE588.dst;
            chunk = D_800EE588.chunk;
            D_800EE588.dst = dst + chunk;
            D_800EE588.done += chunk;
            rest = D_800EE588.total - D_800EE588.done;
            if (rest == 0) {
                if (chunk < 128) {
                    func_8008A7BC(dst, D_800EE588.buffer, chunk);
                    D_800EE588.last = D_800EE588.chunk;
                } else {
                    D_800EE588.src += chunk;
                }
                finished = 1;
            } else {
                D_800EE588.chunk = rest;
                D_800EE588.io_buf = D_800EE588.buffer;
                D_800EE588.io_len = 128;
                D_800EE588.retries = 0;
                D_800EE588.src += chunk;
                if (func_80095494(D_800EE588.buffer, D_800EE588.src, 128)) {
                    fail = 0;
                }
            }
        } else if ((unsigned int)(code - 1) < 2 && D_800EE588.retries < 5) {
            D_800EE588.retries++;
            if (func_80095494(D_800EE588.io_buf, D_800EE588.src, D_800EE588.io_len)) {
                fail = 0;
            }
        }
    }
    if (fail) {
        if (finished && D_800EE588.notify != 0) {
            func_80087D10(D_800EE588.user, D_800EE588.total);
        }
        func_80087134(finished);
    }
}
