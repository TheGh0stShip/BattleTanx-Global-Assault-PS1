typedef struct Node {
    unsigned short id;
    short next;
    short kind;
    char pad06[0x40 - 6];
} Node;
extern short D_800D3254;
extern Node *D_800D3258;
extern short D_800D325C;
extern int D_800A4388;
extern int D_800A4390;

Node *func_80022B64(int kind) {
    int index = D_800D325C;
    short used;
    Node *node;
    short next;

    if (index == -1) {
        return 0;
    }
    used = D_800D3254;
    D_800D3254 = index;
    node = (Node *)((index * sizeof(Node)) + (int)D_800D3258);
    next = node->next;
    node->next = used;
    node->kind = kind;
    node->id = D_800A4390++;
    D_800A4388--;
    D_800D325C = next;
    return node;
}
