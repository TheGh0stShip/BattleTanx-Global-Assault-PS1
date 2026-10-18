typedef struct Link {
    int unk00;
    volatile int flags;
    int unk08;
    unsigned int limit;
    unsigned int tries;
    unsigned int tries2;
    int errors;
    int pad1C;
    int unk20;
    int last_time;
    int sent;
    int total;
    unsigned char cmd;
    unsigned char seq;
    unsigned char length;
    char pad33;
    unsigned int count;
    int data38;
    int data3C;
    unsigned int data40;
    unsigned int data44;
    void (*done)(struct Link *, int, int, int, int);
} Link;

typedef struct LinkGlobals {
    unsigned char rx_length;
    unsigned char rx_data[0x102];
    unsigned char packet[4];
    char pad107;
    Link *current;
} LinkGlobals;

extern Link *D_800EFE14;
extern void func_800A19E4(int);

extern LinkGlobals D_800EFD0C;
extern int func_8008FF1C(int, int, int, void *, int, void *);
extern int func_8008F9A4(void);
extern void func_800A1AF8(Link *, int);
extern int func_800A1994(int, int, int, int);

extern void func_800A1AB0(Link *);
extern int func_800A2094(Link *, int);
extern int func_800A1B2C(Link *, int, int);
extern unsigned char func_800A1920(void *);
extern void func_8008A884(void *, void *, unsigned int);

void func_800A1D3C(Link *c, int a1, int length, int ok) {
    int more = 1;
    unsigned char seq = 0;
    int bad = !ok;
    unsigned int n;

    if (ok != 0) {
        if (length != c->length + 3) {
            bad = 1;
        }
        if (bad == 0) {
            if (func_800A1920(&D_800EFD0C) != D_800EFD0C.rx_data[c->length + 2]) {
                bad = 1;
            }
            if (bad == 0) {
                if (c->flags & 0x100) {
                    c->cmd = D_800EFD0C.rx_data[1];
                    if (c->data38 != 0) {
                        *(unsigned char *)c->data38 = c->cmd;
                    }
                    c->flags &= ~0x100;
                } else if (c->cmd != D_800EFD0C.rx_data[1]) {
                    bad = 1;
                }
                if (bad == 0) {
                    seq = D_800EFD0C.rx_data[0];
                    if (seq != c->seq) {
                        if (c->cmd == 4 && seq == 0) {
                            c->seq = 0;
                            c->flags |= 0x100;
                        } else {
                            bad = 1;
                        }
                    }
                }
            }
        }
    }
    if (bad == 0) {
        if (seq == c->seq) {
            n = D_800EFD0C.rx_length;
            if (n != 0) {
                if (c->data44 - c->count < n) {
                    n = c->data44 - c->count;
                }
                func_8008A884((char *)c->data3C + c->count, &D_800EFD0C.rx_data[2], n);
                c->count += n;
                c->total += n;
            }
        }
        if (c->count >= c->data40) {
            func_800A19E4(1);
            more = 0;
        } else if (func_800A1B2C(c, 1, 8) != 0) {
            more = 0;
        }
    }
    if (bad != 0 || more != 0) {
        int result;
        if (func_8008F9A4() == 4) {
            func_800A1AB0(c);
            result = func_800A2094(c, 1);
        } else {
            result = func_800A1B2C(c, 2, 9);
        }
        if (result == 0) {
            func_800A19E4(0);
        }
    }
}
