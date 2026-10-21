typedef struct {
    unsigned char *start;
    unsigned char *cur;
    int pad8;
    int padC;
    int free;
    int count;
} PacketList;

typedef struct {
    char pad[0x18];
    short frame;
    char pad1A[2];
} EffectDef;

typedef struct {
    int pad0;
    short pad4;
    unsigned short angle;
    int kind;
    int padC;
    int pad10;
    int x, y, z;
    short a0, a1, a2;
    short pad26;
    short b0, b1, b2;
    char pad2E[0x37 - 0x2E];
    unsigned char r, g, b;
} Sprite;

typedef struct {
    int x, y, z;
} Vector;

extern PacketList D_800AD9EC;
extern int D_800ADA04;
extern EffectDef D_800AE184[];

static inline int round_shift(int d) {
    return d >= 0 ? (d + 2048 >= 0 ? (d + 2048) >> 12 : -(-(d + 2048) >> 12))
                  : (d - 2048 >= 0 ? (d - 2048) >> 12 : -(-(d - 2048) >> 12));
}

static inline unsigned char *alloc_packet(int size, int code) {
    PacketList *list = &D_800AD9EC;
    unsigned char *p = 0;
    register int rem asm("$2");
    register int left asm("$3");

    rem = list->free;
    left = rem - size;
    if (left > 0) {
        p = list->cur;
        list->free = left;
        {
            register int c asm("$2") = list->count + 1;
            register unsigned char *n asm("$3") = p + size;

            list->count = c;
            list->cur = n;
        }
        p[0] = code;
        p[2] = 0;
    }
    return p;
}

void func_800728E8(Sprite *s) {
    Vector v;
    unsigned char *p;
    unsigned char *q;
    unsigned char *r;
    volatile unsigned char *vr;
    register int *texp asm("$5");
    int frame;
    int tex;

    v.x = round_shift(s->x);
    v.y = round_shift(s->y);
    v.z = round_shift(s->z);
    p = alloc_packet(24, 6);
    if (p == 0) {
        return;
    }
    p[7] = 0xEC;
    *(short *)(p + 8) = s->a0;
    *(short *)(p + 10) = s->a1;
    *(short *)(p + 12) = s->a2;
    *(short *)(p + 16) = s->b0;
    *(short *)(p + 18) = s->b1;
    *(short *)(p + 20) = s->b2;
    q = alloc_packet(12, 3);
    if (q != 0) {
        q[7] = 0xF0;
        *(int *)(q + 8) = 0;
    }
    r = alloc_packet(32, 8);
    if (r == 0) {
        return;
    }
    vr = r;
    *(Vector *)(r + 8) = v;
    r[4] = s->r;
    r[5] = s->g;
    r[6] = s->b;
    *(short *)(r + 24) = s->angle;
    *(short *)(r + 26) = s->angle;
    texp = (int *)0x800B0000;
    frame = D_800AE184[s->kind].frame;
    __asm__("" : "+r"(texp) : "r"(frame));
    tex = *(int *)((char *)texp - 9724);
    vr[3] = 9;
    vr[7] = 0x2C;
    vr[1] = 0;
    vr[1] = 64;
    *(volatile short *)(r + 20) = 0;
    *(volatile short *)(r + 22) = 0;
    *(volatile short *)(r + 22) = 0;
    *(volatile short *)(r + 20) = 32;
    *(int *)(r + 28) = tex + frame * 12;
    vr[7] |= 2;
}
