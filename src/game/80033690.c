typedef struct { short pad; short next; short type; short rest[29]; } Node;
typedef struct { int pad[4]; int count; } Stats;
extern short D_800D3254;
extern Node *D_800D3258;
extern Stats D_800D2FE4;

void func_80033690(void) {
    short i;
    Node *n;

    D_800D2FE4.count = 0;
    i = D_800D3254;
    while (i != -1) {
        n = &D_800D3258[i];
        if (n->type == 8) {
            D_800D2FE4.count++;
        }
        i = n->next;
    }
}
