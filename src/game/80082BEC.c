typedef struct Request {
    int port;
    int unit;
    int handle;
    unsigned int size;
    unsigned int pos;
    char pad14[0x20];
    int seek_busy;
    int queued;
    int queued_offset;
    unsigned int queued_whence;
    void *queued_cb;
} Request;

typedef struct RequestTable {
    char pad000[0xC];
    int (*io[10])(int, int, unsigned int, int, unsigned int, void *);
    char pad034[0x194];
    Request *pending[10];
    void *seek_callback[10];
} RequestTable;

extern RequestTable D_800EDC9C;
extern void func_8008228C(int);
extern void func_80082B9C(void);

int func_80082BEC(Request *r, int offset, unsigned int whence, void *cb) {
    int result;
    int again;
    int port;

    if (r->seek_busy != 0) {
        r->queued = 1;
        result = 1;
        r->queued_offset = offset;
        r->queued_whence = whence;
        r->queued_cb = cb;
    } else {
        r->queued = 0;
        do {
            again = 0;
            switch (whence) {
            case 0:
                r->pos = offset;
                break;
            case 1:
                r->pos += offset;
                break;
            case 2:
                r->pos = r->size + offset;
                break;
            }
            if (r->pos > r->size) {
                r->pos = r->size;
            }
            port = r->port;
            if (D_800EDC9C.pending[port] != 0) {
                func_8008228C(port);
            }
            D_800EDC9C.pending[port] = r;
            D_800EDC9C.seek_callback[port] = cb;
            r->seek_busy = 1;
            result = D_800EDC9C.io[port](9, r->handle, r->pos, offset, whence, func_80082B9C);
            if (result == 0) {
                D_800EDC9C.seek_callback[port] = 0;
            }
            r->seek_busy = 0;
            if (r->queued != 0) {
                offset = r->queued_offset;
                whence = r->queued_whence;
                cb = r->queued_cb;
                again = 1;
                r->queued_cb = 0;
                r->queued = 0;
            }
        } while (again);
    }
    return result;
}
