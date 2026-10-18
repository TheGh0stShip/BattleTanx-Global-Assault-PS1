typedef struct ListNode {
    unsigned char unused[0x1C];
    struct ListNode *next;
} ListNode;

typedef struct ListOwner {
    unsigned char unused[8];
    ListNode *head;
} ListOwner;

void func_80033FD4(ListOwner *owner, ListNode *target) {
    register ListNode *head __asm__("$2") = owner->head;
    register ListNode *current __asm__("$3") = head;
    ListNode *next;

    if (head == target) {
        owner->head = target->next;
        goto done;
    }
    goto test;
loop:
    next = current->next;
    if (next == target) {
        goto found;
    }
    current = next;
test:
    if (current != 0) {
        goto loop;
    }
found:
    current->next = target->next;
done:
    target->next = 0;
}
