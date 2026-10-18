typedef struct Node {
    unsigned short id;
    short next;
    short kind;
    char pad06[0x40 - 6];
} Node;
extern short D_800D3254;
extern Node *D_800D3258;
extern short D_800D3260[];

void func_80022C3C(void) {
    Node *node;
    int next;

    if (D_800D3254 == -1) {
        return;
    }
    do {
        node = (Node *)((D_800D3254 * sizeof(Node)) + (int)D_800D3258);
        next = node->next;
        node->next = D_800D3260[node->kind];
        D_800D3260[node->kind] = D_800D3254;
        D_800D3254 = next;
    } while (next != -1);
}
