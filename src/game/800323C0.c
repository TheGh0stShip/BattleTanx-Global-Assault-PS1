typedef struct Node {
    short field00;
    short next;
    unsigned char fields04[0x16 - 4];
    unsigned char subject;
    unsigned char fields17[0x40 - 0x17];
} Node;

typedef struct Subject {
    unsigned char fields00[0x58];
    int state;
    unsigned char fields5C[0x114 - 0x5C];
} Subject;

typedef char Node_size[(sizeof(Node) == 0x40) ? 1 : -1];
typedef char Subject_size[(sizeof(Subject) == 0x114) ? 1 : -1];

extern short D_800D329C;
extern Node *D_800D3258;
extern Subject D_800E3E68[];
extern void func_800530E0(Subject *, int, int);

static inline Subject *get_subject(int index) {
    if (index == 127)
        return 0;
    return &D_800E3E68[index];
}

void func_800323C0(void) {
    register int first asm("$3") = D_800D329C;
    int index;
    Node *node;
    Subject *subject;

    if (first == -1)
        return;
    index = first;
    do {
        node = &D_800D3258[index];
        subject = get_subject(node->subject);
        if (subject->state != 2)
            func_800530E0(subject, 2500, 1);
        index = node->next;
    } while (index != -1);
}
