typedef struct { int x, y, z; } Vector;
typedef struct { int x, z; } Point2;
typedef struct { void *obj; int pad[8]; } Hit;
typedef struct { char pad[20]; unsigned short min_x; unsigned short min_z; unsigned short max_x; unsigned short max_z; } Level;
typedef struct {
    int pad[2];
    int kind;
    int active;
    int resource;
    void *base;
    void *home;
    int link;
    Vector pos;
    int pad2;
    unsigned char id_a;
    unsigned char id_b;
    unsigned short flags;
} Marker;
extern Level *D_800D2FE4;
extern short D_800C628C;
extern int D_800D5AA0;
unsigned int func_80086C84(void);
int func_8001AED4(int, int, int, int, int, int, int, int, int, int, int, int);
int func_80017AAC(int, int, Hit *, int, int);
Marker *func_800237D0(int, int);
int func_8001EA3C(Point2 *);

void func_80032C18(void) {
    Hit hits[8];
    Vector pos;
    Point2 p;
    short x;
    short z;
    int found;
    int h;
    unsigned short hi;
    unsigned short lo;
    int res;
    Marker *m;

    found = 0;
    do {
        hi = D_800D2FE4->max_x;
        lo = D_800D2FE4->min_x;
        x = lo + func_80086C84() % ((short)hi - (short)lo);
        hi = D_800D2FE4->max_z;
        lo = D_800D2FE4->min_z;
        z = lo + func_80086C84() % ((short)hi - (short)lo);
        h = func_8001AED4(0, x, z, 0, -50, 50, -50, 50, 0, 50, 0, 0);
        D_800C628C = 0;
        if ((func_80017AAC(h & 0xFFFF, 0x104500F, hits, 0, 1) & 0xFFFF) == 0) {
            found = 1;
        }
    } while (!found);
    pos.x = x << 14;
    pos.z = z << 14;
    res = D_800D5AA0;
    pos.y = 0;
    m = func_800237D0(8, 52);
    if (m != 0) {
        m->pos = pos;
        p.x = m->pos.x;
        p.z = m->pos.z;
        m->pos.y = func_8001EA3C(&p) + 0x32000;
        m->flags = 0xFFFF;
        m->id_a = m->id_b = 127;
        m->active = 1;
        m->kind = 2;
        m->home = 0;
        m->base = 0;
        m->resource = res;
        m->link = 0;
    }
}
