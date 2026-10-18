typedef struct {
    unsigned char kind;
    char pad1;
    unsigned short prev;
    int x;
    char pad8[4];
    union {
        int z;
        struct {
            unsigned short left;
            unsigned short right;
        } b;
    } u;
    char pad10[2];
    unsigned char branch;
    char pad13[5];
    unsigned char mode;
    char pad19;
    unsigned short link;
} Node;
typedef struct {
    void *pending;
    unsigned short head;
    unsigned short count;
    char pad8[2];
    unsigned short next;
    char padC[0x14 - 0xC];
    unsigned short last;
    unsigned short node;
    int side;
    char pad1C[0x24 - 0x1C];
    int from_x;
    int from_y;
    int from_z;
} Route;
typedef struct {
    char pad0[0xF8];
    Route route;
    char pad128[0x14A - 0x128];
    unsigned short route_seen2;
    char pad14C[0x180 - 0x14C];
    int flags;
} Tank;
extern Node *func_8004A794(unsigned short);
extern void func_8004A7C4(unsigned short);
extern int func_8004A160(unsigned short *, Route *);
extern void func_8004BF64(Tank *);

void func_8004AC64(Tank *tank) {
    Route *route = &tank->route;
    unsigned short head = route->head;
    Node *node;
    Node *next;
    Node *m;
    unsigned short link;
    int flags;

    if (head == 0) {
        return;
    }
    tank->route_seen2 = 0;
    node = func_8004A794(head);
    link = node->link;
    route->from_x = node->x;
    route->from_z = node->u.z;
    if (link == 0) {
        route->next = 0;
        route->last = 0;
        route->node = 0;
        route->side = 0;
        route->head = 0;
        route->count--;
    } else {
        next = func_8004A794(link);
        switch (next->kind) {
        case 3:
            if (route->next == head) {
                route->next = 0;
            }
            next->prev = 0;
            route->head = link;
            route->count--;
            break;
        case 4:
            route->next = 0;
            route->last = 0;
            route->node = 0;
            route->side = 0;
            route->pending = 0;
            route->head = 0;
            func_8004A7C4(link);
            route->count -= 2;
            break;
        case 2:
            route->count--;
            if (link == route->next) {
                goto keep;
            }
            route->pending = 0;
            switch (next->branch) {
            case 1:
                route->head = next->u.b.left;
                next->u.b.left = 0;
                if (route->head != 0) {
                    func_8004A794(route->head)->prev = 0;
                }
                route->count -= func_8004A160(&node->link, route);
                break;
            case 2:
                route->head = next->u.b.right;
                next->u.b.right = 0;
                if (route->head != 0) {
                    func_8004A794(route->head)->prev = 0;
                }
                route->count -= func_8004A160(&node->link, route);
                break;
            case 0:
            default:
            keep:
                next->prev = 0;
                route->head = link;
                func_8004BF64(tank);
                break;
            }
            break;
        default:
            route->next = 0;
            route->last = 0;
            route->node = 0;
            route->side = 0;
            route->count -= func_8004A160(&node->link, route);
            route->head = 0;
            route->pending = 0;
            break;
        }
    }
    m = func_8004A794(route->head);
    if (m != 0 && m->kind == 3) {
        m->mode = 0;
    }
    if (route->pending == 0 && route->count < 6) {
        flags = tank->flags & ~0x100;
        tank->flags = flags;
        if (route->count < 5) {
            tank->flags = flags & ~0x80;
        }
    }
    func_8004A7C4(head);
}
