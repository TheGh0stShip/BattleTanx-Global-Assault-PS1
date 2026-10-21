typedef struct { int pad; short type; } Entity;
typedef struct { Entity *obj; int pad[8]; } Hit;
typedef void (*Handler)(Entity *, void *, int, int, int);
typedef struct { int pad; Handler handler; int pad2; } TypeInfo;
typedef struct { short pad[3]; unsigned short cell; } Obj;
extern short D_800C628C;
extern TypeInfo D_800D32F4[];
int func_80017AAC(int, int, Hit *, int, int);

static inline unsigned short query_cell(unsigned short cell, int mask, Hit *hits, int a, int b) {
    D_800C628C = 0;
    return func_80017AAC(cell, mask, hits, a, b);
}

void func_80031830(Obj *o) {
    Hit hits[8];
    int i;
    register int n asm("$19");
    unsigned short count;
    Entity *e;

    count = query_cell(o->cell, 0x10000, hits, 0, 0);
    n = count;
    if (count != 0) {
        i = 0;
        if (i < count) do {
            e = hits[i].obj;
            if (e != 0 && D_800D32F4[e->type].handler != 0 && e->type != -1) {
                D_800D32F4[e->type].handler(hits[i].obj, o, 0, 0, 0);
            }
        } while (++i < n);
    }
}
