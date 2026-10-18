typedef struct { int x, y, z; } Vector;
typedef struct { int pad[2]; unsigned int level; } Info;
typedef struct { Info *info; } Model;
typedef struct { int pad[3]; int state; Model *model; int pad2[3]; Vector pos; } Beacon;
extern int D_800D2FE0;
void func_8006A1BC(Model *, Vector *, int, unsigned short, int);
void func_80061CC0(int, int, int, int, int);

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

static inline void mark_cell(void *p) {
    Beacon *b = p;

    if (b->state == 1) {
        func_80061CC0((short)to_int(b->pos.x), (short)to_int(b->pos.z), 0, 10, 0);
    }
}

void func_80033920(Beacon *b) {
    if (b->state != 2) {
        if (b->model->info->level >= 6) {
            func_8006A1BC(b->model, &b->pos, 0, 0x8000, 0);
        } else {
            func_8006A1BC(b->model, &b->pos, 0, (D_800D2FE0 * 200) & 0xFFF8, 0);
        }
    }
    mark_cell(b);
}
