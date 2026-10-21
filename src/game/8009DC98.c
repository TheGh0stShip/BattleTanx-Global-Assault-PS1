typedef struct PadPort {
    int w0;
    int w4;
    int w8;
    struct PadPort *slots;
    struct PadPort *port;
    int w14;
    int w18;
    unsigned char pad1C[0x14];
    unsigned char *buf;
    unsigned char b34;
    unsigned char b35;
    unsigned char pad36;
    unsigned char b37;
    unsigned char pad38[4];
    unsigned char *act;
    unsigned char *act2;
    unsigned char pad44[2];
    unsigned char b46;
    unsigned char pad47[2];
    unsigned char b49;
    unsigned char pad4A[0x13];
    unsigned char id[6];
    unsigned char pad63[0x80];
    unsigned char bE3;
    unsigned char bE4;
    unsigned char padE5;
    unsigned short hE6;
    unsigned char bE8;
    unsigned char bE9;
    unsigned char bEA;
    unsigned char padEB[5];
} PadPort;

typedef struct {
    unsigned char pad0[0x0A];
    unsigned short h0A;
} PadSys;

extern int D_800B8CB4;
extern int D_800B8CB8;
extern int D_800B8CC8;
extern int D_800B8CCC[];
extern PadSys *D_800B8C5C;
extern PadPort D_800EF2D8[];
extern void func_800A3698(PadPort *p, int mode);
extern void func_8009DE6C(PadPort *p);
extern int func_8009E5F4(PadPort *p);

void func_8009DC98(PadPort *p)
{
    int i;
    PadPort *s;
    unsigned char *q;

    if (p->b49) {
        if (p->bE8 == 8) {
            s = p->slots;
            for (i = 0; i < 4; i++) {
                func_8009DC98(s++);
            }
        }
        p->b49 = 0;
        p->b46 = 0;
        p->hE6 = 0;
        p->w14 = 0;
        p->w18 = 0;
        p->bE3 = 0;
        p->bE4 = 0;
        p->hE6 = 0;
        p->bE9 = 0;
        p->bEA = 0;
        p->w0 = 0;
        p->w4 = 0;
        p->w8 = 0;
        q = p->id;
        for (i = 0; i < 6; i++) {
            *q++ = 0xFF;
        }
    }
}

static inline int next_port(void)
{
    D_800B8CB4++;
    return D_800B8CC8 < D_800B8CB4 || func_8009E5F4(&D_800EF2D8[D_800B8CB4]);
}

void func_8009DD5C(int mode)
{
    PadPort *p;
    int none;
    int done;

    none = -9;
    do {
        p = &D_800EF2D8[D_800B8CB4];
        if (mode != none) {
            if (mode == 0) {
                D_800B8CCC[D_800B8CB4] = ((*p->act >> 4) == 8) << 2;
            } else {
                func_800A3698(p, mode);
                func_8009DE6C(p);
            }
        }
        D_800B8CB8 = 0;
        D_800B8C5C->h0A = 0;
        done = next_port();
        mode = 0xFFFF;
    } while (!done);
}
