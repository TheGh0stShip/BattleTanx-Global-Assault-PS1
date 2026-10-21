typedef struct Node Node;
struct Node {
    unsigned char kind;
    char pad1;
    unsigned short prev;
    Node *free_next;
    union {
        Node *next;
        unsigned short id;
    } u;
    unsigned short branch_a;
    unsigned short branch_b;
    unsigned short chain;
    char pad12[0x1A - 0x12];
    unsigned short link;
};
typedef struct {
    char pad0[8];
    Node nodes[2048];
    Node *free_list;
} NodeSystem;
typedef struct {
    Node *pending;
    char pad4[0x14 - 4];
    unsigned short chain;
    unsigned short current;
    int current_key;
} Route;
extern NodeSystem *D_800A5B24;

static inline Node *node_at(unsigned short id) {
    if (id == 0) {
        return 0;
    }
    return &D_800A5B24->nodes[id];
}

unsigned short func_8004A160(unsigned short *head, Route *route) {
    unsigned short id = *head;
    unsigned short count;
    unsigned short next;
    Node *node;
    Node *link;
    Node *dead;
    unsigned short *chain;
    Node **list;
    int done;

    if (id == 0) {
        return 0;
    }
    count = 0;
    *head = 0;
    node = node_at(id);
    node->prev = 0;
    do {
        done = 0;
        __asm__("" : : "r"(id));
        do {
            switch (node->kind) {
            case 3:
                next = node->link;
                if (next == 0) {
                    done = 1;
                } else {
                    id = next;
                    node = node_at(next);
                }
                break;
            case 2:
                if (route != 0) {
                    for (chain = &route->chain; *chain != 0; chain = &link->chain) {
                        link = node_at(*chain);
                        if (id == *chain) {
                            *chain = link->chain;
                            break;
                        }
                    }
                    if (id == route->current) {
                        route->current = 0;
                        route->current_key = 0;
                    }
                }
                next = node->branch_b;
                if (next != 0) {
                    id = next;
                    node = node_at(next);
                    break;
                }
                next = node->branch_a;
                if (next == 0) {
                    done = 1;
                } else {
                    id = next;
                    node = node_at(next);
                }
                break;
            case 4:
                if (route != 0) {
                    for (list = &route->pending; *list != 0; list = &(*list)->u.next) {
                        if (node == *list) {
                            *list = node->u.next;
                            break;
                        }
                    }
                }
                done = 1;
                break;
            default:
                done = 1;
                break;
            }
        } while (!done);
        for (;;) {
            next = node->prev;
            dead = node_at(id);
            dead->free_next = D_800A5B24->free_list;
            D_800A5B24->free_list = dead;
            dead->u.id = id;
            dead->kind = 1;
            count++;
            if (next == 0) {
                goto out;
            }
            node = node_at(next);
            if (node->kind != 3) {
                break;
            }
            id = next;
        }
        if (node->branch_b == id) {
            node->branch_b = 0;
        } else {
            node->branch_a = 0;
        }
        id = next;
    } while (next != 0);
out:
    return count;
}
