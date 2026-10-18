typedef struct Pending Pending;
struct Pending {
    unsigned char kind;
    char pad1;
    unsigned short prev;
    int key;
    Pending *next;
};
typedef struct {
    unsigned char kind;
    char pad1;
    unsigned short prev;
    char pad4[8];
    unsigned short left;
    unsigned short right;
    char pad10[0x1A - 0x10];
    unsigned short link;
} PathNode;
typedef struct {
    Pending *pending;
    unsigned short head;
    unsigned short count;
    char pad8[2];
    unsigned short next;
    char padC[0x14 - 0xC];
    unsigned short last;
    unsigned short node;
    int side;
} Route;
typedef struct {
    char pad0[0xF8];
    Route route;
    char pad114[0x14A - 0x114];
    unsigned short route_seen;
} Tank;
typedef struct {
    char pad0[0xE010];
    unsigned short max_route;
} MoveSystem;
extern MoveSystem *D_800A5B24;
extern PathNode *func_8004A794(unsigned short);
extern int func_8004A3D4(unsigned short *);
extern int func_8004A160(unsigned short *, int);

static inline void route_trim(Route *route) {
    unsigned short limit = D_800A5B24->max_route;
    unsigned short i;
    PathNode *node;

    if (route->count > limit) {
        node = func_8004A794(route->head);
        for (i = 1; i < limit; i++) {
            node = func_8004A794(node->link);
        }
        route->count -= func_8004A160(&node->link, 0);
    }
}

void func_8004BB98(Tank *tank) {
    Route *route = &tank->route;
    Pending *pending = route->pending;
    unsigned short next = 0;
    unsigned short prev_id;
    unsigned short tmp;
    short id;
    PathNode *cur;
    PathNode *node;
    PathNode *branch;

    tank->route_seen = 0;
    if (pending == 0) {
        do {
            tmp = route->node;
        } while (0);
        id = tmp;
        if ((id & 0xFFFF) == 0) {
            prev_id = next;
            cur = 0;
        } else {
            prev_id = func_8004A794(id)->prev;
            cur = func_8004A794(prev_id);
            next = cur->prev;
            route->count -= func_8004A3D4(&cur->link);
        }
    } else {
        prev_id = pending->prev;
        cur = func_8004A794(prev_id);
        next = cur->prev;
        pending->next = 0;
    }
    route->next = 0;
    route->last = 0;
    route->node = 0;
    route->side = 0;
    while (next != 0) {
        node = func_8004A794(next);
        if (node->kind == 2) {
            tmp = next;
            next = node->prev;
            branch = node;
            node = func_8004A794(next);
            cur->prev = next;
            node->link = prev_id;
            if (branch->right == prev_id) {
                branch->right = 0;
            } else {
                branch->left = 0;
            }
            route->count -= func_8004A160(&tmp, 0);
        }
        prev_id = next;
        cur = node;
        next = cur->prev;
    }
    route_trim(route);
}
