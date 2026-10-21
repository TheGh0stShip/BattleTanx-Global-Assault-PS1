typedef struct {
    short x, y, w, h;
} Rect;

typedef struct {
    int f0;
    int f4;
    unsigned short w;
    unsigned short h;
    int pad[5];
} StrmEntry;

typedef struct {
    int f0[4];
    int f16;
} StrmCtl;

typedef struct {
    volatile unsigned char done;
    volatile unsigned char ready;
    volatile unsigned char busy;
    unsigned char active;
    int f4;
    int f8;
    StrmCtl *ctl;
    unsigned int start;
    int y;
    unsigned int cur;
    int step;
    unsigned int count;
    int width;
    int f40;
    int f44;
    int f48;
    int f52;
    int f56;
    short f60;
    unsigned short div;
    StrmEntry ent[1];
    int f96;
    int f100;
    int f104;
    int f108;
    int f112;
    int f116;
    int index;
    int buf[2];
    int side;
    int f136;
    int f140;
    unsigned short ox;
    unsigned short oy;
} StrmGlobal;

typedef struct {
    int f0;
    int f4;
    int w;
    int h;
    int arg;
    int f20;
    int f24;
    int f28;
    int f32;
    int f36;
    int f40;
    int f44;
    int f48;
    int pad[6];
    int f76;
    int f80;
    int f84;
    int f88;
    int start;
    int end;
    int f100;
    char *name;
} Strm;

extern StrmGlobal D_800EEF0C;
extern int D_800EF204;

extern void func_8008AA48(void *, int, int);
extern void func_800919D8(void);
extern void func_80091984(void);
extern int func_800982B0(char *, unsigned int *, unsigned int *);
extern void func_800916F4(void);
extern void func_8009759C(int, char *);
extern int func_800973AC(int, void *, int);
extern int func_8009702C(void);
extern int func_8009162C(void (*)(void));
extern int func_80091618(void (*)(void));
extern void func_800927E4(void);
extern void func_800927C8(void);
extern void func_8009166C(void);
extern int func_8009278C(Strm *, int);
extern void func_8009BA08(void);
extern void func_8009C5A8(int, int);
extern void func_8007FC88(Rect *, int);

void func_80092AFC(void)
{
    Rect r;
    int next;
    unsigned int cur;

    if (D_800EEF0C.ctl->f16 == 3 && D_800EF204 != 0) {
        func_8009BA08();
        *(int *)0x800EF204 = 0;
    }
    {
        unsigned short ox = D_800EEF0C.ox;
        cur = D_800EEF0C.cur;
        r.x = ox + cur;
    }
    {
        unsigned short oy = D_800EEF0C.oy;
        int y = D_800EEF0C.y;
        r.y = oy + y;
    }
    r.w = D_800EEF0C.width;
    r.h = D_800EEF0C.ent[D_800EEF0C.index].h;
    D_800EEF0C.cur = cur + D_800EEF0C.width;
    next = D_800EEF0C.side ^ 1;
    if (D_800EEF0C.cur < D_800EEF0C.start + D_800EEF0C.count) {
        func_8009C5A8(D_800EEF0C.buf[next], D_800EEF0C.step);
    } else {
        D_800EEF0C.active = 0;
        D_800EEF0C.cur = D_800EEF0C.start;
    }
    func_8007FC88(&r, D_800EEF0C.buf[D_800EEF0C.side]);
    D_800EEF0C.side = next;
}
