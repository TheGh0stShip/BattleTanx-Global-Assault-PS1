typedef struct { int x, y, z; } Vector;
typedef struct { char pad[32]; Vector pos; int pad2[4]; int value; int pad3; unsigned char lit; } Target;
typedef struct {
    int pad[2];
    Target *target;
    int model;
    int value;
    int pad2;
    Vector min;
    Vector max;
    unsigned short sound;
    unsigned short angle;
    unsigned char pad3;
    unsigned char kind;
} Gate;
void func_8001B094(int);
void func_80035948(int, Vector *, int, int, int, int, int, int);
int func_8008B830(int);
void func_8006FDB0(int, Vector *, Vector *, int);
void func_80053790(int, int, int);
void func_800235E0(Vector *, int, int, int, int);
int func_80023B8C(Vector *, int, int, int, int, int);
unsigned int func_80086C84(void);
void func_80022CAC(Gate *);

void func_80035238(Gate *g) {
    Vector center;
    Vector size;

    if (g->value != 0) {
        g->target->value = g->value;
    } else {
        g->target->lit = 0;
        g->target->value = 0;
    }
    func_8001B094(g->sound);
    func_80035948(g->model, &g->target->pos, g->angle, 0, 0, 0, 0, 0);
    center.x = (g->min.x + g->max.x) / 2;
    center.y = (g->min.y + g->max.y) / 2;
    center.z = (g->min.z + g->max.z) / 2;
    size.x = func_8008B830(g->max.x - g->min.x) / 2;
    size.y = func_8008B830(g->max.y - g->min.y) / 2;
    size.z = func_8008B830(g->max.z - g->min.z) / 2;
    if (g->kind != 3) {
        func_8006FDB0(g->kind, &center, &size, 0);
    }
    if (g->kind != 0) {
        switch (g->kind) {
        case 1:
            func_80053790(10, center.x, center.z);
            func_800235E0(&center, 100, 10, 127, 0xE49D0A);
            break;
        case 2:
            func_80053790(12, center.x, center.z);
            func_800235E0(&center, 200, 20, 127, 0xE49D0A);
            break;
        case 3:
            func_8006FDB0(3, &center, 0, func_80023B8C(&center, 127, 200, 5, 0, 2500));
            func_80053790(11, center.x, center.z);
            break;
        }
    } else if (((func_80086C84() >> 16) & 1) == 0) {
        func_80053790(5, center.x, center.z);
    } else {
        func_80053790(51, center.x, center.z);
    }
    func_80022CAC(g);
}
