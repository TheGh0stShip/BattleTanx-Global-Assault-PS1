typedef struct { int x; int y; int z; } Vector;
typedef struct { unsigned int flags; void *obj; char pad[40 - 8]; } Voice;
typedef struct { char pad[0x30]; unsigned short wreck_time; char pad2[0xD0 - 0x32]; } Vehicle;
typedef struct {
    int f0;
    int f4;
    int type;
    Vector pos;
    unsigned short heading;
    unsigned short voice;
    void *owner;
    unsigned char f20;
    unsigned char f21;
    char pad[2];
    int timer;
    int start_time;
} Wreck;
typedef struct {
    char pad0[8];
    Vector pos;
    char pad1[0x2C - 0x14];
    unsigned short heading;
    char pad2[0x9C - 0x2E];
    int type;
    char pad3[0x208 - 0xA0];
    void *owner;
    char pad4[0x2B8 - 0x20C];
    unsigned short voice;
    char pad5[0x2FC - 0x2BA];
    unsigned char f2FC;
} Tank;
extern Voice D_800C62B0[];
extern Vehicle D_800A4EF4[];
extern int D_800D2FE0;
extern unsigned char D_800AED56;
extern Wreck *func_800237D0(int, int);
extern void func_8001B094(int);
extern void func_80029BF0(Vector *, int, int, int, int);
extern void func_8006FDB0(int, Vector *, int, int);
extern void func_8006C334(void *, int, Vector *, Vector *, int, int, int, int);
extern void func_80070D5C(Vector *, Vector *, int, int);

int func_800374F0(Tank *t, unsigned char keep)
{
    Wreck *w;
    Vector lo;
    Vector hi;

    if (t->voice == 0xFFFF) {
        return -1;
    }
    w = func_800237D0(11, 44);
    if (w == 0) {
        if (t->voice != 0xFFFF) {
            func_8001B094(t->voice);
        }
        return -1;
    }
    w->type = t->type;
    w->pos = t->pos;
    w->heading = t->heading;
    w->f20 = 0;
    w->owner = t->owner;
    w->f21 = t->f2FC;
    w->start_time = D_800D2FE0;
    w->voice = t->voice;
    t->voice = 0xFFFF;
    D_800C62B0[w->voice].obj = w;
    D_800C62B0[w->voice].flags &= ~8;
    D_800C62B0[w->voice].flags |= 0x400000;
    w->timer = D_800A4EF4[w->type].wreck_time >> 2;
    if (w->type != 11) {
        if (D_800AED56 & 1) {
            func_80029BF0(&w->pos, 21, 400, 0, t->type);
        } else {
            func_80029BF0(&w->pos, 8, 600, 0, t->type);
        }
    }
    if (keep) {
        w->timer = 0;
    }
    func_8006FDB0(7, &t->pos, 0, 0);
    lo.x = t->pos.x - 0x40000;
    lo.y = t->pos.y + 0x40000;
    lo.z = t->pos.z - 0x40000;
    hi.x = t->pos.x + 0x40000;
    hi.y = t->pos.y + 0x60000;
    hi.z = t->pos.z + 0x40000;
    func_8006C334(0, 3, &lo, &hi, 0, 12288, 1024, 0x60000);
    lo.x = t->pos.x - 0x100000;
    lo.y = t->pos.y + 0x40000;
    lo.z = t->pos.z - 0x100000;
    hi.x = t->pos.x + 0x100000;
    hi.y = t->pos.y + 0x60000;
    hi.z = t->pos.z + 0x100000;
    func_80070D5C(&lo, &hi, 2048, 0x40000);
    return 0;
}
