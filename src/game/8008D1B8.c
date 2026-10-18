typedef struct Node8008D1B8 {
    struct Node8008D1B8 *next;
    struct Node8008D1B8 *prev;
    int data;
    unsigned short w;
    unsigned short h;
} Node8008D1B8;

typedef struct {
    Node8008D1B8 *free;
    int count;
    Node8008D1B8 *buckets[32];
} Pool8008D1B8;

void func_8008D1B8(Pool8008D1B8 *pool, Node8008D1B8 *node) {
    int key = node->w * node->h;
    int index = key >> 10;
    Node8008D1B8 *prev;
    Node8008D1B8 *cur;

    if (index >= 32) {
        index = 31;
    }
    cur = pool->buckets[index];
    prev = 0;
    while (cur != 0 && cur->w * cur->h < key) {
        prev = cur;
        cur = cur->next;
    }
    node->prev = prev;
    node->next = cur;
    if (cur != 0) {
        cur->prev = node;
    }
    if (prev != 0) {
        prev->next = node;
    } else {
        pool->buckets[index] = node;
    }
}
