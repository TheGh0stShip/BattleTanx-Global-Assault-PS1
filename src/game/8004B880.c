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
    char pad1[0x18 - 1];
    unsigned char branch;
    char pad19;
    unsigned short link;
} PathNode;
typedef struct {
    Pending *pending;
    char pad4[2];
    unsigned short count;
    char pad8[2];
    unsigned short next;
    char padC[0x18 - 0xC];
    int side;
} Route;
typedef struct {
    char pad0[0xF8];
    Route route;
} Tank;
typedef struct {
    char pad0[0xE008];
    void *free_moves;
} MoveSystem;
extern MoveSystem *D_800A5B24;
extern PathNode *func_8004A794(unsigned short);
extern unsigned short func_8004B328(Tank *, unsigned short, int);
extern unsigned short func_8004A694(Pending **, int);
extern void func_8004BFC8(Tank *, Pending *);
extern void func_8004C058(Tank *, unsigned short);
extern int func_8004BA6C(Tank *, Pending *);
extern void func_8004B71C(Tank *);

int func_8004B880(Tank *tank) {
    Route *route = &tank->route;
    unsigned short cur;
    unsigned short id = route->next;
    PathNode *node;
    Pending *pending;
    Pending **link;
    unsigned short new_id;
    int key;

    if (id == 0) {
        return 0;
    }
    if (D_800A5B24->free_moves == 0) {
        return 0;
    }
    cur = id;
    node = func_8004A794(cur);
    switch (node->kind) {
    case 2:
        new_id = func_8004B328(tank, cur, route->side);
        route->next = new_id;
        if (new_id == 0) {
            return 0;
        }
        break;
    case 3:
        switch (node->branch) {
        case 1:
        case 2:
        case 17:
        case 18:
            new_id = func_8004B328(tank, cur, node->branch);
            route->next = new_id;
            if (new_id == 0) {
                return 0;
            }
            break;
        case 0:
            new_id = func_8004A694(&pending, 2);
            node->link = new_id;
            pending->prev = cur;
            route->count++;
            func_8004BFC8(tank, pending);
            func_8004C058(tank, new_id);
            func_8004B71C(tank);
            break;
        case 3:
            node->link = func_8004A694(&pending, 4);
            pending->prev = cur;
            route->count++;
            key = func_8004BA6C(tank, pending);
            for (link = &route->pending; *link != 0; link = &(*link)->next) {
                if (key < (*link)->key) {
                    break;
                }
            }
            pending->next = *link;
            *link = pending;
            pending->key = key;
            func_8004B71C(tank);
            break;
        }
        break;
    }
    return 1;
}
