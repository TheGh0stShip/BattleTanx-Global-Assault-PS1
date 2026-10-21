typedef struct PadPort {
    unsigned char pad0[12];
    struct PadPort *sub;
    struct PadPort *parent;
    unsigned char pad20[28];
    unsigned char *in;
    unsigned char unk52;
    unsigned char unk53;
    unsigned char pad54;
    unsigned char unk55;
    unsigned char pad56[4];
    unsigned char *act;
    unsigned char *mode;
    unsigned char pad68[25];
    unsigned char state[6];
    unsigned char pad99[141];
} PadPort;

typedef char PadPortSizeCheck[(sizeof(PadPort) == 240) ? 1 : -1];

extern int D_800B8CAC;
extern int D_800B8CC0;
extern void *D_800B8C74;
extern void *D_800B8C78;
extern void *D_800B8C7C;
extern void *D_800B8C80;
extern void *D_800B8C84;
extern void *D_800B8C88;
extern void *D_800B8C98;
extern PadPort *D_800B8CA8;
extern PadPort D_800EF2D8[2];
extern PadPort D_800EF4B8[2][4];
extern unsigned char D_800EF248[2][35];
extern unsigned char D_800EF290[2][35];

extern void func_800A3134(void);
extern void func_8009E328(void);
extern void bzero_(void *p, int n);
extern void func_8009DD5C(void);
extern void func_8009DC98(void);
extern void func_8009DEB0(void);
extern void func_8009DFC0(void);
extern void func_8009E23C(void);
extern void func_8009E2B8(void);
extern void func_8009DE6C(void);

void func_8009DA78(unsigned char *in0, unsigned char *in1)
{
    PadPort *p;
    PadPort *s;
    unsigned char *q;
    int i;
    int j;
    int k;

    D_800B8CAC = 0;
    D_800B8CC0 = 1;
    func_800A3134();
    D_800B8C74 = func_8009DD5C;
    D_800B8C78 = func_8009DC98;
    D_800B8C7C = func_8009DEB0;
    D_800B8C80 = func_8009DFC0;
    D_800B8C84 = func_8009E23C;
    D_800B8C88 = func_8009E2B8;
    D_800B8CA8 = D_800EF2D8;
    D_800B8C98 = func_8009DE6C;
    bzero_(D_800EF2D8, sizeof(D_800EF2D8));
    bzero_(D_800EF4B8, sizeof(D_800EF4B8));

    p = D_800EF2D8;
        __asm__("" : "=r"(p) : "0"(p));
    p[0].in = in0;
    p[1].in = in1;
    for (i = 0; i < 2; i++, p++) {
        p->sub = D_800EF4B8[i];
        p->parent = p;
        p->in[0] = 0xFF;
        p->in[1] = 0;
        p->act = D_800EF248[i];
        p->mode = D_800EF290[i];
        q = p->state;
        for (j = 5; j >= 0; j--) {
            *q++ = 0xFF;
        }
        s = p->sub;
        for (k = 0; k < 4; k++, s++) {
            s->parent = p;
            s->in = p->in + 2 + k * 8;
            s->unk55 = 0xFF;
            s->unk53 = 0;
            s->unk52 = 0;
            s->in[0] = 0xFF;
            s->in[1] = 0;
            s->act = D_800EF248[i] + 2 + k * 8;
            s->mode = D_800EF290[i] + 3 + k * 8;
            q = s->state;
            for (j = 5; j >= 0; j--) {
                *q++ = 0xFF;
            }
        }
    }
    func_8009E328();
    D_800B8CAC = 1;
}
