typedef struct {
    unsigned short pad0[2];
    unsigned short enabled;
    unsigned short expired;
    unsigned char pad8[8];
    unsigned char a0, a1;
    unsigned char pad12[7];
    unsigned char b0, b1;
    unsigned char pad1b[7];
    unsigned char c0, c1;
    unsigned short c2, c3;
    unsigned char pad28[0x64];
} Bank;

typedef struct {
    unsigned char pad[0x14];
    unsigned int mask;
    unsigned char pad18[8];
    int kind[8];
} BankQuery;

extern Bank D_800EE028[];

void func_800841B8(BankQuery *q, unsigned short *out)
{
    unsigned int i;
    Bank *b;
    int j = 0;

    *out++ = 0;
    for (i = 0; i < 8; i++) {
        b = &D_800EE028[i];
        if (q->mask & (1 << i)) {
            int k;
            *out = b->enabled;
            k = q->kind[j];
            out++;
            if ((unsigned int)(k - 2) < 3) {
                ((unsigned char *)out)[0] = b->a0;
                ((unsigned char *)out)[1] = b->a1;
                out++;
                ((unsigned char *)out)[0] = b->b0;
                ((unsigned char *)out)[1] = b->b1;
                out++;
            } else if (k == 6) {
                ((unsigned char *)out)[0] = b->c0;
                ((unsigned char *)out)[1] = b->c1;
                out++;
                *out = b->c2;
                out++;
                *out = b->c3;
                out++;
            }
            j++;
        }
    }
}
