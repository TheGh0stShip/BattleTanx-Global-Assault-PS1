typedef struct PadPort {
    char pad00[0x3C];
    unsigned char *volatile rx;
    char pad40[6];
    unsigned char state;
    unsigned char block;
    char pad48;
    unsigned char error;
    char pad4A[0x19];
    unsigned char data[0x80];
    unsigned char unkE3;
    unsigned char unkE4;
    char padE5;
    unsigned short length;
    char padE8;
    unsigned char unkE9;
    unsigned char blocks;
    char padEB;
    int offset;
} PadPort;

extern int func_8009EF74(PadPort *);
extern void func_8009EFAC(PadPort *, unsigned char *);

int func_8009EE28(PadPort *p) {
    unsigned char *rx;

    switch (p->state) {
    case 2:
        p->unkE3 = p->rx[3];
        p->unkE4 = p->rx[4];
        p->length = 0;
        p->unkE9 = p->rx[5];
        p->blocks = p->rx[6];
        p->offset = 0;
        break;
    case 3:
        rx = p->rx;
        p->length = (rx[4] << 8) + rx[5];
        p->block = 0;
        break;
    case 4:
        p->offset += ((p->rx[4] + 3) & 0x1FC) + 8;
        if (++p->block < p->blocks) {
        done:
            return 0;
        }
        if (func_8009EF74(p) > 128) {
            p->state = 254;
            p->error = 2;
            goto done;
        }
        p->state = 255;
        func_8009EFAC(p, p->data);
        p->state = 2;
        goto done;
    default:
        return 1;
    }
    return 1;
}
