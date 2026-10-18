typedef struct ResourceNode ResourceNode;

struct ResourceNode {
    unsigned int marker;
    ResourceNode *next;
};

extern int D_800ADD04;
extern ResourceNode *D_800ADD00;
extern int D_800E53F0;
extern ResourceNode *func_80085848(int value, int size);
extern int func_80085F5C(int value);

void *func_80068DA4(int size) {
    register ResourceNode *node asm("$3");
    int allocation_size = size + 8;

    D_800ADD04++;
    D_800E53F0 = func_80085F5C(-1);
    node = func_80085848(-1, allocation_size);
    if ((unsigned int)node <= 0xEA5F) {
        for (;;) {
        }
    }
    node->marker = 0xDEC0ADDE;
    node->next = D_800ADD00->next;
    D_800ADD00->next = node;
    return node + 1;
}
