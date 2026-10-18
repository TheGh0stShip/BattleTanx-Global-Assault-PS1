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
extern void func_800A2668(Link *, int, int, int);
extern void func_800A2564(Link *, int, int, int);
extern void func_800A232C(Link *, int, int, int);
extern void func_800A22C8(Link *, int, int, int);
extern void func_800A21F8(Link *, int, int, int);
extern void func_800A1F94(Link *, int, int, int);
extern void func_800A1D3C(Link *, int, int, int);
extern void func_800A1BEC(Link *, int, int, int);
extern void func_800A1C8C(Link *, int, int, int);
extern void func_800A1C3C(Link *, int, int, int);
extern void func_8008AA48(void *, int, int);

void func_800A2914(int a1, int a2, int a3) {
    Link *c = D_800EFE14;

    if (c == 0) {
        return;
    }
    c->unk20 = 0;
    switch (c->unk08) {
    case 0:
        break;
    case 1:
        func_800A2668(c, a1, a2, a3);
        break;
    case 2:
        func_800A2564(c, a1, a2, a3);
        break;
    case 3:
        func_800A232C(c, a1, a2, a3);
        break;
    case 4:
        func_800A22C8(c, a1, a2, a3);
        break;
    case 5:
        func_800A21F8(c, a1, a2, a3);
        break;
    case 6:
        func_800A1F94(c, a1, a2, a3);
        break;
    case 7:
        func_800A1D3C(c, a1, a2, a3);
        break;
    case 8:
        func_800A1BEC(c, a1, a2, a3);
        break;
    case 9:
        func_800A1C8C(c, a1, a2, a3);
        break;
    case 10:
        func_800A1C3C(c, a1, a2, a3);
        break;
    }
}

void func_800A2A38(void) {
    func_8008AA48(&D_800EFD0C, 0, 0x114);
}
