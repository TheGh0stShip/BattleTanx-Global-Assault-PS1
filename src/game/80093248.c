extern void func_80092CD0(void);
extern void func_8009C52C(void *, int);
extern void func_8009C5A8(void *);
extern int func_80092DF0(void *, void *);

typedef struct {
    unsigned int w0;
    int w4;
    char pad8[8];
    unsigned int format;
    int rate;
    int base;
    char pad28[60];
    int time;
    char pad92[8];
    int flags;
} Req80093248;

typedef struct {
    char pad0[16];
    unsigned short w;
    unsigned short h;
    char pad20[12];
} Slot80093248;

typedef struct {
    char pad0[2];
    unsigned char busy;
    volatile unsigned char decoding;
    unsigned char b4;
    char pad5[7];
    Req80093248 *req;
    unsigned int w16;
    int w20;
    unsigned int w24;
    unsigned int stride;
    unsigned int w32;
    char pad36[8];
    void *bufs[2];
    int cur;
    Slot80093248 slots[2];
    int w120;
    void *out[2];
    int w132;
    char pad136[4];
    unsigned int frame;
    unsigned short x;
    unsigned short y;
} S80093248;
extern S80093248 D_800EEF0C;

int func_80093248(Req80093248 *p, int x, int y, int dt) {
    S80093248 *g = &D_800EEF0C;
    S80093248 *g2;
    S80093248 *g3;
    int r = 0;
    int mode;
    unsigned int t;
    S80093248 *q;
    Slot80093248 *sl;

    if (g->busy != 0) {
        if (g->req != p) {
            return r;
        }
        if (g->b4 == 0) {
            p->time += dt;
            if (g->frame < p->base + (unsigned int)(p->rate * p->time) / 1000 + 1) {
                g->x = x;
                g->y = y;
                if (p->format == 3) {
                    if (((unsigned short)x + p->w0) & 1) {
                        p->w0--;
                    }
                }
                g2 = &D_800EEF0C;
                t = (p->w0 * p->format) >> 1;
                g2->w16 = t;
                g2->w20 = p->w4;
                g2->w24 = t;
                if (p->format == 3) {
                    mode = 1;
                } else {
                    mode = (p->flags & 1) << 1;
                }
                g3 = &D_800EEF0C;
                D_800EEF0C.decoding = 1;
                func_8009C52C(D_800EEF0C.bufs[D_800EEF0C.cur], mode);
                D_800EEF0C.w120 = D_800EEF0C.cur;
                D_800EEF0C.w32 = (D_800EEF0C.slots[D_800EEF0C.cur].w * p->format) >> 1;
                {
                    register unsigned int st asm("$5") = ((D_800EEF0C.slots[D_800EEF0C.cur].h * p->format) << 4) >> 2;
                    D_800EEF0C.stride = st;
                }
                func_8009C5A8(D_800EEF0C.out[D_800EEF0C.w132]);
                D_800EEF0C.cur ^= 1;
                func_80092DF0(D_800EEF0C.bufs[D_800EEF0C.cur], &D_800EEF0C.slots[D_800EEF0C.cur]);
                if (g3->decoding != 0) {
                    q = g3;
                    while (q->decoding != 0) {
                    }
                }
                r = 1;
            }
        } else {
            func_80092CD0();
        }
    }
    return r;
}
