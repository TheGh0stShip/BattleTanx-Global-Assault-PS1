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
    char pad0[0x1C];
    int first;
} Header;

typedef struct {
    Header *header;
    char pad4[0x10];
    Shape *shapes;
} Model;

extern unsigned short func_800162F0(int, int, int, int, int, int, int, int, int, int, int, int);

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

static inline short to_cell(int value) {
    return fixed_to_int(value) >> 2;
}

unsigned short func_80024D80(Model *model, Vector *pos, unsigned short flags, unsigned short index, int mask,
                            int list) {
    Shape *shape;
    int x;
    int z;
    int y0;
    int y1;

    if (index == 0xFFFF) {
        return 0;
    }
    shape = &model->shapes[index + model->header->first];
    x = to_cell(pos->x);
    z = to_cell(pos->z);
    y0 = (short)(shape->box->y0 + to_cell(pos->y));
    y1 = (short)(shape->box->y1 + to_cell(pos->y));
    return func_800162F0(list, x, z, 0, shape->box->x0, shape->box->x1, shape->box->z0, shape->box->z1,
                         y0, y1, flags, mask);
}
