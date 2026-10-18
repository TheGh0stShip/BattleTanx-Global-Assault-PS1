typedef struct Node {
    int pad0;
    int pad4;
    unsigned short *key;
    unsigned short id;
    short padE;
    int a;
    int b;
    int next;
} Node;

extern Node *func_800237D0(int tag, int size);

void func_80074B24(int a, unsigned short *key, int b) {
    Node *n = func_800237D0(71, 28);
    if (n != 0) {
        n->key = key;
        n->id = *key;
        n->a = a;
        n->b = b;
        n->next = 0;
    }
}
