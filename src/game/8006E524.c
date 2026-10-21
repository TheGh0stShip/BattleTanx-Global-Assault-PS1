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

typedef struct Object Object;

typedef struct {
    int pad0;
    int pad4;
    void (*draw)(Object *);
    int pad0C;
    int visible;
    int width;
    int height;
    int frame;
    unsigned char r, g, b;
    unsigned char flags;
} ObjectType;

struct Object {
    char pad0[7];
    unsigned char type;
    char pad8[8];
    Vector pos;
    int scale;
    char pad20[4];
    int alpha;
};

extern PacketList D_800AD9EC;
extern int D_800ADA04;
extern ObjectType D_800ADF64[];
extern int func_8006A1EC(int, Vector *);

static inline int round_shift(int d) {
    return d >= 0 ? (d + 2048 >= 0 ? (d + 2048) >> 12 : -(-(d + 2048) >> 12))
                  : (d - 2048 >= 0 ? (d - 2048) >> 12 : -(-(d - 2048) >> 12));
}

static inline unsigned char *packet_alloc(int bytes, int words) {
    PacketList *list = &D_800AD9EC;
    register unsigned char *p asm("$4") = 0;
    register int rem asm("$2");
    register int left asm("$3");

    rem = list->free;
    left = rem - bytes;
    if (left > 0) {
        p = list->cur;
        list->free = left;
        {
            register int c asm("$2") = list->count + 1;
            list->cur = p + bytes;
            list->count = c;
        }
        p[0] = words;
        p[2] = 0;
    }
    return p;
}

static inline int *tex_base(void) {
    return &D_800ADA04;
}

static inline void add_marker(void) {
    unsigned char *p = packet_alloc(12, 3);

    if (p != 0) {
        p[7] = 0xF0;
        *(int *)(p + 8) = -24;
    }
}

void func_8006E524(Object *obj) {
    Vector v;
    register unsigned char *p asm("$6");

    if (func_8006A1EC(0, &obj->pos) == 0) {
        return;
    }
    if (D_800ADF64[obj->type].visible != 0 && obj->alpha > 0) {
        add_marker();
        p = packet_alloc(32, 8);
        if (p != 0) {
            v.x = round_shift(obj->pos.x);
            v.y = round_shift(obj->pos.y);
            v.z = round_shift(obj->pos.z);
            *(Vector *)(p + 8) = v;
            __asm__("");
            p[4] = D_800ADF64[obj->type].r;
            p[5] = D_800ADF64[obj->type].g;
            p[6] = D_800ADF64[obj->type].b;
            p[3] = 9;
            p[7] = 0x2C;
            *(short *)(p + 20) = 0;
            p[1] = 0;
            *(short *)(p + 22) = 0;
            {
                int *tp = tex_base();
                int f = D_800ADF64[obj->type].frame;
                int t = *tp;
                p[1] = 0;
                *(short *)(p + 22) = 0;
                *(int *)(p + 28) = t + f * 12;
            }
            *(short *)(p + 24) = D_800ADF64[obj->type].width * obj->scale / 4096;
            *(short *)(p + 26) = D_800ADF64[obj->type].height * obj->scale / 4096;
            p[7] |= 2;
            *(short *)(p + 20) = (D_800ADF64[obj->type].flags & 3) << 5;
        }
    }
    D_800ADF64[obj->type].draw(obj);
}
