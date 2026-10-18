typedef struct {
    unsigned char type;
    char pad1[25];
    unsigned short next;
} Node;
typedef struct {
    char pad0[8];
    Node nodes[1];
} NodeSystem;
extern NodeSystem *D_800A5B24;
extern unsigned short func_8004A160(unsigned short *, int);

unsigned short func_8004A820(unsigned short *link, unsigned short count, int arg) {
    unsigned short i;
    Node *node;
    unsigned short id;

    for (i = 0; i < count; i++) {
        id = *link;
        if (id == 0) {
            return 0;
        }
        node = &D_800A5B24->nodes[id];
        switch (node->type) {
        case 3:
            link = &node->next;
            break;
        case 4:
            return 0;
        default:
            return 0;
        }
    }
    return func_8004A160(link, arg);
}
