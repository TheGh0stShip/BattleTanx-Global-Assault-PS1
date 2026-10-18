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
extern unsigned char func_800A195C(Link *);
extern unsigned char func_800A1920(unsigned char *);
extern int func_800A26F4(Link *, int);
extern void func_800A1AF8(Link *, int);

void func_800A232C(Link *c, int a1, int length, int ok) {
    int failed = 0;
    int acked = 0;
    int duplicate = 0;
    int rejected = 0;
    int bad = !ok;
    unsigned char type;
    unsigned char seq;

    if (ok != 0) {
        if (length != D_800EFD0C.packet[0] + 3) {
            bad = 1;
        }
        type = D_800EFD0C.packet[2];
        seq = D_800EFD0C.packet[1];
        if (type == 1 && seq == c->seq) {
            acked = 1;
        } else if (type == 2 && seq == func_800A195C(c)) {
        } else if (type == 2 && seq == c->seq) {
            duplicate = 1;
            c->errors++;
        } else if (type == 3 && seq == c->seq) {
            rejected = 1;
            c->errors++;
        } else {
            bad = 1;
        }
        if (func_800A1920(D_800EFD0C.packet) != D_800EFD0C.packet[D_800EFD0C.packet[0] + 3]) {
            bad = 1;
        }
    }
    if (bad == 0) {
        if (rejected != 0) {
            func_800A19E4(0);
        } else if (duplicate == 0) {
            c->seq = func_800A195C(c);
            c->sent++;
            c->count += c->length;
            c->total += c->length;
            if (acked != 0) {
                if (c->count >= c->data44) {
                    func_800A19E4(1);
                } else if (func_800A26F4(c, 0) == 0) {
                    func_800A19E4(0);
                }
            } else {
                if (c->count >= c->data44) {
                    c->flags |= 0x400;
                }
                failed = 1;
            }
        } else {
            failed = 1;
        }
    } else {
        failed = 1;
    }
    if (failed != 0) {
        func_800A1AF8(c, 4);
    }
}
