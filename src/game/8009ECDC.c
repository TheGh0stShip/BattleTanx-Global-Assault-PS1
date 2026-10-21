typedef struct SioRegs {
    short r0;
    short r2;
    unsigned short status;
    short r6;
    short r8;
    unsigned short ctrl;
} SioRegs;

extern volatile int *D_800B8CD4;
extern volatile SioRegs *D_800B8CD8;
int func_800A3A44(void);

int func_8009ECDC(void)
{
    volatile int *mask = D_800B8CD4;
    volatile SioRegs *sio = D_800B8CD8;

    *mask = ~0x80;
    if (sio->status & 0x80) {
        do {
            if (func_800A3A44() != 0) {
                return 0;
            }
        } while (D_800B8CD8->status & 0x80);
    }
    D_800B8CD8->ctrl |= 0x10;
    return 1;
}
