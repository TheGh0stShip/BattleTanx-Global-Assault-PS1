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

unsigned char func_8009DEB0(PadPort *p, int sub)
{
    int idx;
    int n;
    int c;
    unsigned char *buf;

    idx = p->b45 - 3;
    if (sub) {
        n = idx - (idx / 8) * 8 - 2;
        p = &p->slots[idx / 8];
    } else {
        n = idx;
    }
    c = p->b36;
    if (n >= 0) {
        switch (c) {
        case 0:
            if (n < 6 && p->act[n] == 0) {
                return 0;
            }
            if (n >= p->in_len) {
                return 0;
            }
            buf = p->in;
        read:
            return buf[n];
        case 0x4D:
            if (n < p->out_len) {
                buf = p->out;
                goto read;
            }
            return 0xFF;
        default:
            if (n >= p->out_len) {
                return 0;
            }
            buf = p->out;
            goto read;
        }
    }
    if (n + 2 != 0) {
        return 0;
    }
    return c != 0 ? c : 0x42;
}
