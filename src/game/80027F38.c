typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    char pad0[8];
    Vector pos;
    unsigned short angle;
    char pad16[2];
    int kind;
    int state;
    char pad20[4];
    int start;
    int param;
    unsigned short cell;
} Effect;

extern short D_800A44C8[];
extern int D_800D2FE0;
extern Effect *func_800237D0(int, int);
extern unsigned int func_80086C84(void);
extern unsigned short func_800162F0(Effect *, int, int, int, int, int, int, int, int, int, int, int);

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

static inline short to_cell(int value) {
    return fixed_to_int(value) >> 2;
}

void func_80027F38(Vector *pos, int kind, int param) {
    Effect *e = func_800237D0(36, 48);

    if (e != 0) {
        e->state = 0;
        e->kind = kind;
        e->pos = *pos;
        e->param = param;
        e->start = D_800D2FE0;
        e->angle = func_80086C84() % 0xFFFF;
        e->cell = func_800162F0(e, to_cell(pos->x), to_cell(pos->z), to_cell(pos->y),
                                (short)-D_800A44C8[kind], D_800A44C8[kind],
                                (short)-D_800A44C8[kind], D_800A44C8[kind], 0, 10, 0, 256);
    }
}
