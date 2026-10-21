typedef struct Port Port;
struct Port {
    char pad0[0xC];
    Port *sub;
    Port *parent;
    int (*start)(Port *p);
    int (*step)(Port *p);
    char pad1C[0x10];
    unsigned char *link;
    unsigned char *out;
    char pad34[2];
    unsigned char b36;
    unsigned char b37;
    unsigned char b38;
    char pad39[3];
    unsigned char *rx;
    char pad40[4];
    unsigned char idx;
    char pad45[1];
    unsigned char state;
    unsigned char index;
    char pad48[1];
    unsigned char phase;
    unsigned char b4A;
    char pad4B[5];
    unsigned char b50;
    char pad51[0x97];
    unsigned char type;
    char padE9[7];
};

extern void func_8009F4E8(Port *p, int a);
extern void func_8009EDA4(Port *p);

int func_800A3168(Port *p)
{
    Port *q;
    int i;

    if (p->sub == 0) {
        if (p->b37 != 0) {
            return 0;
        }
        q = p->parent->sub;
        for (i = 0; i < 4; i++, q++) {
            if (q->b36 == 67 || q->b37 == 67) {
                if (*q->link == 1) {
                    return 0;
                }
            }
        }
    }
    if (*p->rx == 243 && p->type == 0) {
        goto reset;
    }
    switch (p->state) {
    case 0:
        return 0;
    case 1:
        func_8009F4E8(p, 1);
        return 0;
    case 0xFF:
        if (p->type != 8) {
            return 0;
        }
        q = p->sub;
        if (q == 0) {
            return 0;
        }
        for (i = 0; i < 4; i++, q++) {
            if (q->state == 1) {
                goto found;
            }
        }
        return 1;
    case 0xFE:
    reset:
        func_8009F4E8(p, 0);
        return 0;
    }
    if (p->start == 0) {
        goto none;
    }
    p->start(p);
    return 0;
found:
    func_800A3168(q);
    return 0;
none:
    func_8009EDA4(p);
    return 0;
}
