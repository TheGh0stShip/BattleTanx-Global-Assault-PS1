typedef struct Link {
    int unk00;
    volatile int flags;
    int unk08;
    int limit;
    int tries;
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
extern int func_8008FF1C(int, int, int, unsigned char *, int, void *);
extern int func_8008F9A4(void);
extern void func_800A1AB0(Link *);
extern int func_800A2094(Link *, int);
extern int func_800A1B2C(Link *, int, int);
extern int func_800A1994(int, int, int, int);

void func_800A1F94(Link *c, int a1, int kind, int ok) {
    int sent = 0;
    int len;
    int result;

    if (ok != 0 && kind == 1) {
        len = D_800EFD0C.rx_length;
        c->unk08 = 7;
        c->unk20 = 0;
        c->length = len;
        sent = func_8008FF1C(10, c->unk00, sent, D_800EFD0C.rx_data, c->length + 3, func_800A1994) != 0;
    }
    if (sent == 0) {
        if (func_8008F9A4() == 4) {
            if (!(c->flags & 0x800)) {
                func_800A1AB0(c);
                c->flags |= 0x800;
            } else {
                c->flags &= ~0x800;
            }
            result = func_800A2094(c, 0);
        } else {
            result = func_800A1B2C(c, 2, 9);
        }
        if (result == 0) {
            func_800A19E4(0);
        }
    }
}
