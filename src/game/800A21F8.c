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
extern int func_8008F9A4(void);
extern void func_800A1AB0(Link *);
extern int func_800A26F4(Link *, int);
extern int func_800A1994(int, int, int, int);

void func_800A21F8(Link *c) {
    int status = func_8008F9A4();
    int result;
    int resend;

    if (status == 4) {
        result = func_800A26F4(c, 1);
    } else {
        resend = 1;
        if (status == 3) {
            if (++c->tries >= c->limit) {
                func_800A19E4(0);
                resend = 0;
            } else {
                func_800A1AB0(c);
            }
        }
        if (resend == 0) {
            return;
        }
        c->unk20 = 0;
        result = func_8008FF1C(10, c->unk00, 0, D_800EFD0C.packet, 1, func_800A1994);
    }
    if (result == 0) {
        func_800A19E4(0);
    }
}
