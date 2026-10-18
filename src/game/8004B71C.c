typedef struct {
    int x;
    int y;
    int z;
    int pad;
} Vector4;
typedef struct {
    int a;
    int b;
} Segment;
typedef struct {
    char pad0[0xC];
    unsigned short left;
    unsigned short right;
} PathNode;
typedef struct {
    char pad0[0xA];
    unsigned short next;
    char padC[0x16 - 0xC];
    unsigned short node;
    int side;
    char pad1C[0x30 - 0x1C];
    Vector4 position;
} Route;
typedef struct {
    char pad0[0xF8];
    Route route;
} Tank;
extern PathNode *func_8004A794(unsigned short);
extern void func_8004C058(Tank *, int);
extern unsigned short func_8004C0F8(Tank *, int);
extern unsigned int func_80086C84(void);
extern void func_8004A8B0(PathNode *, Segment *);
extern void func_80049468(Segment *, int, Vector4 *, Vector4 *);
extern int func_800495D8(Vector4 *, Vector4 *);

void func_8004B71C(Tank *tank) {
    Route *route = &tank->route;
    int id = route->node;
    PathNode *node = func_8004A794(id);
    unsigned short link;
    unsigned short next;
    unsigned int r;
    int choose_left;
    Vector4 a;
    Vector4 b;
    Segment segment;

    if (route->side != 1) {
        if (route->side == 0) {
            goto advance;
        }
        if (route->side != 2) {
            goto advance;
        }
        link = node->left;
    } else {
        link = node->right;
    }
    if (link == 0) {
        do {
            func_8004C058(tank, id);
        } while (0);
    }
advance:
    next = func_8004C0F8(tank, 0);
    route->next = next;
    route->node = next;
    if (next == 0) {
        route->side = 0;
        return;
    }
    node = func_8004A794(next);
    if (node->right != 0) {
        route->side = 1;
    } else if (node->left != 0) {
        route->side = 2;
    } else {
        r = func_80086C84();
        if ((r & 3) == 3) {
            choose_left = (r & 4) == 0;
        } else {
            func_8004A8B0(node, &segment);
            func_80049468(&segment, 0, &a, &b);
            choose_left = func_800495D8(&route->position, &a) < func_800495D8(&route->position, &b);
        }
        if (choose_left) {
            route->side = 2;
        } else {
            route->side = 1;
        }
    }
}
