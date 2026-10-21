typedef struct SpuRegs {
    char pad0[422];
    volatile unsigned short trans_addr;
    volatile unsigned short trans_mode;
    volatile unsigned short ctrl;
} SpuRegs;

extern SpuRegs *D_800B76F0;
extern volatile unsigned int *volatile D_800B76F4;
extern volatile unsigned int *volatile D_800B76F8;
extern volatile unsigned int *volatile D_800B76FC;
extern unsigned short D_800B7708;
extern unsigned int D_800B7718;
extern int D_800B7740;
extern volatile unsigned int D_800B7744;
extern unsigned int D_800B7748;
extern void func_8009A9E4(void);
extern void func_8009A9BC(void);

int func_8009A578(int op, ...) {
    unsigned int *ap = (unsigned int *)&op + 1;
    unsigned int i;
    register unsigned int size asm("$4");
    register unsigned int chcr asm("$6");
    unsigned short mode;

    switch (op) {
    case 2:
        {
            register unsigned int a asm("$4") = *ap;
            register unsigned int n asm("$2") = D_800B7718;

            D_800B7708 = a >> n;
        }
        D_800B76F0->trans_addr = D_800B7708;
        break;
    case 1:
        D_800B7740 = 0;
        i = 0;
        while (D_800B76F0->trans_addr != D_800B7708) {
            if (++i > 3840) {
                return -2;
            }
        }
        D_800B76F0->ctrl = (D_800B76F0->ctrl & ~0x30) | 0x20;
        break;
    case 0:
        D_800B7740 = 1;
        i = 0;
        while (D_800B76F0->trans_addr != D_800B7708) {
            if (++i > 3840) {
                return -2;
            }
        }
        D_800B76F0->ctrl |= 0x30;
        break;
    case 3:
        mode = 0x20;
        if (D_800B7740 == 1) {
            mode = 0x30;
        }
        i = 0;
        while ((D_800B76F0->ctrl & 0x30) != mode) {
            if (++i > 3840) {
                return -2;
            }
        }
        if (D_800B7740 == 1) {
            func_8009A9E4();
        } else {
            func_8009A9BC();
        }
        ap += 1;
        chcr = 0x01000000;
        __asm__ volatile("" : "=r"(chcr) : "0"(chcr));
        {
            register unsigned int t asm("$4") = ap[-1];

            D_800B7744 = t;
        }
        size = *ap;
        D_800B7748 = (size >> 6) + ((size & 0x3F) != 0);
        {
            volatile unsigned int *d = D_800B76F4;
            register unsigned int w asm("$4") = D_800B7744;

            *d = w;
        }
        *D_800B76F8 = (D_800B7748 << 16) | 0x10;
        __asm__ volatile("" : "=r"(chcr) : "0"(chcr));
        chcr |= 0x201;
        if (D_800B7740 == 1) {
            chcr = 0x01000200;
        }
        *D_800B76FC = chcr;
        break;
    }
    return 0;
}
