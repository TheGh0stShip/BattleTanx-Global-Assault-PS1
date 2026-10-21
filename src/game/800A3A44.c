typedef struct Card {
    int unk0;
    int unk4;
    int unk8;
    struct Card *list;
    char pad10[0x26];
    unsigned char port;
    char pad37[5];
    unsigned char *rx;
    char pad40[4];
    unsigned char rxlen;
    char pad45[0xF0 - 0x45];
} Card;

extern unsigned int D_800EFE40;
extern unsigned int D_800EFE3C;
extern int (*D_800B8C8C)();
extern void (*D_800B8CA4)();
extern void (*D_800B8CA0)();
extern int (*D_800B8C7C)();
extern void (*D_800B8C80)();
extern void (*D_800B8C94)();
extern void (*D_800B8C98)();
extern void (*D_800B8C74)();
extern int D_800B8CB4;
extern int D_800B8CC4;
extern int D_800B8CB0;
extern int D_800B8CC0;
extern int D_800B8CCC[];
extern Card *D_800B8CA8;
extern int D_800BD45C;
extern int D_800BD454;
extern unsigned char *D_800BD458;
extern int func_8009E8D0(Card *p, int mode);
extern int func_8009EAA8(Card *p, int mode);
extern void func_800A3A24(int n);
extern int func_8009ECDC(void);
extern void func_8009ED6C(void);

int func_800A3A44(void) {
    register unsigned int c asm("$4");
    unsigned int d;
    register unsigned short t asm("$3");
    unsigned int lim;

    t = *(volatile unsigned short *)0x1F801120;
    __asm__("" : "=r"(t) : "0"(t));
    c = t;
    if (c < D_800EFE40) {
        if (*(volatile unsigned short *)0x1F801128 != 0) {
            c += *(volatile unsigned short *)0x1F801128;
        } else {
            c += 0x10000;
        }
    }
    if (!(*(volatile unsigned short *)0x1F801124 & 0x200)) {
        d = c - D_800EFE40;
        lim = D_800EFE3C;
        d = d >> 3;
    } else {
        d = c - D_800EFE40;
        lim = D_800EFE3C;
    }
    return d >= lim;
}
