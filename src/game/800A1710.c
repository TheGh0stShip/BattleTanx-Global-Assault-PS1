typedef struct CdReadState {
    int sectors;
    unsigned int *volatile buf;
    int pad08;
    volatile int mode;
    int size;
    int pad14;
    int pad18;
    int start_time;
    int pad20;
    int read_cb;
    volatile int sync_cb;
    int ready_cb;
    volatile int flags;
} CdReadState;

extern CdReadState D_800B90BC;
extern int func_80097114(int);
extern int func_80097128(int);
extern int func_80097558(int);
extern int func_80088870(int);
extern int func_8009701C(void);
extern int func_800973AC(int, unsigned char *, unsigned char *);
extern int func_800A1520(int);

int func_800A1710(int sectors, unsigned int *buf, int mode) {
    register CdReadState *p asm("$4");
    CdReadState *q;
    CdReadState *r;
    register int v asm("$2");
    register int z asm("$4");

    p = &D_800B90BC;
    p->mode = mode;
    switch (p->mode & 0x30) {
    case 0:
        p->size = 512;
        break;
    case 0x20:
        p->size = 585;
        break;
    default:
        v = 582;
        q = &D_800B90BC;
        __asm__ volatile("" : "=r"(q) : "0"(q));
        q->size = v;
        break;
    }
    r = &D_800B90BC;
    z = 0;
    r->mode |= 0x20;
    r->buf = buf;
    __asm__ volatile("" : "=r"(sectors) : "0"(sectors));
    r->sectors = sectors;
    r->read_cb = func_80097114(z);
    r->sync_cb = func_80097128(0);
    if (r->flags & 1) {
        r->ready_cb = func_80097558(0);
    }
    r->start_time = func_80088870(-1);
    __asm__ volatile("" : "=r"(r) : "0"(r));
    if (func_8009701C() & 0xE0) {
        { unsigned char *none = 0; __asm__("" : "+r"(none)); func_800973AC(9, none, 0); }
    }
    {
        int ok = func_800A1520(0) > 0;
        __asm__("" : "+r"(ok));
        return ok;
    }
}
