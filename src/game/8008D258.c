struct ListNode {
    struct ListNode *previous;
    struct ListNode *next;
    unsigned char pad_08[4];
    unsigned short width;
    unsigned short height;
};

void func_8008D258(unsigned char *buckets, struct ListNode *node) {
    int index;
    struct ListNode **bucket;

    if (node->previous != 0) {
        node->previous->next = node->next;
    }
    if (node->next != 0) {
        node->next->previous = node->previous;
        return;
    }
    index = (node->width * node->height) >> 10;
    if (index >= 32) {
        index = 31;
    }
    bucket = (struct ListNode **)(buckets + 8);
    bucket[index] = node->previous;
}
