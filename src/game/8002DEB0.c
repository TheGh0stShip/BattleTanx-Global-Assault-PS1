typedef struct { int x, y, z; } Vector;
typedef struct {
    unsigned char kind;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    unsigned char r, g, b;
    unsigned char flags;
    Vector pos;
    short w0;
    short frame;
    short w;
    short h;
    int tex;
} Sprite;
typedef struct { int pad; char *next; int pad2[2]; int remaining; int count; int texbase; } Pool;
typedef struct { int pad[2]; Vector pos; } Obj;
extern Pool D_800AD9EC;
unsigned int func_80086C84(void);

static inline Sprite *alloc_sprite(void) {
    Pool *pool = &D_800AD9EC;
    Sprite *s = 0;
    register int rem asm("$2");
    register int left asm("$3");

    rem = pool->remaining;
    left = rem - 32;
    if (left > 0) {
        s = (Sprite *)pool->next;
        pool->remaining = left;
        {
            register int c asm("$2") = pool->count + 1;
            pool->next = (char *)s + 32;
            pool->count = c;
        }
        s->kind = 8;
        s->b2 = 0;
    }
    return s;
}

static inline int round_int(int v) {
    if (v >= 0) {
        if (v + 2048 >= 0) {
            return (v + 2048) >> 12;
        }
        return -(-(v + 2048) >> 12);
    }
    if (v - 2048 >= 0) {
        return (v - 2048) >> 12;
    }
    return -(-(v - 2048) >> 12);
}

void func_8002DEB0(Obj *o) {
    Sprite *s;
    Vector v;
    int tex;

    s = alloc_sprite();
    if (s != 0) {
        v.x = round_int(o->pos.x);
        v.y = round_int(o->pos.y);
        v.z = round_int(o->pos.z);
        s->pos = v;
        __asm__ volatile("");
        s->r = 128;
        s->g = 128;
        s->b = 128;
        s->b3 = 9;
        s->flags = 44;
        s->b1 = 0;
        tex = D_800AD9EC.texbase;
        s->w0 = 0;
        s->frame = 0;
        s->b1 = 0;
        s->tex = tex + 228;
        s->frame = func_80086C84() >> 16;
        s->w = 96;
        s->h = 96;
        s->w0 = 32;
        s->flags |= 2;
    }
}
