typedef struct { int x, y, z; } Vector;
typedef struct { int pad[5]; short pad2; short x0; short x1; short pad3; short y0; short y1; short z0; short pad4; int pad5; } Cell;
typedef struct { int pad; short type; } Entity;
typedef struct { Entity *obj; int pad[8]; } Hit;
typedef struct { int pad[3]; unsigned short id; char rest[22]; } Msg;
typedef struct { int blocked; int pad[6]; } Result;
typedef void (*Handler)(Entity *, void *, int, Msg *, Result *);
typedef struct { int pad; Handler handler; int pad2; } TypeInfo;
typedef struct { short pad[3]; unsigned short cell; Vector pos; unsigned short id; } Wall;
extern Cell D_800C62B0[];
extern short D_800C628C;
extern TypeInfo D_800D32F4[];
extern Result D_800BE24C;
int func_8001AED4(int, int, int, int, int, int, int, int, int, int, int, int);
int func_80017AAC(int, int, Hit *, int, int);
void func_8008AC90(void *, int);

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

static inline short quarter(int v) {
    return (to_int(v) << 14) >> 16;
}

int func_80031928(Wall *wall, int height) {
    Wall *w = wall;
    Hit hits[8];
    Msg msg;
    Result res;
    Cell *cell;
    register int n asm("$16");
    int i;
    Entity *e;
    int h;
    register int count asm("$20");

    cell = &D_800C62B0[w->cell];
    h = func_8001AED4(0, quarter(w->pos.x), quarter(w->pos.z), quarter(w->pos.y), cell->x0, cell->x1, cell->y0,
                      (short)((unsigned short)cell->y0 + quarter(height)), cell->y1, cell->z0, w->id, 0);
    D_800C628C = 0;
    n = func_80017AAC(h & 0xFFFF, 0xF4D50F, hits, 0, 0) & 0xFFFF;
    count = n;
    do {
        if (n != 0) {
            func_8008AC90(&msg, 36);
            msg.id = w->id;
            i = 0;
            if ((unsigned int)i < (unsigned int)n) do {
                if (hits[i].obj == (Entity *)w) {
                    continue;
                }
                if (hits[i].obj == 0) {
                    return 0;
                }
                res = D_800BE24C;
                if (D_800D32F4[hits[i].obj->type].handler != 0 && hits[i].obj->type != -1) {
                    do {
                        D_800D32F4[hits[i].obj->type].handler(hits[i].obj, w, 0, &msg, &res);
                    } while (0);
                }
                if (res.blocked == 1) {
                    return 0;
                }
            } while (++i < count);
        }
        return 1;
    } while (0);
}
