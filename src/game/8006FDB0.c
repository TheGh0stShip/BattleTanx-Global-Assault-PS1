typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    char pad0[8];
    int type;
    Vector pos;
    int state;
    int color;
    int extra;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    char pad27;
    int timer;
} Blast;

typedef struct {
    char pad0[4];
    int color;
    int extra;
    char pad0C[449 - 12];
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Ambient;

typedef struct {
    Ambient *ambient;
} AmbientRef;

extern AmbientRef D_800D2FE4;
extern int D_800EAC1C;
extern void *func_800237D0(int kind, int size);
extern unsigned int func_80086C84(void);
extern void *func_8006C334(void *src, int kind, Vector *a, Vector *b, int unused, int param, int life, int scale);
extern void func_800718A4(int type, Vector *pos, void *dir, int scale, int attached);
extern void func_80072C50(int type, Vector *pos, void *dir, int scale);

static inline int rand_scaled(int n) {
    return (int)(func_80086C84() >> 16) * n >> 16;
}

void func_8006FDB0(int type, Vector *pos, Vector *off, int attached) {
    Blast *b;
    Vector lo;
    Vector hi;

    b = func_800237D0(66, 44);
    if (b == 0) {
        return;
    }
    b->type = type;
    b->state = 0;
    b->pos = *pos;
    if (off == 0) {
        lo = *pos;
        hi = *pos;
    } else {
        lo.x = pos->x - off->x;
        lo.y = pos->y - off->y;
        lo.z = pos->z - off->z;
        hi.x = pos->x + off->x;
        hi.y = pos->y + off->y;
        hi.z = pos->z + off->z;
    }
    switch (type) {
    case 3: {
        Vector v;

        v = *pos;
        if (off != 0) {
            v.y -= off->y;
        }
        func_800718A4(2, &v, 0, 6144, attached);
    }
    case 1:
        func_8006C334(0, 6, &lo, &hi, 0, ((int)(func_80086C84() >> 16) * 2049 >> 16) + 5120, 16384, 4096);
        func_8006C334(0, 2, &lo, &hi, 0, ((int)(func_80086C84() >> 16) * 2049 >> 16) | 0x2000, 4096, 0x10000);
        break;
    case 2:
        func_8006C334(0, 6, &lo, &hi, 0, ((int)(func_80086C84() >> 16) * 2049 >> 16) + 5120, 16384, 4096);
        func_8006C334(0, 8, &lo, &hi, 0, ((int)(func_80086C84() >> 16) * 2049 >> 16) + 11264, 4096, 0x10000);
        break;
    case 4:
        func_8006C334(0, 6, pos, pos, 0, 4096, 4096, 4096);
        func_8006C334(0, 1, pos, pos, 0, 9216, 1024, 0x10000);
        break;
    case 0:
    case 5:
        func_8006C334(0, 2, &lo, &hi, 0, ((int)(func_80086C84() >> 16) * 2049 >> 16) | 0x2000, 16384, 4096);
        break;
    case 6:
        func_8006C334(0, 6, pos, pos, 0, 5120, 4096, 4096);
        func_8006C334(0, 2, pos, pos, 0, 8192, 1024, 0x10000);
        func_800718A4(0, pos, 0, 2816, 0);
        func_80072C50(0, pos, 0, ((int)(func_80086C84() >> 16) * 1537 >> 16) + 3584);
        func_80072C50(0, pos, 0, ((int)(func_80086C84() >> 16) * 1537 >> 16) + 3584);
        func_80072C50(0, pos, 0, ((int)(func_80086C84() >> 16) * 1537 >> 16) + 3584);
        func_80072C50(0, pos, 0, ((int)(func_80086C84() >> 16) * 1537 >> 16) + 3584);
        break;
    case 7:
        func_8006C334(0, 6, pos, pos, 0, 7680, 4096, 4096);
        func_8006C334(0, 2, pos, pos, 0, 12288, 1024, 0x10000);
        func_800718A4(0, pos, 0, 4096, 0);
        func_80072C50(0, pos, 0, ((int)(func_80086C84() >> 16) * 1537 >> 16) + 3584);
        func_80072C50(0, pos, 0, ((int)(func_80086C84() >> 16) * 1537 >> 16) + 3584);
        func_80072C50(0, pos, 0, ((int)(func_80086C84() >> 16) * 1537 >> 16) + 3584);
        func_80072C50(0, pos, 0, ((int)(func_80086C84() >> 16) * 1537 >> 16) + 3584);
        func_80072C50(0, pos, 0, ((int)(func_80086C84() >> 16) * 1537 >> 16) + 3584);
        break;
    case 8:
        func_8006C334(0, 2, pos, pos, 0, 4096, 8192, 4096);
        break;
    case 9:
        func_8006C334(0, 6, pos, pos, 0, 6144, 4096, 4096);
        func_8006C334(0, 2, pos, pos, 0, 10240, 1024, 0x10000);
        break;
    case 10: {
        Vector v;

        func_8006C334(0, 6, pos, pos, 0, 16384, 4096, 4096);
        func_8006C334(0, 2, pos, pos, 0, 24576, 8192, 4096);
        lo.x = pos->x - 0x400000;
        lo.y = pos->y;
        lo.z = pos->z - 0x400000;
        hi.x = pos->x + 0x400000;
        hi.y = lo.y + 0x200000;
        hi.z = pos->z + 0x400000;
        func_8006C334(0, 6, &lo, &hi, 0, 12288, 0x20000, 8192);
        func_8006C334(0, 3, &lo, &hi, 0, 12288, 0x20000, 8192);
        v = *pos;
        func_800718A4(3, &v, 0, 4096, attached);
        v.y += 0x180000;
        func_800718A4(3, &v, 0, 2560, 0);
        b->r = D_800D2FE4.ambient->r;
        b->g = D_800D2FE4.ambient->g;
        b->b = D_800D2FE4.ambient->b;
        b->color = D_800D2FE4.ambient->color;
        b->extra = D_800D2FE4.ambient->extra;
        D_800EAC1C = 1;
        b->timer = 0;
        break;
    }
    case 11: {
        Vector v;

        func_8006C334(0, 6, pos, pos, 0, 12288, 4096, 4096);
        func_8006C334(0, 2, pos, pos, 0, 18432, 8192, 4096);
        lo.x = pos->x - 0x200000;
        lo.y = pos->y;
        lo.z = pos->z - 0x200000;
        hi.x = pos->x + 0x200000;
        hi.y = lo.y + 0x120000;
        hi.z = pos->z + 0x240000;
        func_8006C334(0, 6, &lo, &hi, 0, 9216, 0x8000, 8192);
        func_8006C334(0, 3, &lo, &hi, 0, 9216, 0x8000, 8192);
        v = *pos;
        func_800718A4(3, &v, 0, 1920, attached);
        v.y += 0x180000;
        func_800718A4(3, &v, 0, 1536, 0);
        b->r = D_800D2FE4.ambient->r;
        b->g = D_800D2FE4.ambient->g;
        b->b = D_800D2FE4.ambient->b;
        b->color = D_800D2FE4.ambient->color;
        b->extra = D_800D2FE4.ambient->extra;
        b->timer = 0;
        break;
    }
    case 12: {
        Vector v;

        func_8006C334(0, 6, pos, pos, 0, 8192, 4096, 4096);
        func_8006C334(0, 2, pos, pos, 0, 12288, 4096, 4096);
        lo.x = pos->x - 0x180000;
        lo.y = pos->y;
        lo.z = pos->z - 0x180000;
        hi.x = pos->x + 0x180000;
        hi.y = lo.y + 0xC0000;
        hi.z = pos->z + 0x180000;
        func_8006C334(0, 6, &lo, &hi, 0, 6144, 8192, 8192);
        func_8006C334(0, 3, &lo, &hi, 0, 6144, 8192, 8192);
        v = *pos;
        func_800718A4(3, &v, 0, 1024, attached);
        break;
    }
    case 13:
        lo.x = pos->x - 0x80000;
        lo.y = pos->y + 0xC0000;
        lo.z = pos->z - 0x80000;
        hi.x = pos->x + 0x80000;
        hi.y = pos->y + 0x1E0000;
        hi.z = pos->z + 0x80000;
        func_8006C334(0, 12, &lo, &hi, 0, 4096, 0x20000, 4096);
        break;
    case 14: {
        Vector v;

        v = *pos;
        if (off != 0) {
            v.y -= off->y;
        }
        func_800718A4(2, &v, 0, 6144, attached);
        break;
    }
    }
}
