typedef struct Segment Segment;
struct Segment {
    int pad[2];
    void *chain;
    Segment *next;
    int offset;
    int a2;
    int length;
    int s56;
    unsigned short sound;
    unsigned short kind;
    int s60;
    int s64;
    int s72;
    int s68;
    int hp_max;
    int hp;
    int s76;
};
typedef struct { int pad[9]; int length; int base; Segment *segments; } Chain;
Segment *func_800237D0(int, int);

void func_800313C4(Chain *c, int kind, int a2, int length, int s56, int s60, int s64, int s68, int s72,
                   int s76) {
    Segment *s;
    Segment *p;
    int hp;

    s = func_800237D0(2, 64);
    if (s != 0) {
        s->sound = 0xFFFF;
        s->offset = c->base + c->length;
        c->length += length;
        s->kind = kind;
        s->s56 = s56;
        s->length = length;
        s->s60 = s60;
        s->s68 = s68;
        s->s64 = s64;
        s->s72 = s72;
        s->next = 0;
        s->chain = c;
        s->a2 = a2;
        s->s76 = s76;
        switch ((unsigned short)kind) {
        case 0:
        case 2:
        case 6:
            hp = 200000;
            s->hp_max = s->hp = hp;
            break;
        case 3:
            hp = 100;
            s->hp_max = s->hp = hp;
            break;
        case 1:
        case 4:
            hp = 20;
            s->hp_max = s->hp = hp;
            break;
        }
        if (c->segments == 0) {
            c->segments = s;
        } else {
            p = c->segments;
            while (p->next != 0) {
                p = p->next;
            }
            p->next = s;
        }
    }
}
