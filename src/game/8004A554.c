typedef struct {
    unsigned char kind;
    char pad1;
    unsigned short prev;
    char pad4[8];
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

static inline Node *node_lookup(unsigned short id) {
    if (id == 0) {
        return 0;
    }
    return &D_800A5B24->nodes[id];
}

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

unsigned short func_8004A554(unsigned short prev, unsigned short *head, unsigned short id) {
    unsigned short last = id;
    unsigned short old = *head;
    Node *node = node_lookup(last);
    unsigned short next;
    unsigned short count;

    if (node == 0) {
        return 0;
    }
    *head = id;
    node->prev = prev;
    count = 1;
    next = node->link;
    while (next != 0) {
        last = next;
        node = node_lookup(last);
        next = node_next(node);
        count++;
    }
    node->link = old;
    node = node_lookup(old);
    node->prev = last;
    return count;
}
