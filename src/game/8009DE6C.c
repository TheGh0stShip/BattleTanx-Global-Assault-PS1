typedef struct PadRec {
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    unsigned char b4;
} PadRec;

typedef struct PadPort {
    int w0;
    PadRec *recs;
    int w8;
    struct PadPort *slots;
    struct PadPort *port;
    unsigned char pad14[0x14];
    unsigned char *in;
    unsigned char *out;
    unsigned char pad30[4];
    unsigned char in_len;
    unsigned char out_len;
    unsigned char b36;
    unsigned char b37;
    unsigned char b38;
    unsigned char pad39[0x0C];
    unsigned char b45;
    unsigned char pad46[0x11];
    unsigned char act[6];
    unsigned char id[6];
    unsigned char pad63[0x83];
    unsigned short hE6;
    unsigned char bE8;
    unsigned char bE9;
    unsigned char padEA[6];
} PadPort;

void func_8009DE6C(PadPort *p)
{
    PadPort *s;
    int i;

    p->b37 = p->b36;
    p->b36 = 0;
    s = p->slots;
    for (i = 0; i < 4; i++) {
        s->b38 = s->b37;
        s->b37 = s->b36;
        s->b36 = 0;
        s++;
    }
}
