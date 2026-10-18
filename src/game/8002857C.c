typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    char pad0[4];
    short x0;
    short y0;
    short z0;
    short pad0A;
    short x1;
    short y1;
    short z1;
} Box;

typedef struct {
    char pad0[8];
    Box *box;
} Shape;

typedef struct {
    char pad0[0x18];
    int shape;
    char pad1C[0x54 - 0x1C];
} Kind;

typedef struct {
    void *node;
    char pad04[0x24 - 4];
} ProbeHit;

extern Kind D_800A44D4[];
extern Shape *D_800D2E14[];
extern short D_800C628C;
extern unsigned short func_8001AED4(int, int, int, int, int, int, int, int, int, int, int, int);
unsigned short func_80017AAC(unsigned short, int, ProbeHit *, int, int);

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

static inline short to_cell(int value) {
    return fixed_to_int(value) >> 2;
}

static inline int probe_hits(unsigned short id, ProbeHit *hits) {
    D_800C628C = 0;
    return func_80017AAC(id, 0xE45D0F, hits, 0, 1);
}

int func_8002857C(unsigned char kind, Vector *pos, unsigned short flags) {
    Shape *shape = D_800D2E14[D_800A44D4[kind].shape];
    ProbeHit hits[8];
    int x = to_cell(pos->x);
    int z = to_cell(pos->z);
    int y0 = (short)(shape->box->y0 + to_cell(pos->y));
    int y1 = (short)(shape->box->y1 + to_cell(pos->y));
    unsigned short id;

    id = func_8001AED4(0, x, z, 0, shape->box->x0, shape->box->x1, shape->box->z0, shape->box->z1, y0, y1, flags, 0);
    return probe_hits(id, hits) == 0;
}
