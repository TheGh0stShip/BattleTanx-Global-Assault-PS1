typedef struct {
    short id;
} Ref;

typedef struct {
    int pad0;
    int pad4;
    Ref *a;
    Ref *b;
    short id_a;
    short id_b;
    unsigned char done;
    char pad15;
    short v16;
    short v18;
    short v1A;
    short v1C;
    short v1E;
    short v20;
    short v22;
    short v24;
    short v26;
} Blast;

typedef struct {
    short pad;
    short pad2;
    short type;
} Target;

typedef struct {
    Target *obj;
    int pad[8];
} Hit;

typedef struct {
    int data[7];
} Damage;

typedef struct {
    int pad[4];
    int kind;
    int zero;
    int pad2[4];
} HitInfo;

typedef struct {
    int pad;
    void (*fn)(Target *t, Blast *b, int c, HitInfo *info, Damage *d);
    int pad2;
} Handler;

extern int D_800DE30C;
extern short D_800C628C;
extern Damage D_800C05CC;
extern Handler D_800D32F4[];
extern unsigned int func_80086C84(void);
extern int func_8001AED4(Blast *b, int a, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l);
extern int func_80017AAC(int h, int mask, Hit *hits, int a, int b);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_800710BC(Blast *b, int *done) {
    Hit hits[8];
    HitInfo info;
    Damage dmg;
    int h;
    register int n asm("$20");
    register int r asm("$2");
    register int i asm("$17");
    register Hit *hit asm("$16");
    Handler *handler;
    int type;
    Blast *self = b;

    if (b->done || (b->a != 0 && b->a->id != b->id_a && b->b != 0 && b->b->id != b->id_b)) {
        *done = 1;
    }
    if (func_80086C84() % fixed_mul(10, D_800DE30C) == 0) {
        h = func_8001AED4(b, self->v16, self->v1A, self->v18, self->v1C, self->v22, self->v20, self->v26, self->v1E,
                          self->v24, 0, 1);
        if ((h & 0xFFFF) != 0xFFFF) {
            register int mask asm("$5") = 0x41108;

            D_800C628C = 0;
            __asm__("addiu $16,$sp,48" : "=r"(hit) : "r"(mask));
            r = func_80017AAC(h & 0xFFFF, mask, hit, 0, 0) & 0xFFFF;
            n = r;
            if (r != 0) {
                i = 0;
                if (i < r) do {
                    dmg = D_800C05CC;
                    info.kind = 8;
                    info.zero = 0;
                    type = hit->obj->type;
                    handler = &D_800D32F4[type];
                    if (handler->fn != 0 && type != -1) {
                        handler->fn(hit->obj, b, 0, &info, &dmg);
                    }
                    hit++;
                } while (++i < n);
            }
        }
    }
}
