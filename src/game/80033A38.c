typedef struct { int x, y, z; } Vector;
typedef struct { int x, z; } Point2;
typedef struct Marker Marker;
struct Marker {
    int pad[3];
    int active;
    int pad2[2];
    int link;
    Marker *next;
    Vector pos;
    int time;
    short pad3;
    unsigned short flags;
};
typedef struct { int pad[2]; Vector pos; char pad2[164 - 20]; Marker *free_list; } Spawner;
extern int D_800D2FE0;
int func_8001EA3C(Point2 *);

void func_80033A38(Spawner *s) {
    Vector p;
    Point2 xz;
    Marker *m;

    p = s->pos;
    while (s->free_list != 0) {
        m = s->free_list;
        s->free_list = m->next;
        m->pos = p;
        xz.x = m->pos.x;
        xz.z = m->pos.z;
        m->pos.y = func_8001EA3C(&xz) + 0x32000;
        m->flags = 0xFFFF;
        m->active = 1;
        m->link = 0;
        m->next = 0;
        m->time = D_800D2FE0;
        p.x += 15;
    }
}
