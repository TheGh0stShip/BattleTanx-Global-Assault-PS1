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

extern Link *volatile D_800EFE14;
extern void func_800A19E4(int);

extern int func_800A2094(Link *, int);

int func_800A2A98(Link *c, int a1, int a2, int a3, int a4, int flag, int a6) {
    if (c->flags & 1) {
        func_800A19E4(0);
    }
    c->data38 = a1;
    c->count = 0;
    c->data3C = a2;
    c->data40 = a3;
    c->data44 = a4;
    c->done = (void *)a6;
    if (flag != 0) {
        c->flags |= 0x200;
    } else {
        c->flags &= ~0x200;
    }
    D_800EFE14 = c;
    c->flags |= 0x101;
    c->flags &= ~0x800;
    return func_800A2094(c, 0);
}
