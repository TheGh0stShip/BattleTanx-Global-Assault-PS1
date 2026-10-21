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
    int pad0;
    int pad4;
    int x, y, z;
    char pad14[0x20 - 0x14];
    int fade;
    char pad24[0x2A - 0x24];
    short frame;
} Flash;

extern PacketList D_800AD9EC;
extern int D_800ADA04;

extern int abs(int);

static inline int round_shift(int d) {
    return d >= 0 ? (d + 2048 >= 0 ? (d + 2048) >> 12 : -(-(d + 2048) >> 12))
                  : (d - 2048 >= 0 ? (d - 2048) >> 12 : -(-(d - 2048) >> 12));
}

static inline void gte_ldlzc(unsigned int v) {
    __asm__ volatile("mtc2 %0, $30\n\tnop\n\tnop" : : "r"(v));
}

static inline void gte_stlzc(int *out) {
    __asm__ volatile("swc2 $31, 0(%0)" : : "r"(out));
}

static inline unsigned char *packet_alloc(PacketList *list, int size) {
    register unsigned char *p asm("$6");
    unsigned char *q;

    q = (unsigned char *)(list->free - size);
    p = 0;
    if ((int)q > 0) {
        p = list->cur;
        list->free = (int)q;
        {
            register int count asm("$2") = list->count + 1;
            register unsigned char *next asm("$3") = p + size;

            list->count = count;
            list->cur = next;
        }
        p[0] = size >> 2;
        p[2] = 0;
    }
    return p;
}

void func_800732E4(Flash *f) {
    Vector v;
    int level;
    unsigned char *p;
    register unsigned char *q asm("$5");
    int left;
    PacketList *list;
    int scale;
    int a;
    register int b asm("$6");
    unsigned int sign;
    unsigned int ua;
    int sb;
    int lza;
    int lzb;
    int k;
    int d;

    a = f->fade;
    b = 0x10000;
    sign = (a & 0x80000000) ^ (b & 0x80000000);
    sb = b;
    __asm__("" : : "r"(sign));
    ua = abs(a);
    gte_ldlzc(ua);
    gte_stlzc(&lza);
    level = lza - 12;
    if (level < 0) {
        ua <<= lza;
        gte_ldlzc(sb);
        gte_stlzc(&lzb);
        k = lzb - lza;
        if (k >= 0) {
            d = 12 - lzb;
            if (d >= 0) {
                d = sb >> d;
            } else {
                d = sb << -d;
            }
            ua = ua / d;
            ua <<= k;
        } else {
            d = sb >> -level;
            ua = ua / d;
        }
    } else {
        ua <<= 12;
        ua = ua / b;
    }
    level = ua;
    if (sign) {
        level = -level;
    }
    if (level < 0) {
        level = 0;
    }
    v.x = round_shift(f->x);
    v.y = round_shift(f->y);
    v.z = round_shift(f->z);
    p = packet_alloc(&D_800AD9EC, 32);
    q = p;
    if (q == 0) {
        return;
    }
    *(Vector *)(q + 8) = v;
    q[4] = level / 32;
    q[5] = level / 32;
    q[6] = level / 32;
    q[3] = 9;
    q[7] = 0x2C;
    q[1] = 0;
    *(int *)(q + 28) = D_800ADA04 + 48;
    *(short *)(q + 20) = 0;
    *(short *)(q + 22) = 0;
    q[1] = 0;
    *(short *)(q + 22) = f->frame;
    scale = (4096 - level) * 384 / 4096;
    *(short *)(q + 24) = (4096 - level) * 384 / 4096;
    *(short *)(p + 26) = scale;
    *(short *)(p + 20) = 32;
    p[7] |= 2;
}
