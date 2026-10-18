typedef struct { int x, y, z; } Vector;
typedef struct { int pad[8]; short value; short pad2; int pad3; } Cell;
typedef struct { int pad[2]; int x; int z; int pad2; int y; int pad3[2]; unsigned short angle; } Body;
typedef struct {
    int pad[2];
    Body *body;
    int pad2;
    int offset;
    int pad3;
    int length;
    int last_speed;
    unsigned short cell;
    short state;
    int timer;
    int model;
    int reset;
    int pad4;
    int hp;
    int pad5[1];
    int speed;
} Seg;
extern Cell D_800C62B0[];
int func_8008AD60(int);
int func_8008ACC0(int);
void func_80035948(int, Vector *, int, int, int, int, int, int);
void func_8006FDB0(int, Vector *, int, int);

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

static inline Cell *cell_at(int i) {
    return &D_800C62B0[i];
}


static inline int half_length(Seg *s) {
    return s->length / 2;
}

void func_800305DC(Seg *s) {
    Body *body = s->body;
    Vector v;
    int half;
    int a;
    int value;

    if (s->cell != 0xFFFF) {
        value = (unsigned int)to_int(s->speed) >> 2;
        cell_at(s->cell)->value = value;
    }
    s->last_speed = s->speed;
    a = body->angle >> 4;
    half = half_length(s);
    v.x = body->x + fixed_mul(func_8008AD60(a), s->offset + half);
    a = body->angle >> 4;
    half = half_length(s);
    v.z = body->z + fixed_mul(func_8008ACC0(a), s->offset + half);
    v.y = body->y;
    if (s->model != 0) {
        func_80035948(s->model, &v, body->angle, 0, 0, 0, 0, 0);
    }
    func_8006FDB0(4, &v, 0, 0);
    s->state = 5;
    s->hp = 200000;
    s->timer = s->reset;
}
