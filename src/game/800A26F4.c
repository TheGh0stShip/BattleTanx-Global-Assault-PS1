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
    int data40;
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

extern void func_8008A884(void *, void *, int);
extern unsigned char func_800A1920(void *);
extern int func_800A19BC(int, int, int, int);

int func_800A26F4(Link *c, int retry) {
    int result = 1;
    unsigned int n;

    if (retry != 0 && ++c->tries >= c->limit) {
        func_800A19E4(0);
    } else if (c->flags & 0x400) {
        func_800A19E4(1);
    } else if (c->flags & 4) {
        c->unk20 = 0;
        c->flags |= 8;
        if (retry != 0) {
            c->flags |= 0x10;
        }
    } else {
        do {
            if (c->flags & 8) {
                if (c->flags & 0x10) {
                    retry = 1;
                }
                c->flags &= ~0x18;
            }
            if (c->cmd == 4) {
                c->seq = 0;
            }
            n = c->data44 - c->count;
            if (n >= 256) {
                n = 255;
            }
            c->length = n;
            D_800EFD0C.rx_length = n;
            D_800EFD0C.rx_data[0] = c->seq;
            D_800EFD0C.rx_data[1] = c->cmd;
            if (n != 0) {
                func_8008A884(&D_800EFD0C.rx_data[2], (char *)c->data3C + c->count, n);
            }
            D_800EFD0C.rx_data[n + 2] = func_800A1920(&D_800EFD0C);
            if (retry == 0) {
                c->tries = 0;
            }
            c->unk20 = 0;
            c->flags &= ~0x402;
            c->unk20 = 0;
            c->unk08 = 1;
            c->flags |= 4;
            result = func_8008FF1C(11, c->unk00, 0, &D_800EFD0C, n + 4, func_800A19BC);
            c->flags &= ~4;
        } while (c->flags & 8);
    }
    return result;
}
