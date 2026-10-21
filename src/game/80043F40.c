typedef struct Pos2 {
    int x;
    int z;
} Pos2;
typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;
typedef struct Cell {
    int flags;
    void *owner;
    unsigned short next[4];
    short x;
    short z;
    short y;
    short min_x;
    short max_x;
    short min_z;
    short max_z;
    short y_low;
    short y_high;
    short radius;
    unsigned short angle;
    char pad26[0x28 - 0x26];
} Cell;
typedef struct Node {
    short id;
    short next;
    short kind;
    short pad06;
    void *object;
} Node;
typedef struct Hit {
    Node *owner;
    unsigned short id;
    char pad06[2];
    Vec3 pos;
    char pad14[0x24 - 0x14];
} Hit;
typedef struct Body Body;
typedef struct Driver {
    short id;
    char pad02[6];
    Body *body;
} Driver;
typedef struct Mover {
    char pad00[0x30];
    int scale;
    char pad34[0x5D - 0x34];
    unsigned char stuck;
    char pad5E[0x60 - 0x5E];
    void *dir;
} Mover;
typedef struct Impact {
    Vec3 pos;
    unsigned short heading;
    short pad;
    int source;
    void *owner;
    int status;
    unsigned short part;
    short pad2;
    Mover *mover;
} Impact;
typedef struct Reply {
    int kind;
    char pad[0x1C - 4];
} Reply;
typedef struct NodeClass {
    void (*update)();
    void (*query)(Node *, Driver *, int, Impact *, Reply *);
    void (*draw)();
} NodeClass;
typedef struct Kind {
    char pad00[0xAA];
    unsigned short width;
    char padAC[0xD0 - 0xAC];
} Kind;
struct Body {
    Driver *driver;
    char pad04[4];
    Vec3 pos;
    Vec3 prev;
    char pad20[0x2C - 0x20];
    unsigned short angle;
    char pad2E[0x34 - 0x2E];
    Mover mover;
    char pad98[0x9C - 0x98];
    int kind;
    char padA0[0x208 - 0xA0];
    void *owner;
    char pad20C[0x218 - 0x20C];
    int status;
    char pad21C[0x28C - 0x21C];
    int boost;
    char pad290[0x2B8 - 0x290];
    unsigned short grid_id;
};

extern Kind D_800A4EF4[];
extern Cell D_800C62B0[];
extern short D_800C628C;
extern NodeClass D_800D32F4[];

unsigned short func_8001CAC8(Mover *, int, unsigned short, Pos2 *, Pos2 *, unsigned short, Driver *, short *);
void func_8001EBA0(Body *);
unsigned short func_80019D80(Vec3 *, Vec3 *, int, int, Driver *, Hit *);
void func_80015F64(unsigned short, short, short);
void func_8001BEA8(Mover *, int, unsigned short, unsigned short);
void func_8001E0A4(Mover *, unsigned short, int *);
unsigned short func_80017AAC(int, int, Hit *, int, int);
void func_80043D30(Body *, Reply *);

static inline int to_int(int v) {
    return v >= 0 ? v >> 12 : -(-v >> 12);
}
static inline void place(unsigned short id, unsigned short angle, short x, short z) {
    if (id != 0xFFFF) {
        int off = id * sizeof(Cell);

        ((Cell *)((char *)D_800C62B0 + off))->angle = angle;
        func_80015F64(id, x, z);
    }
}
static inline short height(Cell *c, short off) {
    return off + c->y;
}

