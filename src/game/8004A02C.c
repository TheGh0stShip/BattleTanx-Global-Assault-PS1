typedef struct {
    unsigned char kind;
    char pad1[11];
    unsigned short branch_a;
    unsigned short branch_b;
    char pad10[2];
    unsigned char branch;
    char pad13[7];
    unsigned short link;
} Node;
typedef struct {
    char pad0[8];
    Node nodes[1];
} NodeSystem;
extern NodeSystem *D_800A5B24;

static inline unsigned short node_next(Node *node) {
    unsigned short id = 0;

    if (node != 0) {
        switch (node->kind) {
        case 3:
            id = node->link;
        case 2:
            switch (node->branch) {
            case 0:
                break;
            case 1:
                id = node->branch_a;
                break;
            case 2:
                id = node->branch_b;
                break;
            }
            break;
        }
    }
    return id;
}

Node *func_8004A02C(Node *node, unsigned short *out) {
    unsigned short id = node_next(node);
    Node *cur;

    while (id != 0) {
        cur = &D_800A5B24->nodes[id];
        switch (cur->kind) {
        case 3:
            *out = id;
            return cur;
        case 4:
            *out = 0;
            return 0;
        case 2:
            id = node_next(cur);
            break;
        default:
            *out = 0;
            return 0;
        }
    }
    *out = 0;
    return 0;
}
