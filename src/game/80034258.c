typedef struct {
    short pad[3];
    unsigned char flag;
    char pad1;
    short handle;
    short pad2;
    int x;
    int y;
    int z;
    unsigned short id;
    short pad3;
    int link;
} Blocker;
extern unsigned int D_800D2FE8;
Blocker *func_800237D0(int, int);
short func_800162F0(Blocker *, int, int, int, int, int, int, int, int, int, int, int);

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

void func_80034258(int x, int y, int z, short a, short b, short c, short d, short e, short f, unsigned short id,
                   int flag) {
    Blocker *o;

    switch (D_800D2FE8) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 8:
    case 11:
    case 12:
    case 13:
        break;
    default:
        o = func_800237D0(20, 32);
        if (o != 0) {
            o->handle = func_800162F0(o, (to_int(x) << 14) >> 16, (to_int(z) << 14) >> 16, (to_int(y) << 14) >> 16, a,
                                      b, e, f, c, d, id, 0x10000);
            o->flag = flag;
            o->id = id;
            o->x = x;
            o->y = y;
            o->z = z;
            o->link = 0;
        }
        break;
    }
}
