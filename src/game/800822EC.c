typedef struct Request {
    int port;
    int unit;
    int handle;
    int size;
    int unk10;
    int unk14;
    int unk18;
    int pad1C;
    int pad20;
    int busy;
    void *queued_buf;
    int queued_len;
    void *queued_cb;
    int unk34;
    int unk38;
} Request;

typedef struct RequestTable {
    char pad000[0xC];
    int (*io[30])();
    char pad084[0x40];
    char path[0x104];
    Request *pending[30];
    void *callback[30];
} RequestTable;

extern RequestTable D_800EDC9C;

extern void func_80081E94(char *, int *, int *, char **);
extern void func_80082014(char *, char *);

int func_800822EC(Request *r, char *path) {
    int port;
    int unit;
    char *name;
    int size;
    int ok;

    func_80081E94(path, &port, &unit, &name);
    ok = 0;
    r->port = port;
    r->unk10 = 0;
    r->unk14 = 0;
    r->busy = 0;
    r->unk34 = 0;
    r->unk18 = 0;
    r->queued_buf = 0;
    r->unk38 = 0;
    r->unit = unit;
    if (port != -1) {
        if (D_800EDC9C.io[port](4)) {
            func_80082014(D_800EDC9C.path, name);
            name = D_800EDC9C.path;
        }
        if ((r->handle = D_800EDC9C.io[port](5, unit, name, 2, &size)) != 0
            || (r->handle = D_800EDC9C.io[port](5, unit, name, 0, &size)) != 0) {
            ok = 1;
            r->size = size;
        }
    }
    return ok;
}
