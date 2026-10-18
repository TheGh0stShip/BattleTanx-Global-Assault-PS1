typedef struct Link {
    int unk00;
    volatile int flags;
    int unk08;
    unsigned int limit;
    unsigned int tries;
    int pad14;
    int errors;
    int pad1C;
    int unk20;
    int last_time;
    int sent;
    int pad2C;
    unsigned char cmd;
    unsigned char seq;
    unsigned char length;
    char pad33;
    int count;
    int data38;
    int data3C;
    int data40;
    int data44;
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
extern int func_800A1994(int, int, int, int);

int func_800A2094(Link *c, int retry) {
    int result = 1;

    if (retry != 0 && ++c->tries >= c->limit) {
        func_800A19E4(0);
    } else if (c->flags & 0x20) {
        c->flags |= 0x40;
        if (retry != 0) {
            c->flags |= 0x80;
        }
    } else {
        do {
            if (c->flags & 0x40) {
                if (c->flags & 0x80) {
                    retry = 1;
                }
                c->flags &= ~0xC0;
            }
            if (retry == 0) {
                c->tries = 0;
            }
            c->unk08 = 6;
            c->unk20 = 0;
            c->flags |= 0x20;
            c->unk20 = 0;
            result = func_8008FF1C(10, c->unk00, 0, &D_800EFD0C, 1, func_800A1994);
            c->flags &= ~0x20;
        } while (c->flags & 0x40);
    }
    return result;
}
