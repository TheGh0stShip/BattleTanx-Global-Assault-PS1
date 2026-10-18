typedef struct FileCtl {
    int handle;
    char pad4[292];
    int busy;
    int pad12C;
    unsigned int count;
} FileCtl;

extern FileCtl D_800EC200;
extern int D_80086058;
extern int func_8007EB1C(int, char *, unsigned int);

int func_8007F450(int handle, char *buf, unsigned int len) {
    int ok = 0;
    unsigned int chunk;

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
            D_800EC200.count = 0;
            ok = func_8007EB1C(handle, buf, chunk);
            if (ok) {
                ok = D_800EC200.count != 0;
                if (ok) {
                    buf += D_800EC200.count;
                    len -= D_800EC200.count;
                }
            }
        }
    }
    return ok;
}
