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

extern void func_800A1AB0(Link *);
extern int func_800A2094(Link *, int);

void func_800A1C8C(Link *c) {
    int status = func_8008F9A4();
    int result;

    if (status == 4) {
        func_800A1AB0(c);
        result = func_800A2094(c, 1);
    } else {
        if (status == 3 && ++c->tries >= c->limit) {
            func_800A19E4(0);
            return;
        }
        c->unk20 = 0;
        result = func_8008FF1C(10, c->unk00, 0, D_800EFD0C.packet, 1, func_800A1994);
    }
    if (result == 0) {
        func_800A19E4(0);
    }
}
