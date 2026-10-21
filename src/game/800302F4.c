typedef struct { int x, y, z; } Vector;
typedef struct Segment Segment;
struct Segment {
    int pad[3];
    Segment *next;
    int offset;
    int pad2;
    int length;
    int pad3;
    unsigned short sound;
    short pad4;
    int pad5[4];
    int hp;
};
typedef struct {
    int pad[6];
    int min;
    int max;
    unsigned short angle;
    short pad2;
    int pad3;
    int pos;
    Segment *segments;
    short max_speed;
    short pad4;
    int pad5[2];
    int speed;
} Chain;
int func_8008AD60(int);
int func_8008ACC0(int);
void func_8002FF98(Segment *);
void func_800301FC(Segment *);
void func_8001B094(int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_800302F4(Chain *c, int pos) {
    Vector step;
    Segment *s;
    int offset;
    int at;
    int limit;
    int clamp;
    int d;

    offset = 0;
    d = pos - c->pos;
    limit = c->max_speed << 12;
    clamp = limit;
    c->speed = d;
    if (d > limit) {
        c->speed = limit;
    } else if (d < -clamp) {
        c->speed = -clamp;
    }
    step.x = fixed_mul(func_8008AD60(c->angle >> 4), c->speed);
    step.z = fixed_mul(func_8008ACC0(c->angle >> 4), c->speed);
    step.y = 0;
    c->pos = pos;
    for (s = c->segments; s != 0; s = s->next) {
        at = pos + offset;
        s->offset = at;
        if (s->hp > 0) {
            if (c->min < at + s->length && at < c->max) {
                if (s->sound == 0xFFFF) {
                    func_8002FF98(s);
                } else {
                    func_800301FC(s);
                }
            } else if (s->sound != 0xFFFF) {
                func_8001B094(s->sound);
                s->sound = 0xFFFF;
            }
        }
        offset += s->length;
    }
}
