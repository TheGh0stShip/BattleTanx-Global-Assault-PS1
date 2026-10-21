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

int func_800A3D48(Card *arg) {
    register Card *p asm("$17");
    int m;
    int i;
    int off;
    int r;
    int *st;
    int base;
    Card *q;
    int b;

    D_800B8C80(arg);
    p = arg;
    m = 0;
    if (D_800B8CC0 != 0 && (b = *p->rx, b >> 4 == 8)) {
        m = p->port == 0;
    }
    if (m != 0) {
        for (i = -1, off = -240; i < 4; i++, off += 240) {
            if (--D_800BD454 <= 0) {
                break;
            }
            if (i >= 0) {
                D_800B8C80((char *)p->list + off);
            }
            r = func_8009EAA8(p, (unsigned char)D_800B8C7C(p, 1));
            if (r < 0) {
                return r;
            }
            func_800A3A24(60);
            if (func_8009ECDC() == 0) {
                return -3;
            }
        }
    }
    base = D_800B8CB4 == 0;
    if (D_800BD454 >= 2) {
        {
            int *a;

            a = D_800B8CCC;
            st = a + base;
        }
        off = base * 240;
        do {
            int n;

            n = *st;
            if (n < 0) {
                break;
            }
            if (n > 0) {
                q = ((Card *)(off + (int)D_800B8CA8))->list + n - 1;
                D_800B8C94(q);
            }
            switch (*st) {
            case 4:
                *st = 3;
                break;
            case 3:
                D_800B8C94(q - 1);
                *st = 1;
                break;
            case 0:
            case 1:
                q = (Card *)((char *)D_800B8CA8 + off);
                D_800B8C94(q);
                D_800B8C98(q);
                *st = -1;
                break;
            }
            r = func_8009E8D0(p, (unsigned char)D_800B8C7C(p, m));
            if (r < 0) {
                return r;
            }
            func_800A3A24(60);
            if (func_8009ECDC() != 0) {
                continue;
            }
            return -3;
        } while (--D_800BD454 >= 2);
    }
    while (--D_800BD454 > 0) {
        r = func_8009E8D0(p, (unsigned char)D_800B8C7C(p, m));
        if (r < 0) {
            return r;
        }
        func_800A3A24(60);
        if (func_8009ECDC() == 0) {
            return -3;
        }
    }
    func_8009ED6C();
    {
        int k;

        k = p->rxlen;
        p->rxlen = k + 1;
        k += (int)p->rx;
        *(unsigned char *)k = *D_800BD458;
    }
    D_800B8C74(0);
    return 0;
}
