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

static inline int take_branch_a(Node *node) {
    if (node->branch_b == 0) {
        return 1;
    }
    if (node->branch_a == 0) {
        return 0;
    }
    return node->branch_a == 0;
}

extern int func_8004A160(unsigned short *, int);

unsigned short func_8004A3D4(unsigned short *link) {
    int total = 0;
    int done;
    Node *node;
    unsigned short prev;
    unsigned short id;
    unsigned short count;

    __asm__("" : "=r"(total) : "0"(total));
    done = 0;
    do {
        node = node_lookup(*link);
        if (node == 0) {
            done = 1;
        } else {
            switch (node->kind) {
            case 3:
                link = &node->link;
                break;
            case 2:
                node = node_lookup(*link);
                prev = node->prev;
                if (take_branch_a(node)) {
                    id = node->branch_a;
                    node->branch_a = 0;
                } else {
                    id = node->branch_b;
                    node->branch_b = 0;
                }
                count = func_8004A160(link, 0);
                *link = id;
                node = node_lookup(id);
                if (node != 0) {
                    node->prev = prev;
                }
                total += count;
                break;
            case 4:
                done = 1;
                break;
            default:
                done = 1;
                break;
            }
        }
    } while (!done);
    prev = total;
    return prev;
}
