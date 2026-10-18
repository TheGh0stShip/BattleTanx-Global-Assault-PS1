typedef struct FileCtl {
    int handle;
    char pad4[292];
    int busy;
} FileCtl;

extern FileCtl D_800EC200;
extern int D_80086058;
extern int func_800942E8(int, char *, unsigned int);

int func_8007F52C(int handle, char *buf, unsigned int len) {
    int ok = 0;
    unsigned int chunk;
    int n;

    if (D_80086058 != 0) {
        if (D_800EC200.busy == handle) {
            D_800EC200.busy = 0;
        }
        ok = 1;
        while (len != 0 && ok) {
            chunk = len;
            if (chunk > 0xFFFF) {
                chunk = 0xFFFF;
            }
            n = func_800942E8(handle - 1, buf, chunk);
            ok = n == chunk;
            if (ok) {
                buf += n;
                len -= n;
            }
        }
    }
    return ok;
}
