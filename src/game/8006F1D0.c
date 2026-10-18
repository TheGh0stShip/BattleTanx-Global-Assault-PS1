typedef struct Node {
    struct Node *next;
    int data[10];
} Node;

extern Node D_800EABE4;
extern Node *D_800EAC10;
extern int D_800EAC14;
extern int D_800EAC18;

void func_8006F1D0(void) {
    Node *node;

    D_800EAC10 = &D_800EABE4;
    D_800EABE4.next = 0;
    while (D_800EAC10 != &D_800EABE4 - 511) {
        node = D_800EAC10;
        D_800EAC10 = node - 1;
        node[-1].next = node;
    }
    D_800EAC14 = 0;
    D_800EAC18 = 0;
}
