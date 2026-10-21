typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    unsigned char kind;
    char pad1;
    unsigned short next;
    union {
        Vector point;
        int length;
    } u;
} PathNode;
typedef struct {
    char pad0[0x11C];
    Vector goal;
} Tank;
extern PathNode *func_8004A794(unsigned short);
extern int func_800495D8(Vector *, Vector *);

static inline Vector *path_point(Tank *tank, PathNode *node) {
    for (;;) {
        if (node == 0) {
            return &tank->goal;
        }
        if (node->kind == 3) {
            return &node->u.point;
        }
        node = func_8004A794(node->next);
    }
}

int func_8004BA6C(Tank *tank, PathNode *start) {
    Vector *from = path_point(tank, start);
    PathNode *node = func_8004A794(start->next);
    int total = 0;

    for (;;) {
        if (node == 0) {
            total += func_800495D8(&tank->goal, from);
            break;
        }
        if (node->kind == 3) {
            total += func_800495D8(&node->u.point, from);
            from = &node->u.point;
            node = func_8004A794(node->next);
        } else {
            total += func_800495D8(path_point(tank, node), from);
            total += node->u.length;
            break;
        }
    }
    return total;
}
