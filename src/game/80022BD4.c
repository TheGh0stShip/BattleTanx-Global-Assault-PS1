typedef struct Node {
    unsigned short id;
    short next;
    short kind;
    char pad06[0x40 - 6];
} Node;
extern Node *D_800D3258;
extern short D_800D325C;
extern unsigned int D_800A4388;
extern int D_800A438C;

Node *func_80022BD4(void) {
    int index;
    Node *node;

    if (D_800A4388 < 16) {
        return 0;
    }
    index = D_800D325C;
    if (index == -1) {
        return 0;
    }
    D_800A4388--;
    node = (Node *)((index * sizeof(Node)) + (int)D_800D3258);
    D_800A438C++;
    D_800D325C = node->next;
    return node;
}
