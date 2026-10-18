typedef struct Node {
    unsigned short id;
    short next;
    short kind;
    char pad06[0x40 - 6];
} Node;
typedef struct NodeClass {
    void (*update)(Node *, int *);
    void *unk04;
    void (*draw)(Node *);
} NodeClass;
extern Node *D_800D3258;
extern short D_800D325C;
extern short D_800D3260[];
extern NodeClass D_800D32F4[];
extern unsigned char D_800D3174[][74];
extern int D_800A4388;
void func_80022C3C(void);
void func_8004866C(void);

void func_80022D64(int phase) {
    int kind;
    short *link;
    int result;
    short index;
    short free;

    func_80022C3C();
    for (kind = 0; kind < 74; kind++) {
        if (D_800D32F4[kind].update == 0) {
            continue;
        }
        if (D_800D3174[phase][kind] == 0) {
            continue;
        }
        link = &D_800D3260[kind];
        while (*link != -1) {
            result = 0;
            D_800D32F4[D_800D3258[*link].kind].update(&D_800D3258[*link], &result);
            if (result != 0) {
                if (result == 1) {
                    D_800D3258[*link].id = 0;
                    D_800D3258[*link].kind = -1;
                    index = *link;
                    *link = D_800D3258[*link].next;
                    free = D_800D325C;
                    D_800D325C = index;
                    D_800D3258[index].next = free;
                    D_800A4388++;
                }
            } else {
                link = &D_800D3258[*link].next;
            }
        }
    }
    func_80022C3C();
    func_8004866C();
}
