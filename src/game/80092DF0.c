extern int func_8009CF0C(int *, void *);
extern int func_800973AC(int, unsigned char *, unsigned char *);
extern unsigned int func_800976A0(unsigned char *);
extern void func_8008A7BC(void *, void *, int);
extern void func_8009CAEC(int, void *, int);
extern void func_8009CFCC(int);

typedef struct {
    unsigned short h0;
    unsigned short h2;
    char pad4[4];
    unsigned int frame;
    char pad12[4];
    unsigned short w;
    unsigned short h;
} Hdr80092DF0;

typedef struct {
    char pad0[8];
    unsigned int w;
    unsigned int h;
    char pad16[8];
    int frames;
    unsigned int last;
    char pad32[60];
    unsigned int lo;
    unsigned int hi;
} Req80092DF0;

typedef struct {
    char pad0[4];
    volatile unsigned char stop;
    char pad5[3];
    int dropped;
    Req80092DF0 *req;
    char pad16[24];
    unsigned short id0;
    unsigned short id1;
    char pad44[92];
    int mode;
    unsigned int frame;
} S80092DF0;
extern S80092DF0 D_800EEF0C;

int func_80092DF0(void *dst, void *slot) {
    S80092DF0 *g = &D_800EEF0C;
    S80092DF0 *q;
    S80092DF0 *g2;
    unsigned char loc[8];
    int addr;
    Hdr80092DF0 *hdr;
    int ok = 1;
    int timeout;
    int done;
    int poll;
    unsigned int pos;

    if (g->stop == 0) {
        timeout = 0x400000;
        done = (g->req->last > g->frame + ok) ^ ok;
        poll = ok;
        if (!done) {
            q = g;
            do {
                if (func_8009CF0C(&addr, &hdr) == 0) {
                    break;
                }
                timeout--;
                poll--;
                if (timeout == 0) {
                    ok = 0;
                    done = 1;
                } else if (poll == 0 && q->frame != 0 && func_800973AC(16, 0, loc) != 0) {
                    pos = func_800976A0(loc);
                    if (pos < q->req->lo || pos >= q->req->hi) {
                        done = 1;
                    }
                    poll = 20480;
                }
            } while (!done);
            if (!done) {
                g2 = &D_800EEF0C;
                if (g2->frame == 0) {
                    g2->id0 = hdr->h2;
                    g2->id1 = hdr->h0;
                    g2->frame = g2->req->frames - 1;
                }
                if (hdr->h2 == g2->id0 && hdr->h0 == g2->id1 && hdr->w == g2->req->w && hdr->h == g2->req->h && hdr->frame > g2->frame) {
                    if (hdr->frame != g2->frame + 1) {
                        g2->dropped++;
                    }
                    g2->frame = hdr->frame;
                    func_8008A7BC(slot, hdr, 32);
                    func_8009CAEC(addr, dst, g2->mode);
                } else {
                    done = 1;
                }
                func_8009CFCC(addr);
                if (!done) {
                    return ok;
                }
            }
        }
        D_800EEF0C.stop = 1;
    }
    return ok;
}
