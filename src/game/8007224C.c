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
    char pad00[6];
    short size;
    int texture;
    char pad0C[8];
    Vector pos;
    short rx, ry, rz;
    short pad26;
    short tx, ty, tz;
    short pad2E;
    char pad30[7];
    unsigned char r, g, b;
} Sprite;

typedef struct {
    char pad00[24];
    short index;
    char pad1A[2];
} TexInfo;

extern PacketList D_800AD9EC;
extern int D_800ADA04;
extern TexInfo D_800AE184[];

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

static inline void prim_clear(unsigned char *q) {
    q[1] = 0;
    *(short *)(q + 20) = 0;
    *(short *)(q + 22) = 0;
}

static inline unsigned char *alloc_packet(PacketList *list, int size) {
    register unsigned char *p asm("$4") = 0;
    register int rem asm("$2");
    register int left asm("$3");

    rem = list->free;
    left = rem - size;
    if (left > 0) {
        p = list->cur;
        list->free = left;
        {
            register int c asm("$2") = list->count + 1;
            list->cur = p + size;
            list->count = c;
        }
        p[0] = size / 4;
        p[2] = 0;
    }
    return p;
}

void func_8007224C(Sprite *sprite) {
    register Sprite *s asm("$8") = sprite;
    Vector pos;
    register unsigned char *m asm("$4");
    unsigned char *p;

    pos.x = round_shift(s->pos.x);
    pos.y = round_shift(s->pos.y);
    pos.z = round_shift(s->pos.z);
    m = alloc_packet(packets(), 24);
    if (m == 0) {
        return;
    }
    m[7] = 0xEC;
    *(short *)(m + 8) = s->rx;
    *(short *)(m + 10) = s->ry;
    *(short *)(m + 12) = s->rz;
    *(short *)(m + 16) = s->tx;
    *(short *)(m + 18) = s->ty;
    *(short *)(m + 20) = s->tz;
    m = alloc_packet(packets(), 12);
    if (m != 0) {
        m[7] = 0xF0;
        *(int *)(m + 8) = -32;
    }
    p = alloc_packet(packets(), 32);
    if (p != 0) {
        int *tp = tex_base();
        int idx;
        int base;

        *(Vector *)(p + 8) = pos;
        p[4] = s->r;
        p[5] = s->g;
        p[6] = s->b;
        *(short *)(p + 24) = s->size / 2;
        *(short *)(p + 26) = s->size / 2;
        idx = D_800AE184[s->texture].index;
        base = *tp;
        p[3] = 9;
        p[7] = 0x2C;
        prim_clear(p);
        p[1] = 0x44;
        *(short *)(p + 22) = 0;
        *(short *)(p + 20) = 32;
        *(int *)(p + 28) = base + idx * 12;
        p[7] |= 2;
    }
    p = alloc_packet(packets(), 32);
    if (p != 0) {
        int *tp = tex_base();
        int idx;
        int base;

        *(Vector *)(p + 8) = pos;
        p[4] = s->r;
        p[5] = s->g;
        p[6] = s->b;
        *(short *)(p + 24) = -s->size / 2;
        *(short *)(p + 26) = s->size / 2;
        idx = D_800AE184[s->texture].index;
        base = *tp;
        p[3] = 9;
        p[7] = 0x2C;
        prim_clear(p);
        p[1] = 0x44;
        *(short *)(p + 22) = 0;
        *(short *)(p + 20) = 32;
        *(int *)(p + 28) = base + idx * 12;
        p[7] |= 2;
    }
    p = alloc_packet(packets(), 32);
    if (p != 0) {
        int *tp = tex_base();
        int idx;
        int base;

        *(Vector *)(p + 8) = pos;
        p[4] = s->r;
        p[5] = s->g;
        p[6] = s->b;
        *(short *)(p + 24) = s->size / 2;
        *(short *)(p + 26) = -s->size / 2;
        idx = D_800AE184[s->texture].index;
        base = *tp;
        p[3] = 9;
        p[7] = 0x2C;
        prim_clear(p);
        p[1] = 0x44;
        *(short *)(p + 22) = 0;
        *(short *)(p + 20) = 32;
        *(int *)(p + 28) = base + idx * 12;
        p[7] |= 2;
    }
    p = alloc_packet(packets(), 32);
    if (p != 0) {
        int *tp = tex_base();
        int idx;
        int base;

        *(Vector *)(p + 8) = pos;
        p[4] = s->r;
        p[5] = s->g;
        p[6] = s->b;
        *(short *)(p + 24) = -s->size / 2;
        *(short *)(p + 26) = -s->size / 2;
        idx = D_800AE184[s->texture].index;
        base = *tp;
        p[3] = 9;
        p[7] = 0x2C;
        prim_clear(p);
        p[1] = 0x44;
        *(short *)(p + 22) = 0;
        *(short *)(p + 20) = 32;
        *(int *)(p + 28) = base + idx * 12;
        p[7] |= 2;
    }
}
