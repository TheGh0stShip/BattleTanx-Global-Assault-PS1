typedef struct Request Request;

typedef struct RequestTable {
    char pad000[0x34];
    int transferred;
    int status;
    char pad03C[0x22C];
    int (*progress)(Request *, void *, int, int);
} RequestTable;

extern RequestTable D_800EDC9C;
extern int func_80082DF4(Request *, void *, int, void *);
extern void func_80082840(void);
extern void func_80083194(Request *);
extern int func_8008310C(Request *);
extern int func_8008314C(Request *, int);

int func_80082854(Request *r, void *buf, int len) {
    int aborted;
    int done;

    if (func_80082DF4(r, buf, len, func_80082840) != 0) {
        aborted = 0;
        done = aborted;
        do {
            if (D_800EDC9C.progress != 0) {
                if (D_800EDC9C.progress(r, buf, len, done) == 0) {
                    func_80083194(r);
                    aborted = 1;
                }
            }
            done = func_8008310C(r);
        } while (func_8008314C(r, 0) == 0 && aborted == 0);
        if (aborted == 0 && D_800EDC9C.progress != 0) {
            D_800EDC9C.progress(r, buf, len, D_800EDC9C.transferred);
        }
    } else {
        D_800EDC9C.transferred = 0;
        D_800EDC9C.status = 0;
    }
    return D_800EDC9C.transferred;
}
