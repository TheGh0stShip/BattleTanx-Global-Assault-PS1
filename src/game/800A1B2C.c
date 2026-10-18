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
    char pad32[2];
    int count;
    int data38;
    int data3C;
    int data40;
    int data44;
    void (*done)(struct Link *, int, int, int, int);
} Link;

typedef struct LinkGlobals {
    char pad000[0x103];
    unsigned char packet[4];
    char pad107;
    Link *current;
} LinkGlobals;

extern Link *D_800EFE14;
extern void func_800A19E4(int);

extern LinkGlobals D_800EFD0C;
extern unsigned char func_800A1920(unsigned char *);
extern int func_8008FF1C(int, int, int, unsigned char *, int, void *);
extern int func_800A19BC(int, int, int, int);

int func_800A1B2C(Link *c, unsigned char cmd, int a2) {
    if (cmd != 1) {
        c->errors++;
    }
    D_800EFD0C.packet[0] = 0;
    D_800EFD0C.packet[1] = c->seq;
    D_800EFD0C.packet[2] = cmd;
    D_800EFD0C.packet[3] = func_800A1920(D_800EFD0C.packet);
    c->unk08 = a2;
    c->unk20 = 0;
    c->flags &= ~2;
    return func_8008FF1C(11, c->unk00, 0, D_800EFD0C.packet, 4, func_800A19BC);
}
