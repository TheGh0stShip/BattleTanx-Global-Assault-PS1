typedef struct {
    unsigned char *start;
    unsigned char *cur;
    int pad8;
    int padC;
    int free;
    int count;
} PacketList;

typedef struct Part Part;
struct Part {
    Part *next;
    int pad4;
    int pad8;
    short dx, dy, dz;
    char pad12[0x1F - 0x12];
    unsigned char flags;
    unsigned short size;
    char pad22[2];
    unsigned char r, g, b;
    unsigned char tex;
    unsigned char frame;
};

typedef struct {
    int pad0;
    int pad4;
    int pad8;
    Part *parts;
    int x, y, z;
} Model;

typedef struct {
    int x, y, z;
} Vector;

extern PacketList D_800AD9EC;
extern int D_800ADA04;
typedef struct {
    short cmd;
    unsigned char arg;
    unsigned char value;
} AnimStep;

extern AnimStep *D_800ADF48[];

static inline int round_shift(int d) {
    return d >= 0 ? (d + 2048 >= 0 ? (d + 2048) >> 12 : -(-(d + 2048) >> 12))
                  : (d - 2048 >= 0 ? (d - 2048) >> 12 : -(-(d - 2048) >> 12));
}

static inline PacketList *packets(void) {
    return &D_800AD9EC;
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

static inline unsigned char *alloc_child(PacketList *list, int size) {
    unsigned char *p;
    register int left asm("$2");

    left = list->free - size;
    p = 0;
    if (left > 0) {
        p = list->cur;
        list->free = left;
        {
            register int c asm("$3") = list->count + 1;
            register unsigned char *n asm("$2") = p + size;

            list->cur = n;
            list->count = c;
        }
        p[0] = size / 4;
        p[2] = 0;
    }
    return p;
}

static inline int tex_addr(int anim, int frame) {
    return D_800ADA04 + D_800ADF48[anim][frame].arg * 12;
}

static inline void set_len(unsigned char *p, int n) {
    p[3] = n;
}

void func_8006EB4C(Model *model) {
    register Model *m asm("$9") = model;
    Vector v;
    unsigned char *p;
    unsigned char *q;
    Part *e;
    register int i asm("$11");
    register int mode asm("$5");

    if (m->parts == 0) {
        return;
    }
    {
        unsigned char *t = alloc_packet(packets(), 12);

        if (t != 0) {
            t[7] = 0xF0;
            *(int *)(t + 8) = -24;
        }
    }
    for (i = 0; i < 2; i++) {
        mode = 16;
        if (i == 0) {
            mode = 32;
        }
        e = m->parts;
        v.x = round_shift(m->x) + e->dx;
        v.y = round_shift(m->y) + e->dy;
        v.z = round_shift(m->z) + e->dz;
        if (e->tex == 255) {
            p = alloc_packet(packets(), 40);
            if (p == 0) {
                goto next;
            }
            *(Vector *)(p + 8) = v;
            p[4] = e->r;
            p[5] = e->g;
            p[6] = e->b;
            p[28] = e->r;
            p[29] = e->g;
            p[30] = e->b;
            set_len(p, 8);
            p[7] = 0x38;
            *(short *)(p + 20) = 0;
            p[1] = 0;
            *(short *)(p + 22) = 0;
            p[1] = mode;
        } else {
            p = alloc_packet(packets(), 44);
            if (p == 0) {
                goto next;
            }
            *(Vector *)(p + 8) = v;
            p[4] = e->r;
            p[5] = e->g;
            p[6] = e->b;
            p[32] = e->r;
            p[33] = e->g;
            p[34] = e->b;
            set_len(p, 12);
            p[7] = 0x3C;
            *(short *)(p + 20) = 0;
            p[1] = 0;
            *(short *)(p + 22) = 0;
            *(int *)(p + 28) = tex_addr(e->tex, e->frame);
            p[1] = mode;
        }
        *(short *)(p + 24) = e->size;
        *(short *)(p + 26) = e->size;
        *(short *)(p + 22) = 0;
        p[7] |= 2;
        *(short *)(p + 20) = (e->flags & 3) << 5;
    next:
        while ((e = e->next) != 0) {
            v.x = round_shift(m->x) + e->dx;
            v.y = round_shift(m->y) + e->dy;
            v.z = round_shift(m->z) + e->dz;
            if (e->tex == 255) {
                if (p[0] + 8 >= 255) {
                    continue;
                }
                q = alloc_child(packets(), 32);
                if (q == 0) {
                    continue;
                }
                *(Vector *)(q + 8) = v;
                *(volatile unsigned char *)(q + 4) = e->r;
                q[5] = e->g;
                q[6] = e->b;
                q[28] = e->r;
                q[29] = e->g;
                q[30] = e->b;
                *(short *)(q + 24) = e->size;
                *(short *)(q + 26) = e->size;
                q[7] = 0x38;
                *(short *)(q + 22) = 0;
                p[0] += *(volatile unsigned char *)q;
                p[2]++;
                q[7] |= 2;
                *(short *)(q + 22) = 0;
            } else {
                if (p[0] + 8 >= 255) {
                    continue;
                }
                q = alloc_child(packets(), 32);
                if (q == 0) {
                    continue;
                }
                *(Vector *)(q + 8) = v;
                *(volatile unsigned char *)(q + 4) = e->r;
                q[5] = e->g;
                q[6] = e->b;
                q[28] = e->r;
                q[29] = e->g;
                q[30] = e->b;
                q[7] = 0x3C;
                *(short *)(q + 22) = 0;
                *(short *)(q + 24) = e->size;
                *(short *)(q + 26) = e->size;
                p[0] += *(volatile unsigned char *)q;
                p[2]++;
                q[7] |= 2;
                *(short *)(q + 22) = 0;
            }
        }
    }
}
