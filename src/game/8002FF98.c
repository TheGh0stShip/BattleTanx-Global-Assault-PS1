typedef struct { int x; int z; int pad; int y; int pad2[2]; unsigned short angle; } Frame;
typedef struct { int pad[2]; Frame frame; } Body;
typedef struct {
    int pad[2];
    Body *body;
    int pad2;
    int offset;
    int width;
    int length;
    int height;
    short handle;
} Seg;
int func_8008AD60(int);
int func_8008ACC0(int);
short func_800162F0(Seg *, int, int, int, int, int, int, int, int, int, int, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

static inline short quarter(int v) {
    return (to_int(v) << 14) >> 16;
}

void func_8002FF98(Seg *s) {
    Body *body = s->body;
    Frame *f = &body->frame;
    int reach;
    int x;
    int z;

    reach = s->offset + s->length / 2;
    x = body->frame.x + fixed_mul(reach, func_8008AD60(f->angle >> 4));
    z = f->z + fixed_mul(reach, func_8008ACC0(f->angle >> 4));
    s->handle = func_800162F0(s, quarter(x), quarter(z), quarter(f->y), (short)(-quarter(s->width) / 2),
                              quarter(s->width) / 2, (short)(-quarter(s->length) / 2), quarter(s->length) / 2, 0,
                              quarter(s->height), f->angle, 0x200000);
}
