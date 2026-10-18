typedef struct Request {
    int port;
    int unk04;
    int addr;
    int unk0C;
    int sector;
    char pad14[0x10];
    int busy;
    void *queued_buf;
    int queued_len;
    void *queued_cb;
} Request;

typedef struct RequestTable {
    char pad000[0xC];
    int (*io[30])(int, int, int, void *, int, void *);
    char pad084[0x144];
    Request *pending[30];
    void *callback[30];
} RequestTable;

extern RequestTable D_800EDC9C;
extern void func_8008228C(int);
extern void func_80082F7C(int, int, int, int);

int func_80082FE0(Request *r, void *buf, int len, void *cb) {
    int again;
    int result;
    int port;

    if (r->busy != 0) {
        r->queued_buf = buf;
        r->queued_len = len;
        r->queued_cb = cb;
        return 1;
    }
    r->queued_buf = 0;
    do {
        port = r->port;
        again = 0;
        if (D_800EDC9C.pending[port] != 0) {
            func_8008228C(port);
        }
        D_800EDC9C.callback[port] = cb;
        D_800EDC9C.pending[port] = r;
        r->busy = 1;
        result = D_800EDC9C.io[port](11, r->addr, r->sector, buf, len, func_80082F7C);
        if (result == 0) {
            D_800EDC9C.pending[port] = 0;
        }
        r->busy = 0;
        if (r->queued_buf != 0) {
            buf = r->queued_buf;
            len = r->queued_len;
            cb = r->queued_cb;
            again = 1;
            r->queued_cb = 0;
            r->queued_buf = 0;
        }
    } while (again);
    return result;
}
