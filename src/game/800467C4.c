typedef struct {
    unsigned char *start;
    unsigned char *cur;
    int pad8;
    int padC;
    int free;
    int count;
} PacketList;

typedef struct {
    int x, y, z;
} Vector;

typedef struct {
    char pad0[4];
    short x0;
    short x1;
    short y0;
    short y1;
    char padC[0xD0 - 0xC];
} VehicleType;

typedef struct {
    char pad0[6];
    unsigned short angle;
    char pad8[0x9C - 8];
} View;

typedef struct {
    char pad0[8];
    Vector position;
    char pad14[0x2C - 0x14];
    unsigned short heading;
    char pad2E[0x9C - 0x2E];
    int type;
} Tank;

extern PacketList D_800AD9EC;
extern int D_800ADA04;
extern VehicleType D_800A4EF4[];
extern View D_800D3034[];

static inline int round_shift(int d) {
    return d >= 0 ? (d + 2048 >= 0 ? (d + 2048) >> 12 : -(-(d + 2048) >> 12))
                  : (d - 2048 >= 0 ? (d - 2048) >> 12 : -(-(d - 2048) >> 12));
}

static inline PacketList *packets(void) {
    return &D_800AD9EC;
}

static inline int *tex_base(void) {
    return &D_800ADA04;
}

static inline unsigned char *alloc_packet(PacketList *list, int size) {
    unsigned char *p;
    register int rem asm("$2");
    register int left asm("$3");

    rem = list->free;
    left = rem - size;
    p = 0;
    if (left > 0) {
        p = list->cur;
        list->free = left;
        {
            register int c asm("$2") = list->count + 1;
            register unsigned char *n asm("$3") = p + size;

            list->count = c;
            list->cur = n;
        }
        p[0] = size / 4;
        p[2] = 0;
    }
    return p;
}

void func_800467C4(Tank *tank) {
    register Tank *t asm("$8") = tank;
    Vector pos;
    register unsigned char *m asm("$5");
    register unsigned char *d asm("$4");
    register unsigned char *s asm("$6");

    pos.x = round_shift(t->position.x);
    pos.y = 0;
    pos.z = round_shift(t->position.z);
    m = alloc_packet(packets(), 24);
    if (m == 0) {
        return;
    }
    d = alloc_packet(packets(), 12);
    if (d != 0) {
        d[7] = 0xF0;
        *(int *)(d + 8) = 128;
    }
    m[7] = 0xEC;
    *(short *)(m + 8) = 0;
    *(short *)(m + 10) = 4096;
    *(short *)(m + 12) = 0;
    *(short *)(m + 16) = 0;
    *(short *)(m + 18) = 0;
    *(short *)(m + 20) = 4096;
    s = alloc_packet(packets(), 32);
    if (s == 0) {
        return;
    }
    {
        int c = 24;

        *(Vector *)(s + 8) = pos;
        __asm__("");
        s[4] = c;
        s[5] = c;
        s[6] = c;
    }
    *(short *)(s + 24) = (D_800A4EF4[t->type].x1 - D_800A4EF4[t->type].x0) * 3;
    {
        int y1 = D_800A4EF4[t->type].y1;
        int y0 = D_800A4EF4[t->type].y0;

    s[3] = 9;
    s[7] = 0x2C;
    {
        int *tp = tex_base();
        int base;

        s[1] = 0;
        base = *tp;
        *(short *)(s + 20) = 0;
        *(short *)(s + 22) = 0;
        s[1] = 32;
        *(short *)(s + 26) = (y1 - y0) * 3;
        *(int *)(s + 28) = base + 264;
    }
    }
    *(short *)(s + 22) = (D_800D3034[((unsigned char *)D_800D3034)[1]].angle - t->heading) >> 4;
    *(short *)(s + 20) = 64;
    s[7] |= 2;
}