static inline void get_xz(Pos2 *d, Vec3 *v) {
    int x = v->x;
    int z = v->z;

    d->x = x;
    d->z = z;
}
static inline void set_vec(Vec3 *v, int x, int y, int z) {
    v->x = x;
    v->y = y;
    v->z = z;
}
static inline unsigned short probe(unsigned short id, Hit *hits) {
    D_800C628C = 1;
    return func_80017AAC(id, 0x203A310, hits, 0, 0);
}
static inline unsigned short sweep(Pos2 *from, Pos2 *to, Vec3 *cur, int mask, int width, Body *t, Hit *hits) {
    Vec3 a;
    Vec3 b;
    unsigned short n;
    Driver *d;

    get_xz(from, cur);
    D_800C628C = 0;
    d = t->driver;
    a.x = from->x;
    a.y = 0;
    a.z = from->z;
    b.x = to->x;
    b.y = 0;
    b.z = to->z;
    n = func_80019D80(&a, &b, mask, width, d, hits);
    from->x = a.x;
    from->z = a.z;
    to->x = b.x;
    to->z = b.z;
    return n;
}

unsigned short func_80043F40(Body *body, int arg1, int angle, int heading) {
    unsigned short result = 0;
    Mover *m = &body->mover;
    Vec3 *p;
    Pos2 pos;
    Pos2 prev;
    Pos2 start;
    Hit near[8];
    Hit hits[8];
    short flag;
    register int dir asm("$21");
    unsigned short moved;
    unsigned short i;
    unsigned short count;

    start.x = body->pos.x;
    start.z = body->pos.z;
    p = &body->pos;
    get_xz(&pos, p);
    {
        int px = body->prev.x;
        int pz = body->prev.z;

        prev.x = px;
        prev.z = pz;
    }
    flag = 0;
    moved = func_8001CAC8(m, arg1, angle, &pos, &prev, body->grid_id, body->driver, &flag);
    dir = heading;
    if (moved != 0) {
        if (m->dir == 0) {
            body->angle = heading;
        }
        if (!(body->status & 1)) {
            return 1;
        }
        func_8001EBA0(body);
    } else {
        set_vec(p, pos.x, body->pos.y, pos.z);
        if (m->dir == 0) {
            body->angle = angle;
        }
        m->stuck = 0;
    }
    if (!(body->status & 1)) {
        return 1;
    }
    i = body->mover.dir != 0;
    if (i == 0 && (body->pos.x != prev.x || body->pos.z != prev.z)) {
        int width = D_800A4EF4[body->kind].width >> 1;
        Hit *list = hits;

        count = sweep(&pos, &prev, &body->pos, 0x804407, width, body, list);
        if (count != 0) {
            for (i = 0; i < count; i++) {
                Cell *c = &D_800C62B0[hits[i].id];

                if (height(c, c->y_low) < 101) {
                    if (body->status & 2) {
                        if ((body->kind != 3 || body->boost == 0) && height(c, c->y_high) < 37) {
                            continue;
                        }
                    }
                    body->angle = dir;
                    body->pos.x = body->prev.x;
                    body->pos.z = body->prev.z;
                    break;
                }
            }
        }
    }
    place(body->grid_id, body->angle, to_int(body->pos.x) >> 2, (to_int(body->pos.z) << 14) >> 16);
    result |= flag;
    if (body->driver->body == 0) {
        return 1;
    }
    {
        Mover *mv = &body->mover;

        func_8001BEA8(mv, arg1, dir, body->angle);
        func_8001E0A4(mv, body->grid_id, &body->pos.y);
        mv->scale = 4096;
    }
    count = probe(body->grid_id, near);
    for (i = 0; i < count; i++) {
        int off = i * sizeof(Hit);
        Hit *h = (Hit *)((char *)near + off);

        if (h->owner != 0) {
            Reply reply;
            Impact imp;
            NodeClass *nc;

            reply.kind = 2;
            imp.heading = body->angle;
            imp.pos = h->pos;
            imp.status = body->status & 2;
            imp.owner = body->owner;
            imp.source = 0;
            imp.mover = 0;
            nc = &D_800D32F4[h->owner->kind];
            if (nc->query != 0 && h->owner->kind != -1) {
                nc->query(h->owner, body->driver, 0, &imp, &reply);
            }
            func_80043D30(body, &reply);
            if (!(body->status & 1)) {
                return 1;
            }
        }
    }
    return result;
}
