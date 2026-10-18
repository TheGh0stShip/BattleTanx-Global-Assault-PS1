typedef struct Node {
    unsigned short id;
    short next;
    short kind;
    char pad06[0x40 - 6];
} Node;
typedef struct NodeClass {
    int (*update)(Node *, int *);
    void *unk04;
    void (*draw)(Node *);
} NodeClass;
extern Node *D_800D3258;
extern short D_800D3260[];
extern NodeClass D_800D32F4[];
void func_80022C3C(void);

void func_80022F2C(void) {
    int kind;
    int index;

    func_80022C3C();
    for (kind = 0; kind < 74; kind++) {
        if (D_800D32F4[kind].draw == 0) {
            continue;
        }
        index = D_800D3260[kind];
        while (index != -1) {
            D_800D32F4[D_800D3258[index].kind].draw(&D_800D3258[index]);
            index = D_800D3258[index].next;
        }
    }
}
