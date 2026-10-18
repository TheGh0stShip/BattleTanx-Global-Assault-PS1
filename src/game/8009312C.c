extern void func_8009B918(void *);
extern int func_80092C20(void);
extern int func_80092D3C(void);
extern int func_80092DF0(void *, void *);

typedef struct {
    char pad0[16];
    unsigned int format;
    char pad20[16];
    int width;
    int height;
    int flags;
    char pad48[4];
    int w52;
    void *buf0;
    void *buf1;
    void *buf2;
    void *buf3;
    void *buf4;
    int w76;
    char pad80[4];
    int w84;
    int w88;
} Req8009312C;

typedef struct {
    char pad0[32];
    char data[32];
} Slot8009312C;

typedef struct {
    char pad0[2];
    unsigned char busy;
    char pad3[9];
    Req8009312C *req;
    char pad16[20];
    int stride;
    char pad40[4];
    void *bufs[2];
    int cur;
    struct Slot8009312C_ {
        char data[32];
    } slots[2];
    int w120;
    void *buf2;
    void *buf3;
    int w132;
    void *buf4;
    int w140;
    short h144;
    short h146;
} S8009312C;
extern S8009312C D_800EEF0C;

int func_8009312C(Req8009312C *p, void *buf0, void *buf1, int width, void *buf2, void *buf3, int height, void *buf4, int flags, int w84, int w76) {
    S8009312C *g = &D_800EEF0C;
    int r = 0;

    if (g->busy == 0) {
        p->w52 = 0;
        p->buf0 = buf0;
        p->buf1 = buf1;
        p->width = width;
        p->buf2 = buf2;
        p->buf3 = buf3;
        p->height = height;
        p->buf4 = buf4;
        p->flags = flags;
        p->w84 = w84;
        p->w76 = w76;
        p->w88 = 0;
        g->req = p;
        g->stride = (p->format << 4) >> 1;
        g->h144 = 0;
        g->h146 = 0;
        g->w140 = 0;
        g->bufs[0] = buf0;
        g->bufs[1] = buf1;
        g->buf2 = buf2;
        g->buf3 = buf3;
        g->buf4 = buf4;
        func_8009B918(buf4);
        g->cur = 0;
        g->w132 = 0;
        g->w120 = 0;
        r = func_80092C20();
        if (r != 0) {
            r = func_80092D3C();
            if (r != 0) {
                r = func_80092DF0(D_800EEF0C.bufs[D_800EEF0C.cur], &D_800EEF0C.slots[D_800EEF0C.cur]);
            }
        }
    }
    return r;
}
