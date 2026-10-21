typedef unsigned char u8;

typedef struct Track Track;
struct Track {
    u8 pad00[0x0C];
    Track *link;
    Track *master;
    void *pending;
    int (*handler)(Track *);
    u8 pad1C[0x30 - 0x1C];
    u8 *out;
    u8 pad34[2];
    u8 f36;
    u8 f37;
    u8 f38;
    u8 pad39[0x3C - 0x39];
    u8 *in;
    u8 pad40[4];
    u8 msgLen;
    u8 pad45;
    u8 state;
    u8 f47;
    u8 pad48;
    u8 f49;
    u8 f4A;
    u8 pad4B[0x50 - 0x4B];
    u8 f50;
    u8 pad51[0xE8 - 0x51];
    u8 status;
};

extern void (*D_800B8C78)(Track *);
void func_800A3698(Track *t, int v);
int func_800A3954(Track *t);
int func_8009EE28(Track *t);

void func_800A3318(Track *t)
{
    u8 *out;
    u8 *in;
    unsigned int old;
    unsigned int hi;
    int i;

    if (t != t->master) {
        u8 c = t->in[1];
        if (c != 0 && c != 0x5A) {
            func_800A3698(t, 0xFF);
            return;
        }
    }

    out = t->out;
    hi = t->in[0] >> 4;
    old = t->status;
    if (old == 8) {
        *out = 0;
    } else if (hi != 15) {
        t->status = hi;
        in = t->in;
        *out++ = 0;
        *out++ = *in++;
        if (t != t->master) {
            t->msgLen = 8;
            in++;
            for (i = 2; i < 8; i++)
                *out++ = *in++;
        } else if (hi == 8) {
            t->msgLen = 2;
        } else {
            in++;
            for (i = 2; i < t->msgLen; i++)
                *out++ = *in++;
        }
    }

    if ((t->in[1] == 0 && !(t->state == 1 && t->pending == 0) && t->f50 == 0)
        || (t->status != old && !t->f4A && !func_800A3954(t)
            && !(t == t->master ? t->f37 : t->f38)))
        D_800B8C78(t);

    t->f4A = 0;
    if (t->state == 0xFF)
        return;
    if ((u8)(t->state - 2) < 252 && t->in[0] != 0xF3)
        D_800B8C78(t);

    if (t->state != 0 && t->state != 0xFF) {
        if (t == t->master) {
            if (!t->f36)
                return;
        } else {
            if (!t->f37)
                return;
        }
    }

    switch (t->state) {
    case 0:
        if (t->status == 0)
            return;
        if (t->link == 0 && t->f36)
            return;
        if (t->status == 8 && t->link->in[0] == 0xFF) {
            t->f49 = 2;
            t->state = 0xFF;
        } else {
            t->f49 = 1;
            t->state++;
        }
        break;
    case 1:
        t->f47 = 0;
        t->state++;
        break;
    case 0xFE:
        t->state++;
        break;
    case 0xFF:
        break;
    default:
        if (t->handler)
            t->state += t->handler(t);
        else
            t->state += func_8009EE28(t);
        break;
    }
}
