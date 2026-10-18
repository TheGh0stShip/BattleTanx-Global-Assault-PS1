typedef struct Link {
    int unk00;
    volatile int flags;
    int unk08;
    unsigned int limit;
    unsigned int tries;
    unsigned int tries2;
    int errors;
    unsigned int timeout;
    unsigned int unk20;
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
    int in_timer;
    int timer_pad;
} LinkGlobals;

extern Link *D_800EFE14;
extern void func_800A19E4(int);

extern LinkGlobals D_800EFD0C;
extern int func_8008F988(void);
extern void func_8008FF1C(int, int);

void func_800A2DFC(unsigned int ticks) {
    Link *c;
    unsigned int limit;
    int status;

    if (ticks == 0) {
        return;
    }
    c = D_800EFD0C.current;
    if (c == 0) {
        return;
    }
    if (!(c->flags & 1)) {
        return;
    }
    c->flags |= 0x1000;
    switch (c->unk08) {
    case 6:
        if ((c->flags & 0x100) && !(c->flags & 0x200)) {
            goto idle;
        }
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
        c->unk20 += ticks;
        limit = c->timeout;
        break;
    case 0:
    default:
    idle:
        c->unk20 = 0;
        limit = -1;
        break;
    }
    if (c->unk20 < limit) {
        return;
    }
    c->unk20 = 0;
    D_800EFD0C.in_timer = 1;
    D_800EFD0C.timer_pad = 0;
    status = func_8008F988();
    switch (c->unk08) {
    case 0:
        break;
    case 1:
    case 4:
    case 8:
    case 10:
        if (!(status & 1)) {
            c->flags |= 2;
        }
        break;
    case 2:
    case 3:
    case 5:
    case 6:
    case 7:
    case 9:
        if (!(status & 2)) {
            func_8008FF1C(13, c->unk00);
        }
        break;
    }
    D_800EFD0C.in_timer = 0;
}
