typedef struct { int pad; short type; } Entity;
typedef struct { Entity *obj; int pad[8]; } Hit;
typedef void (*Handler)(Entity *, void *, int, int, int);
typedef struct { int pad; Handler handler; int pad2; } TypeInfo;
typedef struct { char pad[56]; unsigned short cell; } Obj;
extern short D_800C628C;
extern TypeInfo D_800D32F4[];
int func_80017AAC(int, int, Hit *, int, int);

void func_8002E97C(Obj *o) {
    Hit hits[8];
    int i;
    int n;
    Entity *e;

    int cell = o->cell;

    if (cell != 0xFFFF) {
        D_800C628C = 0;
        n = func_80017AAC(cell, 0x100000, hits, 2, 0) & 0xFFFF;
        for (i = 0; i < n; i++) {
            e = hits[i].obj;
            if (e != 0 && D_800D32F4[e->type].handler != 0 && e->type != -1) {
                D_800D32F4[e->type].handler(hits[i].obj, o, 0, 0, 0);
            }
        }
    }
}
