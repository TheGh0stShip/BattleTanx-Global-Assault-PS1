typedef struct PadPort {
    unsigned char pad0[0x0C];
    struct PadPort *slots;
    unsigned char pad10[0x26];
    unsigned char b36;
    unsigned char pad37[5];
    unsigned char *act;
    unsigned char pad40[0x10];
    unsigned char b50;
    unsigned char pad51[0x97];
    unsigned char bE8;
    unsigned char padE9[7];
} PadPort;

typedef struct SioRegs {
    unsigned char data;
    unsigned char pad1[3];
    unsigned short status;
    unsigned short pad6;
    unsigned short mode;
    unsigned short ctrl;
    unsigned short padC;
    unsigned short baud;
} SioRegs;

extern volatile SioRegs *D_800B8CD8;
extern volatile int *D_800B8CD4;
extern int D_800B8CB4;
extern int D_800B8CCC[];
extern void (*D_800B8C94)(PadPort *p);
extern void (*D_800B8C98)(PadPort *p);
extern void func_800A3A24(int n);
extern void func_8009ED6C(void);

int func_8009E5F4(PadPort *p)
{
    volatile SioRegs *sio;
    int n;
    int v;

    sio = D_800B8CD8;
    sio->ctrl = 0x40;
    sio->ctrl = 0;
    sio->mode = 13;
    sio->baud = 0x88;
    func_800A3A24(p->bE8 == 8 ? 80 : 145);
    n = D_800B8CB4;
    D_800B8CD8->ctrl = n ? 0x3003 : 0x1003;
    if (D_800B8CCC[n] >= 0) {
        while (D_800B8CCC[D_800B8CB4] > 0) {
            v = --D_800B8CCC[D_800B8CB4];
            D_800B8C94(p->slots + v);
        }
        if (D_800B8CCC[D_800B8CB4] == 0) {
            D_800B8CCC[D_800B8CB4] = -1;
            D_800B8C94(p);
            D_800B8C98(p);
        }
    }
    sio = D_800B8CD8;
    if (sio->status & 0x200) {
        sio->ctrl |= 0x10;
        if (sio->status & 0x200) {
            sio->data = 1;
            func_8009ED6C();
            D_800B8CD8->data;
            return 0;
        }
        *D_800B8CD4 = ~0x80;
    }
    if (p->b50 && p->b36) {
        return 0;
    }
    *p->act = 0;
    return 1;
}
