typedef struct {
    unsigned char pad[0x1A6];
    volatile unsigned short trans_addr;
    volatile unsigned short trans_fifo;
    volatile unsigned short control;
    volatile unsigned short trans_mode;
    volatile unsigned short status;
} SpuRegs;

extern SpuRegs *D_800B76F0;
extern unsigned short D_800B7708;
extern int D_800B7740;
extern void (*volatile D_800B7728)(void);
extern char D_800C5530[];
extern char D_800C5550[];
extern char D_800C5564[];
extern void func_8009AA0C(void);
extern void func_800943B0(char *, ...);
extern void func_80096E6C(int, int);

void func_8009A2FC(unsigned short *addr_in, unsigned int size_in)
{
    unsigned int size = size_in;
    unsigned short *addr = addr_in;
    unsigned short status;
    int n;
    int i;
    unsigned int wait;

    status = D_800B76F0->status & 0x7FF;
    D_800B76F0->trans_addr = D_800B7708;
    func_8009AA0C();
    while (size != 0) {
        n = (size > 64) ? 64 : size;
        i = 0;
        if (n > 0) {
            do {
                D_800B76F0->trans_fifo = *addr++;
                i += 2;
            } while (i < n);
        }
        {
            register unsigned short c asm("$4") = D_800B76F0->control;

            D_800B76F0->control = (c & 0xFFCF) | 0x10;
            __asm__ volatile("" : : "r"(c));
        }
        func_8009AA0C();
        wait = 0;
        while (D_800B76F0->status & 0x400) {
            if (++wait > 3840) {
                func_800943B0(D_800C5530, D_800C5550);
                break;
            }
        }
        func_8009AA0C();
        func_8009AA0C();
        size -= n;
    }
    {
        register unsigned short c asm("$4") = D_800B76F0->control;
        register unsigned short d asm("$3") = c & 0xFFCF;

        D_800B76F0->control = d;
    }
    wait = 0;
    while ((D_800B76F0->status & 0x7FF) != status) {
        if (++wait > 3840) {
            func_800943B0(D_800C5530, D_800C5564);
            break;
        }
    }
}

void func_8009A4B4(void)
{
    unsigned int i;

    if (D_800B7740 == 0) {
        func_8009AA0C();
    }
    D_800B76F0->control &= 0xFFCF;
    i = 0;
    while (D_800B76F0->control & 0x30) {
        if (++i > 3840) {
            break;
        }
    }
    __asm__ volatile("" : "=r"(i));
    if (D_800B7728 != 0) {
        D_800B7728();
    } else {
        func_80096E6C(0xF0000009, 32);
    }
}
