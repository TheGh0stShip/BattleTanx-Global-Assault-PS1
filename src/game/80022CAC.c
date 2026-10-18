typedef struct Node {
    unsigned short id;
    short next;
    short kind;
    char pad06[0x40 - 6];
} Node;
extern Node *D_800D3258;
extern short D_800D325C;
extern short D_800D3260[];
extern int D_800A4388;

void func_80022CAC(Node *node) {
    short *link = &D_800D3260[node->kind];
    Node *cur;
    short index;
    short free;

    while (*link != -1) {
        cur = &D_800D3258[*link];
        if (cur == node) {
            break;
        }
        link = &cur->next;
    }
    if (*link == -1) {
        return;
    }
    D_800D3258[*link].id = 0;
    index = *link;
    *link = D_800D3258[*link].next;
    free = D_800D325C;
    D_800D325C = index;
    D_800D3258[index].next = free;
    D_800A4388++;
}
