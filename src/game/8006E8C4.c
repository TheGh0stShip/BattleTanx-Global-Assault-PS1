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
    char pad12[2];
    unsigned short attr;
    char pad16[0x1F - 0x16];
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

static inline int *tex_base(void) {
    return &D_800ADA04;
}

static inline void set_len(unsigned char *p, int n) {
    p[3] = n;
}

void func_8006E8C4(Model *model) {
    register Model *m asm("$8") = model;
    Vector v;
    register unsigned char *p asm("$5");
    register Part *e asm("$6");

    __asm__("");

    {
        unsigned char *t = alloc_packet(packets(), 12);

        if (t != 0) {
            t[7] = 0xF0;
            *(int *)(t + 8) = -24;
        }
    }
    for (e = m->parts; e != 0; e = e->next) {
        p = alloc_packet(packets(), 32);
        if (p == 0) {
            continue;
        }
        v.x = round_shift(m->x) + e->dx;
        v.y = round_shift(m->y) + e->dy;
        v.z = round_shift(m->z) + e->dz;
        *(Vector *)(p + 8) = v;
        p[4] = e->r;
        p[5] = e->g;
        p[6] = e->b;
        set_len(p, 9);
        p[7] = 0x2C;
        *(short *)(p + 20) = 0;
        p[1] = 0;
        *(short *)(p + 22) = 0;
        {
            int *tp = tex_base();
            int f = D_800ADF48[e->tex][e->frame].arg;
            int t = *tp;

            p[1] = 0;
            *(int *)(p + 28) = t + f * 12;
        }
        *(short *)(p + 22) = e->attr;
        *(short *)(p + 24) = e->size;
        *(short *)(p + 26) = e->size;
        p[7] |= 2;
        *(short *)(p + 20) = (e->flags & 3) << 5;
    }
}
