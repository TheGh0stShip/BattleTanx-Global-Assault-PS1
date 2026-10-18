typedef struct Request {
    int port;
    int unit;
    int handle;
    unsigned int size;
    unsigned int pos;
    int busy;
    void *queued_buf;
    unsigned int queued_len;
    void *queued_cb;
} Request;

typedef struct RequestTable {
    char pad000[0xC];
    int (*io[10])(int, int, int, void *, unsigned int, void *);
    char pad034[0x194];
    Request *pending[20];
    void *callback[10];
} RequestTable;

extern RequestTable D_800EDC9C;
extern void func_8008228C(int);
extern void func_80082D90(void);

int func_80082DF4(Request *r, void *buf, unsigned int len, void (*cb)(Request *, void *, int, int)) {
    int result;
    int again;
    int port;

    if (r->busy != 0) {
        result = 1;
        r->queued_buf = buf;
        r->queued_len = len;
        r->queued_cb = cb;
    } else {
        r->queued_buf = 0;
        do {
            result = 0;
            again = result;
            if (r->size - r->pos < len) {
                len = r->size - r->pos;
            }
            if (len != 0) {
                port = r->port;
                if (D_800EDC9C.pending[port] != 0) {
                    func_8008228C(port);
                }
                D_800EDC9C.callback[port] = cb;
                D_800EDC9C.pending[port] = r;
                r->busy = 1;
                result = D_800EDC9C.io[port](10, r->handle, r->pos, buf, len, func_80082D90);
                if (result == 0) {
                    D_800EDC9C.pending[port] = 0;
                }
                r->busy = 0;
            } else if (cb != 0) {
                r->busy = 1;
                cb(r, buf, 0, 1);
                r->busy = 0;
            }
            if (r->queued_buf != 0) {
                buf = r->queued_buf;
                len = r->queued_len;
                cb = r->queued_cb;
                again = 1;
                r->queued_cb = 0;
                r->queued_buf = 0;
            }
        } while (again);
    }
    return result;
}
