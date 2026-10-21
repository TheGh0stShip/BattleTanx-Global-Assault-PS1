typedef struct SioRegs {
    unsigned char data;
    char pad1[3];
    unsigned short stat;
    char pad6[2];
    unsigned short mode;
    unsigned short ctrl;
    char padC[2];
    unsigned short baud;
} SioRegs;

typedef struct PadRegs {
    int unk00;
} PadRegs;

typedef struct PadPort {
    char pad0[0x3C];
    unsigned char *in;
    unsigned char *out;
    unsigned char index;
    unsigned char count;
} PadPort;

extern volatile SioRegs *D_800B8CD8;
extern volatile PadRegs *D_800B8CD4;
extern int D_800EFE3C;
extern int D_800EFE40;

int func_800A3A44(void);

int func_8009E8D0(PadPort *p, int byte)
{
    int r;
    int baud;
    int c;

    if (byte < 0) {
        r = D_800B8CD8->data;
        p->index = 0xFF;
        p->count = 1;
        *p->out = ~byte;
        while (!(D_800B8CD8->stat & 1)) {
        }
        while (func_800A3A44() == 0) {
        }
        D_800B8CD8->data = ~byte;
        goto done;
    }
    c = *p->in;
    baud = 0x88;
    if ((c >> 4) == 8 && p->index >= 9) {
        baud = 0x22;
    }
    D_800EFE3C = 430;
    D_800EFE40 = *(volatile unsigned short *)0x1F801120;
    while (!(D_800B8CD8->stat & 2)) {
    }
    r = D_800B8CD8->data;
    D_800B8CD8->baud = baud;
    while (!(D_800B8CD4->unk00 & 0x80)) {
        if (func_800A3A44() != 0) {
            return -20;
        }
    }
    D_800B8CD8->data = byte;
    p->count++;
    p->in[p->index] = r;
    p->index++;
done:
    return r;
}
