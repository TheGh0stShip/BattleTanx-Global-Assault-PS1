typedef struct {
    volatile unsigned char data;
    char pad1[3];
    volatile unsigned short stat;
    char pad6[8];
    volatile unsigned short baud;
} SioRegs;

typedef struct {
    char pad0[0x3C];
    signed char *buf;
    char pad40[4];
    unsigned char idx;
    unsigned char count;
    char pad46[0xA2];
    unsigned char type;
} PadPort;

extern SioRegs *D_800B8CD8;
extern volatile int *D_800B8CD4;
extern int D_800B8CB8;
extern unsigned int D_800EFE40;
extern unsigned int D_800EFE3C;
extern void func_800A3A24(int n);
extern int func_800A3A44(void);

int func_8009EAA8(PadPort *p, int out) {
    register int baud asm("$17");
    int in;
    unsigned int t;

    baud = 136;
    if (((*p->buf & 0xFF) >> 4) == 8 && p->idx >= 9) {
        baud = 34;
    }
    while (!(D_800B8CD8->stat & 2)) {
    }
    func_800A3A24(400);
    in = D_800B8CD8->data;
    if (p->idx != 0 || (in >> 4) != 8) {
        D_800B8CD8->baud = baud;
    } else {
        D_800B8CD8->baud = 34;
    }
    while (!(*D_800B8CD4 & 0x80)) {
        t = *(volatile unsigned short *)0x1F801120;
        if (t < D_800EFE40) {
            if (*(volatile unsigned short *)0x1F801128 != 0) {
                t += *(volatile unsigned short *)0x1F801128;
            } else {
                t += 0x10000;
            }
        }
        if ((*(volatile unsigned short *)0x1F801124 & 0x200) && t - D_800EFE40 >= D_800EFE3C) {
            return -2;
        }
        if ((t - D_800EFE40) >> 3 >= D_800EFE3C) {
            return -2;
        }
    }
    if (p->type != 8 && D_800B8CB8 == 2) {
        func_800A3A24(60);
        while (func_800A3A44() == 0) {
        }
    }
    D_800B8CD8->data = out;
    p->count++;
    if (*(volatile unsigned char *)&p->idx != 0xFF) {
        p->buf[p->idx] = in;
    }
    p->idx++;
    return in;
}
