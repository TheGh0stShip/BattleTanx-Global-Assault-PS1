typedef struct Spot {
    int x;
    int z;
    short angle;
    unsigned char used;
    char pad;
} Spot;

typedef struct Bounds {
    char pad00[4];
    unsigned short x0;
    unsigned short z0;
    char pad08[4];
    unsigned short x1;
    unsigned short z1;
} Bounds;

typedef struct Shape {
    char pad00[8];
    Bounds *bounds;
} Shape;

typedef struct Seg {
    unsigned char pad0;
    unsigned char kind;
    short length;
    unsigned short shape;
    unsigned short rail;
    unsigned short left;
    unsigned short right;
} Seg;

typedef struct Level {
    struct {
        char pad00[0x10];
        char *segs;
    } *data;
} Level;

typedef struct TrackDef {
    char pad0;
    unsigned char type;
    char pad02[2];
    int start_key;
    int end_key;
    unsigned short speed;
    unsigned short sound;
    int segs[6];
} TrackDef;

typedef struct Piece Piece;

typedef struct Track {
    char pad00[8];
    int x;
    int z;
    int length;
    int unk14;
    int lo;
    int hi;
    char pad20[0x20 - 0x20];
    unsigned short angle;
    char pad22[2];
    int pos;
    int base;
    Piece *pieces;
    unsigned short speed;
    unsigned char pace;
    char pad33;
    int unk34;
    unsigned char type;
    unsigned char state;
    unsigned short sound;
    int unk3C;
} Track;

struct Piece {
    char pad00[8];
    Track *track;
    Piece *next;
    int start;
    int width;
    int length;
    int depth;
    unsigned short flag;
    unsigned short kind;
    void *shape;
    void *rail;
    void *right;
    void *left;
    int rate;
    int limit;
    int offset;
};

void *func_800237D0(int, int);
void func_8008AA48(void *, int, int);
int func_80026340(Level *, int, Spot *, int);
void *func_80026300(Level *, int);
int func_8008AE30(int, int);
int func_8008AD60(int);
int func_8008ACC0(int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_80030DA4(TrackDef *def, Level *lvl) {
    Track *t = func_800237D0(1, 64);
    Spot start;
    Spot end;
    int i;
    int width;
    int dx, dz;
    int angle;

    if (t == 0) {
        return;
    }
    func_8008AA48(&start, 0, sizeof(start));
    func_8008AA48(&end, 0, sizeof(end));
    func_80026340(lvl, def->start_key, &start, 1);
    func_80026340(lvl, def->end_key, &end, 1);
    t->unk14 = 0;
    dx = (short)(end.x - start.x) << 14;
    dz = (short)(end.z - start.z) << 14;
    angle = func_8008AE30(dx, dz) & 0xFFF;
    t->angle = angle << 4;
    t->length = fixed_mul(func_8008AD60(angle), dx) + fixed_mul(func_8008ACC0(angle), dz);
    t->x = (short)start.x << 14;
    t->z = (short)start.z << 14;
    t->lo = -4096;
    t->hi = t->length + 4096;
    t->base = 0;
    t->sound = def->sound;
    t->type = def->type;
    t->state = 2;
    t->unk3C = 0;
    t->pos = 0;
    t->speed = def->speed;
    t->pieces = 0;
    t->unk34 = 0;
    for (i = 0; i < 6; i++) {
        Seg *seg;
        void *shape, *rail, *left, *right;
        Bounds *b;
        int length, depth, offset;
        unsigned short kind;
        Piece *p;

        if (def->segs[i] == -1) {
            continue;
        }
        seg = (Seg *)(lvl->data->segs + def->segs[i]);
        shape = func_80026300(lvl, seg->shape);
        right = func_80026300(lvl, seg->right);
        b = ((Shape *)shape)->bounds;
        width = (short)(b->x1 - b->x0) << 14;
        length = seg->length << 14;
        depth = (short)(b->z1 - b->z0) << 14;
        kind = seg->kind;
        rail = func_80026300(lvl, seg->rail);
        left = func_80026300(lvl, seg->left);
        if (seg->kind == 4) {
            Bounds *rb = ((Shape *)right)->bounds;
            offset = (short)(rb->z1 - rb->z0) << 14;
        } else {
            offset = 0;
        }
        p = func_800237D0(2, 64);
        if (p == 0) {
            continue;
        }
        p->flag = 0xFFFF;
        p->start = t->base + t->pos;
        t->pos += length;
        p->kind = kind;
        p->depth = depth;
        p->length = length;
        p->shape = shape;
        p->left = left;
        p->rail = rail;
        p->right = right;
        p->next = 0;
        p->track = t;
        p->width = width;
        p->offset = offset;
        switch (p->kind) {
        case 0:
        case 2:
        case 6:
            p->rate = p->limit = 200000;
            break;
        case 3:
            p->rate = p->limit = 100;
            break;
        case 1:
            p->rate = p->limit = 20;
            break;
        case 4:
            p->limit = 20;
            p->rate = 20;
            break;
        }
        if (t->pieces == 0) {
            t->pieces = p;
        } else {
            Piece *q = t->pieces;
            while (q->next != 0) {
                q = q->next;
            }
            q->next = p;
        }
    }
    t->pace = 100;
}
