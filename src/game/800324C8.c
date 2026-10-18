typedef struct { int x, y, z; } Vector;
typedef struct { int x, z; } Point2;
typedef struct { int pad[5]; short height; short pad2; int pad3[4]; } Cell;
typedef struct { int pad; unsigned short count; } Counter;
typedef struct { char pad[12]; Counter *counter; char rest[0x114 - 16]; } Waypoint;
typedef struct Marker Marker;
typedef struct { int pad[2]; Marker *marker; int pad2[3]; unsigned char waypoint; } Base;
struct Marker {
    int pad[3];
    int active;
    int resource;
    Base *base;
    Base *home;
    Marker *link;
    Vector pos;
    int pad2;
    unsigned char id;
    unsigned char pad3;
    unsigned short cell;
};
extern Cell D_800C62B0[];
extern Waypoint D_800E3E68[];
void func_80033CEC(Base *, Vector *);
int func_8001EA3C(Point2 *);
void func_80015F64(int, int, int);
void func_800531D4(Waypoint *, int);

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

static inline Cell *cell_at(int i) {
    return &D_800C62B0[i];
}

static inline Waypoint *waypoint_at(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_800324C8(Marker *m, Base *b) {
    Point2 p;
    int h;
    int cell;
    short x;
    short z;

    if (m->active == 1) {
        func_80033CEC(b, &m->pos);
        p.x = m->pos.x;
        p.z = m->pos.z;
        m->pos.y = func_8001EA3C(&p) + 0x64000;
        x = (unsigned int)to_int(m->pos.x) >> 2;
        z = (unsigned int)to_int(m->pos.z) >> 2;
        h = (to_int(m->pos.y) << 14) >> 16;
        cell = m->cell;
        func_80015F64(cell, x, z);
        cell_at(cell)->height = h;
    } else {
        func_80033CEC(b, &m->pos);
        p.x = m->pos.x;
        p.z = m->pos.z;
        m->pos.y = func_8001EA3C(&p) + 0x64000;
        m->cell = 0xFFFF;
    }
    m->id = b->waypoint;
    m->active = 0;
    m->home = b;
    m->base = b;
    m->link = b->marker;
    b->marker = m;
    __asm__ volatile("");
    waypoint_at(b->waypoint)->counter->count++;
    func_800531D4(waypoint_at(b->waypoint), 4);
}
