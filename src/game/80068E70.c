typedef struct ResourceNode ResourceNode;

struct ResourceNode {
    int value;
    ResourceNode *next;
};

extern int D_800ADD04;
extern ResourceNode *D_800ADD00;
extern void func_80085DD4(ResourceNode *node);
extern void *func_80085F5C(int value);

static inline void clear_resources(ResourceNode *root) {
    ResourceNode *node = root->next;

    while (node != 0) {
        ResourceNode *next = node->next;

        func_80085DD4(node);
        D_800ADD04--;
        node = next;
    }
    root->next = 0;
}

void func_80068E70(void) {
    if (D_800ADD00 != 0)
        clear_resources(D_800ADD00);
    func_80085F5C(-1);
}
