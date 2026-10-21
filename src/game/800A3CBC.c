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

int func_800A3CBC(Card *p) {
    int r;
    int m;

    m = 0;
    if (*p->rx >> 4 == 8) {
        m = p->port == 0;
    }
    r = func_8009EAA8(p, (unsigned char)D_800B8C7C(p, m));
    if (r == 90 || r == 0 || r < 0) {
        return r;
    }
    return -9;
}
