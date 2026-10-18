typedef struct { int x, y, z; } Vector;
typedef struct Segment Segment;
struct Segment { int pad[3]; Segment *next; int offset; int pad2; int length; int pad3[2]; int model; int pad4[3]; int hp; };
typedef struct { int x; int z; int pad; int y; int pad2[2]; unsigned short angle; } Frame;
typedef struct { int pad[2]; Frame frame; short pad2; int pad3; Segment *segments; } Chain;
int func_8008AD60(int);
int func_8008ACC0(int);
void func_8006A1BC(int, Vector *, int, int, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int half_length(Segment *s) {
    return s->length / 2;
}

void func_80031198(Chain *c) {
    Frame *f = &c->frame;
    Segment *s;
    int half;
    int a;
    Vector v;

    for (s = c->segments; s != 0; s = s->next) {
        if (s->hp > 0) {
            a = f->angle >> 4;
            half = half_length(s);
            v.x = f->x + fixed_mul(func_8008AD60(a), s->offset + half);
            a = f->angle >> 4;
            half = half_length(s);
            v.z = f->z + fixed_mul(func_8008ACC0(a), s->offset + half);
            v.y = f->y;
            func_8006A1BC(s->model, &v, 0, c->frame.angle, 0);
        }
    }
}
